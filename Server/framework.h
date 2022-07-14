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

#ifdef __WIN32__
WORD versionWanted = MAKEWORD(1, 1);
WSADATA wsaData;
WSAStartup(versionWanted, &wsaData);
#endif
#include <algorithm>
#include <ctime>
//#include "json.hpp"
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <fstream>
#pragma comment(lib,"graphics.lib")
#include <sstream>
#include <iomanip>
#include <thread>
#include <vector>
#include <windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "afxsock.h"
#define fi first
#define se second
//using json = nlohmann::json;
using namespace std;
using namespace cv;

typedef pair <int, int> ii;
typedef pair <ii, ii> iii;

// Global variable




struct user {
    string username, strpass, idBanking;
};

class Server {
public:

    Server();

    //check login
    bool loginValid(user clientA);
};

struct date
{
    int d, m, y;
};

class customer
{
public:
    char* user_name;
    date date_in, date_out;
    int kind_room;
    char* note;
    customer* next = NULL;
    customer* pre = NULL;
};

class link_list
{
public:
    int number_customer = 0;
    customer* head = NULL;
    customer* tail = NULL;
    bool is_empty()
    {
        if (this->head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    customer* find(char* s)
    {
        if (this == NULL) return NULL;
        for (customer* p = this->head; p; p = p->next)
        {
            if (p->user_name == s)
            {
                return p;
            }
        }
        return NULL;
    }
    void add(customer* p)
    {
        number_customer++;
        if (this->head == NULL)
        {
            this->head = this->tail = p;
            return;
        }
        else
        {
            this->tail->next = p;
            p->pre = this->tail;
            this->tail = p;
            return;
        }
    }
    void remove(char* s)
    {
        number_customer--;
        customer* x = NULL;
        for (customer* p = this->head; p; p = p->next)
        {
            if (p->user_name == s)
            {
                x = p;
                break;
            }
        }
        if (x == NULL)
        {
            return;
        }
        else
        {
            if (x == this->head)
            {
                if (this->head != this->tail)
                {
                    this->head = this->head->next;
                    this->head->pre = NULL;
                }
                else
                {
                    this->head = NULL;
                    this->tail = NULL;
                }
                delete x;
                return;
            }
            if (x == this->tail)
            {
                this->tail = this->tail->pre;
                this->tail->next = NULL;
                delete x;
                return;
            }
            else
            {
                x->next->pre = x->pre;
                x->pre->next = x->next;
                delete x;
                x = NULL;
                return;
            }


        }
    }
};
class Hotel
{
public:
    // First hotel will manage 
    int num_hotel = 0;

    link_list list_booking;

    char* name = new char[200];

    int number_Standard_room;
    int number_Superior_room;
    int number_Deluxe_room;
    int number_Suite_room;

    double price_Standard_room;
    double price_Superior_room;
    double price_Deluxe_room;
    double price_Suite_room;

    char* decription_Standard_room = new char[200];
    char* decription_Superior_room = new char[200];
    char* decription_Deluxe_room = new char[200];
    char* decription_Suite_room = new char[200];


    void Add_customer(customer* p);
    void Load_info_hotel(ifstream& fin);
    int Number_room_available(date date1, date date2);
    char* Get_info_hotel(date date1, date date2);
    int Number_kind_of_room_available(date date1, date date2);
    double Price_of_kind_room(int kind);
    iii Number_available_room_of_each_kind_on_date(date date1, date date2);

    bool Is_kind_of_room_available_on_date(date date1, date date2, int kind);

};
extern vector <thread> threadimages;
extern vector <thread> threadclient;
extern vector <CSocket* > socketclients;

extern Hotel* list_hotel;
extern int nClient;
extern int bESCPressed;
extern CSocket cserver;


void Load_data_hotel();
string int_to_string(int a);
string double_to_string(double a);
void string_to_char(string t, char*& s);
void copy_string(char*& s, char*& t);
Hotel* get_hotel_from_list(char* name_hotel);
void getRequirefromMenu(CSocket& sockClient);
void getRequirefromLookup(CSocket& sockClient);
void solve_client(CSocket* client1);

bool kiem_tra_ngay_thang_nam(int day, int m, int y);
int date_larger_than(date date1, date date2);
int distance_time(date date1, date date2);
