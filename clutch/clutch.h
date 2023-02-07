
// clutch.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CclutchApp:
// Сведения о реализации этого класса: clutch.cpp
//

class CclutchApp : public CWinApp
{
public:
	CclutchApp();

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CclutchApp theApp;
