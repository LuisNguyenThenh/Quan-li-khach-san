// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
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
            // TODO: code your application's behavior here.
            if (!AfxSocketInit()) {
                cout << "Can't connect to server.\n";
                return 0;
            }
            CSocket clientsocket;
            clientsocket.Create();
            if (clientsocket.Connect(_T("127.0.0.1"), 1234) != 0) {
                cout << "Connect successfully.\n";
                client a = client();
                char* tmp = new char;
                int lengthMsg;
                int flag;

                while (1) {
                    int p = a.clientA.username.length();
                    int q = a.clientA.strpass.length();
                    clientsocket.Send((char*)&p, sizeof(int), 0);
                    clientsocket.Send(&a.clientA.username, sizeof(p), 0);
                    clientsocket.Send((char*)&q, sizeof(int), 0);
                    clientsocket.Send(&a.clientA.strpass, sizeof(q), 0);
                    
                    clientsocket.Receive((char*)&flag, sizeof(int), 0);
                    cout << flag;
                    break;
                    /*if (flag == 0) {
                        cout << "Username or Password does not correct.\n";
                    }
                    else {
                        cout << "Login successfully";
                        break;
                    }*/

                }
                clientsocket.Close();
            }
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
