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
#include <algorithm>
#include <ctime>
//#include "json.hpp"
#include <cstring>
#include <stdio.h>
#include <string.h>
#include<fstream>
#include <sstream>
#include <thread>
#include <vector>
#include "afxsock.h"
//using json = nlohmann::json;
using namespace std;

struct user {
	string username, strpass, idBanking;
};

class Server {
public:
	Server();

	//check login
	bool loginValid(user clientA);
};
class Hotel
{
public:
	int num_hotel = 0;

	char* name = new char[200];

	int number_Standard_room_available;
	int number_Superior_room_available;
	int number_Deluxe_room_available;
	int number_Suite_room_available;

	double price_Standard_room;
	double price_Superior_room;
	double price_Deluxe_room;
	double price_Suite_room;

	char* decription_Standard_room = new char[200];
	char* decription_Superior_room = new char[200];
	char* decription_Deluxe_room = new char[200];
	char* decription_Suite_room = new char[200];

	void Load_info_hotel(ifstream &fin);
	int Number_room_available();
	char* Get_info_hotel();
	int Number_kind_of_room_available();
	void Decrease_room(int num);
};
void Load_data_hotel(Hotel*& list_hotel);
string int_to_string(int a);
string double_to_string(double a);
void string_to_char(string t, char*& s);

Hotel* get_hotel_from_list(char* name_hotel, Hotel*& list_hotel);
void getRequirefromMenu(CSocket& sockClient);
void getRequirefromLookup(CSocket& sockClient);