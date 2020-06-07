// SysProg_Bonus_Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "framework.h"
#include "SysProg_Bonus_Server.h"
#include <iostream>
#include <thread>
#include <windows.h>
#include <mutex>
#include <vector>
#include <sstream>
#include <fstream>
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Единственный объект приложения

CWinApp theApp;

using namespace std;

struct messHeader {
    int adress;
    int code;
    int count;
    int size;
};

vector<HANDLE> hEvents;
int nCode;
string Message;
mutex MainMutex;

HANDLE hPipe;
CSocket s;


int Flag = -1;

void SetConfirm() {
    DWORD dwWrite;
    bool ok = true;
    WriteFile(hPipe, &ok, sizeof(bool), &dwWrite, nullptr);
}

string GetMess_Pipe(int size) {
    string mess;
    DWORD dwRead;
    char* buff = new char[size];
    ReadFile(hPipe, buff, size, &dwRead, nullptr);
    buff[size-1] = '\0';
    mess = buff;
    delete[] buff;
    return mess;
}

string GetMess_Sock(int size) {
    if (size <= 0) {
        cout << "ERROR :: Failed to receive message :: ERROR";
        return string("");
    }
    vector <char> v(size);
    s.Receive(&v[0], size);
    return string(&v[0], size);
}

string int_to_str(int i) {
    ostringstream stream;
    stream << i;
    return stream.str();
}

void ThreadFunc(int id) {
    MainMutex.lock();
    cout << "Thread " << id << " created" << endl;
    MainMutex.unlock();

    //КАКИЕ ТО ДЕЙСТВИЯ ПОТОКА
    //-----
    //КОНЕЦ ДЕЙСТВИЙ

    while (true) {
        WaitForSingleObject(hEvents[id], INFINITE);
        switch (nCode) {
        case 0: {
            break;
        }
        case 1: {
            MainMutex.lock();
            cout << "Thread " << id << " done" << endl;
            MainMutex.unlock();
            return;
        }
        case 2: {
            MainMutex.lock();
            string fname = int_to_str(id) + ".txt";
            ofstream fout(fname);
            fout << Message;
            cout << "text was save in file " + fname << endl;
            MainMutex.unlock();
        }
        }
    }
}

void CreatePipe()
{
    hPipe = CreateNamedPipe("\\\\.\\pipe\\MyPipe",
        PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
        4096, 4096, 0, NULL);
    if (hPipe == INVALID_HANDLE_VALUE)
    {
        cout << L"Error of creating pipe! Process will be terminated!" << endl;
        return;
    }

}

void FlagThread0() {
    CreatePipe();
    ConnectNamedPipe(hPipe, NULL);
    DWORD dwRead;
    int buff;
    
    ReadFile(hPipe, &buff, sizeof(int), &dwRead, nullptr);

    Flag = buff;
    if (buff ==0) {
        cout << "App connected with Named Pipe" << endl;

        CSocket Local;
        Local.Create();
        Local.Connect("127.0.0.1", 11111);
        Local.Send(&buff, sizeof(int));
        Local.Close();
        return;
    }

    if (buff == 1) {
        DisconnectNamedPipe(hPipe);
        CloseHandle(hPipe);
        return;
    }
}

//CSocket Server;


void FlagThread1() {
    
    int buff;

    s.Receive(&buff, sizeof(int));

    Flag = buff;
    if (buff ==1) {
        cout << "App connected with Windows Socket" << endl;

        HANDLE hLocalPipe= CreateFile("\\\\.\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        DWORD dwWrite;
        WriteFile(hLocalPipe, &buff, sizeof(int), &dwWrite, nullptr);
        CloseHandle(hLocalPipe);
        return;
    }
    if (buff == 0) {
        s.Close();
        //Server.Close();
        return;
    }
}

void start() {
    vector<thread> v_threads;

    Flag=-1;

    AfxSocketInit();
    CSocket Server;
    Server.Create(11111);

    while (true) {
        thread t1(FlagThread0);
        t1.detach();

        Server.Listen();
        Server.Accept(s);
        FlagThread1();

        messHeader m;
        int vectsize = v_threads.size();

        switch (Flag) {
        case 0: {
            DWORD dwRead;
            ReadFile(hPipe, &m, sizeof(m), &dwRead, NULL);
            break;
        }
        case 1: {
            s.Receive(&m, sizeof(messHeader));
            break;
        }
        }

        nCode = m.code;

        switch (nCode)
        {
        case 0: {
            for (int i = vectsize; i < vectsize + m.count; i++) {
                hEvents.push_back(CreateEvent(NULL, FALSE, FALSE, NULL));
                v_threads.push_back(thread(ThreadFunc, i));
                //v_threads.at(i).detach();
            }
            break;
        }
        case 1: {
            vectsize = v_threads.size();
            if (m.count != -1) {
                for (int i = vectsize - 1; i >= vectsize - m.count; i--) {
                    if (i < 0)
                        break;

                    PulseEvent(hEvents[i]);
                    v_threads[i].join();
                    hEvents.pop_back();
                    v_threads.pop_back();

                }
            }
            else {
                for (int i = vectsize - 1; i >= 0; i--) {
                    PulseEvent(hEvents[i]);
                    v_threads[i].join();
                    hEvents.pop_back();
                    v_threads.pop_back();
                }
            }
            break;
        }
        case 2: {
            switch (Flag) {
            case 0: {
                SetConfirm();
                Message = GetMess_Pipe(m.size);
                break;
            }
            case 1: {
                Message = GetMess_Sock(m.size);
                break;
            }
            }

            cout << "message: " << Message << endl;
            if (m.adress != -1)
                PulseEvent(hEvents[m.adress]);
            else {
                for (int i = 0; i < v_threads.size(); i++) {
                    PulseEvent(hEvents[i]);
                }
            }
            break;
        }
        }

        vectsize = v_threads.size();

        switch (Flag) {
        case 0: {
            DWORD dwWrite;
            WriteFile(hPipe, &vectsize, sizeof(int), &dwWrite, nullptr);
            DisconnectNamedPipe(hPipe);
            break;
        }
        case 1: {
            s.Send(&vectsize, sizeof(int));
            s.Close();
            break;
        }
        }
    }
}


int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // инициализировать MFC, а также печать и сообщения об ошибках про сбое
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: вставьте сюда код для приложения.
            wprintf(L"Критическая ошибка: сбой при инициализации MFC\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: вставьте сюда код для приложения.
            start();
        }
    }
    else
    {
        // TODO: измените код ошибки в соответствии с потребностями
        wprintf(L"Критическая ошибка: сбой GetModuleHandle\n");
        nRetCode = 1;
    }

    return nRetCode;
}
