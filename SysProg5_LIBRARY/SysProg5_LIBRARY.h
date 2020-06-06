// SysProg5_LIBRARY.h: основной файл заголовка для библиотеки DLL SysProg5_LIBRARY
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CSysProg5LIBRARYApp
// Реализацию этого класса см. в файле SysProg5_LIBRARY.cpp
//

class CSysProg5LIBRARYApp : public CWinApp
{
public:
	CSysProg5LIBRARYApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
