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


#include "ServerLIB_dll.cpp"

//#include "Lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Единственный объект приложения

CWinApp theApp;

using namespace std;

//struct messHeader {
//    int adress;
//    int code;
//    int count;
//    int size;
//};


//extern "C" __declspec(dllimport) bool __stdcall initAll();
//extern "C" __declspec(dllimport) messHeader __stdcall ReadyHeader();
//extern "C" __declspec(dllimport) char* __stdcall GetMessageFromApp(int size);
//extern "C" __declspec(dllimport) void __stdcall SendThreadCount(int vectsize);


vector<HANDLE> hEvents;
int nCode;
string Message;
mutex MainMutex;



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



void start() {
    vector<thread> v_threads;

    if (!initAll()) {
        cout << "ERROR::INIT";
        return;
    }

    while (true) {
        messHeader m = ReadyHeader();
        int vectsize = v_threads.size();
       

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
            Message = GetMessageFromApp(m.size);

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
        SendThreadCount(vectsize);

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
