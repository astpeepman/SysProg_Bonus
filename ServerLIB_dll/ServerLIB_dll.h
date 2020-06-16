// ServerLIB_dll.h: основной файл заголовка для библиотеки DLL ServerLIB_dll
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CServerLIBdllApp
// Реализацию этого класса см. в файле ServerLIB_dll.cpp
//

class CServerLIBdllApp : public CWinApp
{
public:
	CServerLIBdllApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#include <afxsock.h>
#include <iostream>
#include <thread>
#include <vector>


using namespace std;

struct messHeader {
	int adress;
	int code;
	int count;
	int size;
};

int Flag;
HANDLE hPipe;
CSocket s;
CSocket Server;

//void FlagThread0();
//void FlagThread1();
//extern "C" __declspec(dllexport) bool __stdcall initAll();
//extern "C" __declspec(dllexport) messHeader __stdcall ReadyHeader();