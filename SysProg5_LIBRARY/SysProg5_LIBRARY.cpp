// SysProg5_LIBRARY.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "SysProg5_LIBRARY.h"
#include <afxsock.h>
#include <iostream>

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

// CSysProg5LIBRARYApp

BEGIN_MESSAGE_MAP(CSysProg5LIBRARYApp, CWinApp)
END_MESSAGE_MAP()


// Создание CSysProg5LIBRARYApp

CSysProg5LIBRARYApp::CSysProg5LIBRARYApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CSysProg5LIBRARYApp

CSysProg5LIBRARYApp theApp;


// Инициализация CSysProg5LIBRARYApp

BOOL CSysProg5LIBRARYApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}

CSocket S;

struct messHeader
{
	int adress;
	int code;
	int count;
	int size;
	messHeader() {
		adress = -2;
		code = 0;
		count = 0;
		size = 0;
	}
};

extern "C" __declspec(dllexport) bool __stdcall init() {
	
	AfxSocketInit();
	S.Create();
	if (!S.Connect("127.0.0.1", 11111))
	{
		return false;
	}
	else {
		int flag = 1;
		S.Send(&flag, sizeof(int));
		return true;
	}

}

extern "C" __declspec(dllexport) void __stdcall deinit() {
	S.Close();
}

extern "C" __declspec(dllexport) int __stdcall  StartThread(int count) {

	messHeader m;
	m.code = 0;
	m.count = count;
	S.Send(&m, sizeof(m));

	int ThreadsCount;
	S.Receive(&ThreadsCount, sizeof(int));
	return ThreadsCount;
}

extern "C" __declspec(dllexport) int __stdcall  StopThread(int count) {

	messHeader m;
	m.code = 1;
	m.count = count;
	S.Send(&m, sizeof(m));

	int ThreadsCount;
	S.Receive(&ThreadsCount, sizeof(int));
	return ThreadsCount;
}

bool Confirm() {

	bool ok = false;
	S.Send(&ok, sizeof(bool));
	return ok;
}

extern "C" __declspec(dllexport) void __stdcall SendMess(char* mess, int adress) {

	messHeader m;
	m.code = 2;
	m.size = strlen(mess);
	m.adress = adress;

	S.Send(&m, sizeof(m));

	std::string buff = mess;

	S.Send(buff.c_str() , m.size);
}

extern "C" __declspec(dllexport) void __stdcall INITAFX() {
	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
}
