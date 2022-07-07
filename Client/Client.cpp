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
                int number;
                clientsocket.Receive((char*)&number, sizeof(int), 0);
                user clientA;
                // thong bao da co account hay ch? 
                cout << "Did you have any account ? (Y or N)\n";
                char c = _getch();
                int flag = 1;
                // tien hanh dki tai khoan
                if (c == 'n') {
                    system("cls");
                    flag = 0;
                    clientsocket.Send((char*)&flag, sizeof(int), 0);
                    accountRegister(clientA);
                    int p = clientA.username.length(),
                        q = clientA.strpass.length();
                    clientsocket.Send((char*)&p, sizeof(int), 0);
                    clientsocket.Send(&clientA.username, sizeof(p), 0);
                    clientsocket.Send((char*)&q, sizeof(int), 0);
                    clientsocket.Send(&clientA.strpass, sizeof(q), 0);
                }
                // tien hanh dang nhhap
                else {
                    clientsocket.Send((char*)&flag, sizeof(int), 0);
                    while (1) {
                        client a = client();
                        int p = a.clientA.username.length();
                        int q = a.clientA.strpass.length();
                        clientsocket.Send((char*)&p, sizeof(int), 0);
                        clientsocket.Send(&a.clientA.username, sizeof(p), 0);
                        clientsocket.Send((char*)&q, sizeof(int), 0);
                        clientsocket.Send(&a.clientA.strpass, sizeof(q), 0);

                        clientsocket.Receive((char*)&flag, sizeof(int), 0);
                        if (flag == 1) {
                            cout << "Login Successfully.\n";
                            clientsocket.Send((char*)&flag, sizeof(int), 0);
                            break;
                        }
                        else {
                            clientsocket.Send((char*)&flag, sizeof(int), 0);
                            cout << "Username or Password does not correct.\n";
                        }
                    }
                    clientsocket.Close();
                }
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
