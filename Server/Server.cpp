// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;


////TESTING
//void gotoxy(int x, int y)
//{
//    static HANDLE h = NULL;
//    if (!h)
//        h = GetStdHandle(STD_OUTPUT_HANDLE);
//    COORD c = { x, y };
//    SetConsoleCursorPosition(h, c);
//}
//int whereX()
//{
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
//        return csbi.dwCursorPosition.X;
//    return -1;
//}
////========= lấy tọa độ y của con trỏ hiện tại =======
//int whereY()
//{
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
//        return csbi.dwCursorPosition.Y;
//    return -1;
//}

//TESTING
vector <thread> threadimages;
vector <thread> threadclient;
vector <CSocket* > socketclients;
Hotel* list_hotel;
CSocket cserver;
int nClient = 0;
int bESCPressed = 0;
void print_image(const char* s)
{
    Mat image;
    image = imread("hotel.jpg");

    imshow("Hotel", image);
    waitKey(0);
    return;
}

int main()
{
    vector <thread> threads;
    // Sleep(10000);
    Load_data_hotel();
    cout << "Loaded data successfully!" << endl;
    //threads.push_back(thread(print_image, "hotel.jpg"));
    //threads[0].join();
    //Sleep(1000);
    //thread_image.push_back(thread(print_image, "hotel.jpg"));


    int nRetCode = 0;
    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {

            AfxSocketInit(NULL);

            Server server = Server();
            // return 0;
             // TODO: code your application's behavior here.
             //Server k = Server();

        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
