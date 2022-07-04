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
                //cout << "Connect successfully.\n";
                client a = client();
                char* tmp;
                int lengthMsg;
  
                do {
                    int p = a.clientA.username.length();
                    int q = a.clientA.strpass.length();
                    clientsocket.Send(&p, sizeof(p), 0);
                    clientsocket.Send(&a.clientA.username, p, 0);
                    clientsocket.Send(&q, sizeof(q), 0);
                    clientsocket.Send(&a.clientA.strpass, q, 0);

                    // nhan so luong byte va tin nhan tu server
                    clientsocket.Receive((char*)&lengthMsg, sizeof(int), 0);
                    tmp = new char[lengthMsg + 1];
                    clientsocket.Receive((char*)tmp, lengthMsg, 0);
                    tmp[lengthMsg] = '\0';
                    
                    // xac nhan dong ket noi.
                    if (tmp == "oke") {
                        delete tmp;
                        break;
                    }

                    cout << *tmp << endl;
                    delete tmp;
                    
                } while (1);

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
