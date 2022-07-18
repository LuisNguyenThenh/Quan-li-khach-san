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
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include "core.hpp"
#include "highgui.hpp"
#define fi first
#define se second
//using json = nlohmann::json;
using namespace std;
using namespace cv;

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
	char* username = new char[101],
		* strpass = new char[101],
		* idBanking = new char[11];
};

class client
{
public:
	consoleGraphic conSole;
	client();
	// Register
	bool registerValid(user clientA);

	void accountRegister(user& clientA) {
		do {
			this->conSole.gotoxy(35, 7);
			std::cout << "+--------------------------------------------+";
			this->conSole.gotoxy(35, 8);
			std::cout << "|                   Register                 |";
			this->conSole.gotoxy(35, 9);
			std::cout << "+--------------------------------------------+";
			this->conSole.gotoxy(35, 10);
			std::cout << "| Username:                                  |";
			this->conSole.gotoxy(35, 11);
			std::cout << "| Password:                                  |";
			this->conSole.gotoxy(35, 12);
			std::cout << "| ID Banking:                                |";
			this->conSole.gotoxy(35, 13);
			std::cout << "+--------------------------------------------+";
			this->conSole.gotoxy(35, 15); std::cout << "(Username is \'0\' to \'9\' and \'a\' to \'z\')\n";
			this->conSole.gotoxy(35, 16); std::cout << "(ID banking (10 numbers) include: \'0\' to \'9\')";
			this->conSole.gotoxy(47, 10);
			cin.getline(clientA.username, 100);
			this->conSole.gotoxy(47, 11);
			cin.getline(clientA.strpass, 100);
			this->conSole.gotoxy(49, 12);
			cin.getline(clientA.idBanking, 11);
			if (this->registerValid(clientA) == 0) {
				this->conSole.gotoxy(35, 18);
				system("pause");
				system("cls");
			}
		} while (this->registerValid(clientA) == 0);
		this->conSole.gotoxy(0, 0);
		this->conSole.gotoxy(35, 17);
		std::cout << "Register Successfully\n";
		this->conSole.gotoxy(35, 18);
		system("pause");
	}

	void accountLogin();
};

class date
{
public:
	int d, m, y;
};

extern user clientA;
extern vector <thread> threadimage;

void accountRegister();
void booking(int connector);
void lookup(int connector);
void menuClient(int connector);
void recv_image(int socket);
void show_image(cv::Mat image);

int date_larger_than(date date1, date date2);
bool kiem_tra_ngay_thang_nam(date date);
bool kiem_tra_nam_nhuan(int y);
void string_to_char(string t, char*& s);