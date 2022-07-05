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
            if (AfxSocketInit() == FALSE)
            {
                cout << "Khong the khoi tao Socket Libraray";
                return FALSE;
            }
            
            CSocket ServerSocket;
            
            if (ServerSocket.Create(1234, SOCK_STREAM, NULL) == 0)
            {
                cout << "Khoi tao that bai" << endl;
                cout << ServerSocket.GetLastError();
                return false;
            }
            else
            {
                cout << "Server khoi tao thanh cong!" << endl;
                if (ServerSocket.Listen(1) == 0)
                {
                    cout << "Port nay khong the nghe duoc" << endl;
                    ServerSocket.Close();
                    return false;
                }
            }
            CSocket Connector;
            // Tao mot socket de duy tri su ket noi giua va trao doi du lieu
            if (ServerSocket.Accept(Connector))
            {
                cout << "Da co client ket noi den!" << endl << endl;

                char ServerMsg[100];
                int MsgSize;
                char* ClientMsg;

                while (true)
                {
                    cout << "Server:";
                    cin.getline(ServerMsg, 100);
                    MsgSize = strlen(ServerMsg);
                    // Gui do dai cua thong diep 
                    ServerSocket.Send(&MsgSize, sizeof(int), 0);
                    // Gui di thong diep
                    ServerSocket.Send(ServerMsg, MsgSize, 0);


                    //Nhan do dai cua thong diep 
                    if (ServerSocket.Receive((char*)&MsgSize, sizeof(int), 0) != SOCKET_ERROR)
                    {
                        // Tao bo nho 
                        ClientMsg = new char[MsgSize + 1];

                        //Nhan thong diep
                        if (ServerSocket.Receive((char*)ClientMsg, MsgSize, 0) != SOCKET_ERROR)
                        {
                            ClientMsg[MsgSize] = '\0';

                            cout << "Client:" << ClientMsg << endl;
                        }
                        delete[] ClientMsg;
                    }
                    
                }

            }
            ServerSocket.Close();
            Connector.Close();
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
