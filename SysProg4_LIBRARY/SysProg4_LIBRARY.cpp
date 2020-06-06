// SysProg4_LIBRARY.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "SysProg4_LIBRARY.h"
#include <windows.h>
#include <iostream>
#include <conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		должен стоять в качестве первого оператора в
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CSysProg4LIBRARYApp

BEGIN_MESSAGE_MAP(CSysProg4LIBRARYApp, CWinApp)
END_MESSAGE_MAP()


// Создание CSysProg4LIBRARYApp

CSysProg4LIBRARYApp::CSysProg4LIBRARYApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CSysProg4LIBRARYApp

CSysProg4LIBRARYApp theApp;


// Инициализация CSysProg4LIBRARYApp

BOOL CSysProg4LIBRARYApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


using namespace std;

HANDLE hPipe;

struct messHeader
{
    int potok;
    int codeOfOperation;
    int count;
    int size;
    messHeader() {
        potok = -2;
        codeOfOperation = 0;
        count = 0;
        size = 0;
    }
};

extern "C" __declspec(dllexport) bool __stdcall init() {

    if (WaitNamedPipe("\\\\.\\pipe\\MyPipe", NMPWAIT_WAIT_FOREVER))
    {
        hPipe = CreateFile("\\\\.\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        DWORD dwWrite;
        int flag = 0;
        WriteFile(hPipe, &flag, sizeof(int), &dwWrite, nullptr);
        return true;
    }
    else {
        return false;
    }
}

extern "C" __declspec(dllexport) void __stdcall deinit() {
    CloseHandle(hPipe);
}

bool Confirm() {

    DWORD dwRead;
    bool ok = false;
    ReadFile(hPipe, &ok, sizeof(bool), &dwRead, nullptr);
    return ok;
}

extern "C" __declspec(dllexport) void __stdcall SendMess(char* mess, int adress) {
    DWORD dwWrite;
    messHeader m;
    m.codeOfOperation = 2;
    m.size = strlen(mess);
    m.potok = adress;

    WriteFile(hPipe, &m, sizeof(m), &dwWrite, nullptr);

    if (Confirm()) {
        WriteFile(hPipe, mess, strlen(mess), &dwWrite, nullptr);
    }
}

extern "C" __declspec(dllexport) int __stdcall  StartThread(int count) {
    DWORD dwWrite;
    messHeader m;
    m.codeOfOperation = 0;
    m.count = count;

    WriteFile(hPipe, &m, sizeof(m), &dwWrite, nullptr);

    int ThreadsCount;
    DWORD dwRead;
    ReadFile(hPipe, &ThreadsCount, sizeof(int), &dwRead, nullptr);
    return ThreadsCount;

}

extern "C" __declspec(dllexport) int __stdcall  StopThread(int count) {


    DWORD dwWrite;
    messHeader m;
    m.codeOfOperation = 1;
    m.count = count;

    WriteFile(hPipe, &m, sizeof(m), &dwWrite, nullptr);

    int ThreadsCount;
    DWORD dwRead;
    ReadFile(hPipe, &ThreadsCount, sizeof(int), &dwRead, nullptr);
    return ThreadsCount;

}