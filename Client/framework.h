#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // remove support for MFC controls in dialogs

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Control
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include "afxsock.h"
#include <Windows.h> 
#include <fstream>
using namespace std;

enum statusCursor { UP, DOWN, LEFT, RIGHT, enter, BACK };

class consoleGraphic
{
public:
	int heigth = 700, width = 1320;
	consoleGraphic();
	void resizeConsole();
	void gotoxy(int x, int y);
	void FixConsoleWindow();
	void ShowCur(bool CursorVisibility);
	void drawBox(int x, int y, int h, int w);
};

struct user {
	string username, strpass;
};

class client
{
public:
	user clientA; consoleGraphic conSole;
	client();
	// Register
	void accountRegister(user& clientA);
	bool registerValid(user clientA);
	// Log in
	bool loginValid(user clientA);
};