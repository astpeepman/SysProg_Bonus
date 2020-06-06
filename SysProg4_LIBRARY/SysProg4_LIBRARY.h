// SysProg4_LIBRARY.h: основной файл заголовка для библиотеки DLL SysProg4_LIBRARY
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CSysProg4LIBRARYApp
// Реализацию этого класса см. в файле SysProg4_LIBRARY.cpp
//

class CSysProg4LIBRARYApp : public CWinApp
{
public:
	CSysProg4LIBRARYApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
