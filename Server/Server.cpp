// test_new socket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "framework.h"
#include "pch.h"
#pragma comment (lib, "ws2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;


std::vector <std::thread> threadimages;
std::vector <std::thread> threadclient;
std::vector <int> idsocketclient;
Hotel* list_hotel;
int nClient = 0;
int bESCPressed;
int server;
sockaddr_in server_addr;
int main()
{

    //std::cout << double_to_string(31.46566);
    int a = 0;
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
            WSADATA wsData;
            WORD ver = MAKEWORD(2, 2);

            int wsOk = WSAStartup(ver, &wsData);
            if (wsOk != 0)
            {
                // cerr << "Can't Initialize winsock! Quitting" << std::endl;
            }
            Load_data_hotel();
            std::cout << "Load data successfully!" << std::endl;

            std::cout << "Start" << std::endl;
            int n = 2;

            //Mat image;

            Server solve_server = Server();

            WSACleanup();
            // TODO: code your application's behavior here.
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
