// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Client1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

user clientA;
vector <thread> threadimage;
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
                std::cout << "Can't connect to server.\n";
                return 0;
            }
            //std::string ipAddress = "127.0.0.1";			// IP Address of the server
            //int port = 1234;						// Listening port # on the server

            //// Initialize WinSock
            //WSAData data;
            //WORD ver = MAKEWORD(2, 2);
            //int wsResult = WSAStartup(ver, &data);
            //if (wsResult != 0)
            //{
            //    cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
            //    return 0;
            //}

            //// Create socket
            //SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
            //if (sock == INVALID_SOCKET)
            //{
            //    cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
            //    WSACleanup();
            //    return 0;
            //}

            //// Fill in a hint structure
            //sockaddr_in hint;
            //hint.sin_family = AF_INET;
            //hint.sin_port = htons(port);
            //inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

            //// Connect to server
            //int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
            //if (connResult == SOCKET_ERROR)
            //{
            //    cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
            //    closesocket(sock);
            //    WSACleanup();
            //    return 0;
            //}

            //// Do-while loop to send and receive data
            //char buf[4096];
            //std::string userInput;

            //do
            //{
            //    //char buf[100];
            //    //recv(sock, buf, 100, 0);
            //    //cout << buf << endl;
            //    // Prompt the user for some text
            //    std::cout << "> ";
            //    getline(cin, userInput);

            //    if (userInput.size() > 0)		// Make sure the user has typed in something
            //    {
            //        // Send the text
            //        int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
            //        if (sendResult != SOCKET_ERROR)
            //        {
            //            // Wait for response
            //            ZeroMemory(buf, 4096);
            //            int bytesReceived = recv(sock, buf, 4096, 0);
            //            if (bytesReceived > 0)
            //            {
            //                // Echo response to console
            //                std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
            //            }
            //        }
            //    }

            //} while (userInput.size() > 0);

            //// Gracefully close down everything
            //closesocket(sock);
            //WSACleanup();



            int clientsocket = -1;
            sockaddr_in server_addr;
            time_t ticks;

            clientsocket = socket(AF_INET, SOCK_STREAM, 0);

            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(1234);

            // Convert IPv4 and IPv6 addresses from text to binary
            // form
            if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
            {
                printf("\nInvalid address/ Address not supported \n");
                return -1;
            }

            bind(clientsocket, (sockaddr*)&server_addr, sizeof(server_addr));

            if (connect(clientsocket, (sockaddr*)&server_addr, sizeof(server_addr)) == 0)
            {
                //char a[1000]="Hello!";
                //int size = strlen(a);
                //cout << size << endl;
                //cout << a << endl;
                //send(clientsocket, (char*)&size, sizeof(int), 0);
                //send(clientsocket, (char*)&a, size, 0);

                bool check_connected = false;
                recv(clientsocket, (char*)&check_connected, sizeof(bool), 0);
                if (check_connected)
                {
                    std::cout << "Connect successfully.\n";
                }
                int number;

                recv(clientsocket, (char*)&number, sizeof(int), 0);
                //std::cout << number << std::endl;
                // thong bao da co account hay ch? 
                client a; consoleGraphic Graphic;
                Graphic.gotoxy(35, 10);
                std::cout << "Did you have any account? (Y or N)\n";
                char c = _getch();
                int flag = 1;
                // tien hanh dki tai khoan
                if (c == 'n') {
                    system("cls");
                    flag = 0;
                    send(clientsocket, (char*)&flag, sizeof(int), 0);
                    a.accountRegister(clientA);
                    int p = strlen(clientA.username),
                        q = strlen(clientA.strpass),
                        r = strlen(clientA.idBanking);
                    send(clientsocket, (char*)&p, sizeof(int), 0);
                    send(clientsocket, (char*)clientA.username, p, 0);
                    std::cout << clientA.username << std::endl;
                    send(clientsocket, (char*)&q, sizeof(int), 0);
                    send(clientsocket, (char*)clientA.strpass, q, 0);
                    std::cout << clientA.strpass << std::endl;
                    send(clientsocket, (char*)&r, sizeof(r), 0);
                    send(clientsocket, (char*)clientA.idBanking, r, 0);
                    std::cout << clientA.idBanking << std::endl;
                    system("cls");
                    int tmp = 1;
                    send(clientsocket, (char*)&tmp, sizeof(int), 0);
                    // dki r thi dang nhap th xD
                    a.accountLogin(); // cho nay nhin` phen` qua :D
                    while (1) {
                        int p = strlen(clientA.username),
                            p2 = strlen(clientA.strpass);
                        /* cout << p << endl;
                         cout << a.clientA.username << endl;
                         cout << q << endl;
                         cout << a.clientA.strpass << endl;*/
                         //clientA.username = clientA.username; //bo truong clientA trong client di do k co td j het :D
                        send(clientsocket, (char*)&p, sizeof(int), 0);
                        send(clientsocket, (char*)clientA.username, p, 0);
                        send(clientsocket, (char*)&p2, sizeof(int), 0);
                        send(clientsocket, (char*)clientA.strpass, p2, 0);

                        recv(clientsocket, (char*)&flag, sizeof(int), 0);
                        if (flag == 1) {
                            system("cls");
                            Graphic.gotoxy(45, 6);
                            std::cout << "Login Successfully.\n";
                            send(clientsocket, (char*)&flag, sizeof(int), 0);
                            menuClient(clientsocket);
                            break;
                        }
                        else {
                            send(clientsocket, (char*)&flag, sizeof(int), 0);
                            std::cout << "Username or Password does not correct.\n";
                        }
                    }
                }
                // tien hanh dang nhhap
                else {
                    send(clientsocket, (char*)&flag, sizeof(int), 0);
                    a.accountLogin();
                    while (1) {
                        int p = strlen(clientA.username),
                            p2 = strlen(clientA.strpass);
                        /* cout << p << endl;
                         cout << a.clientA.username << endl;
                         cout << q << endl;
                         cout << a.clientA.strpass << endl;*/
                         //clientA.username = clientA.username; //bo truong clientA trong client di do k co td j het :D
                        send(clientsocket, (char*)&p, sizeof(int), 0);
                        send(clientsocket, (char*)clientA.username, p, 0);
                        send(clientsocket, (char*)&p2, sizeof(int), 0);
                        send(clientsocket, (char*)clientA.strpass, p2, 0);
                        recv(clientsocket, (char*)&flag, sizeof(int), 0);
                        if (flag == 1) {
                            system("cls");
                            Graphic.gotoxy(45, 6);
                            std::cout << "Login Successfully.\n";
                            send(clientsocket, (char*)&flag, sizeof(int), 0);
                            menuClient(clientsocket);
                            break;
                        }
                        else {
                            send(clientsocket, (char*)&flag, sizeof(int), 0);
                            std::cout << "Username or Password does not correct.\n";
                        }
                    }
                }
            }
            closesocket(clientsocket);
            WSACleanup();
            for (int i = 0; i < threadimage.size(); i++)
            {
                threadimage[i].join();
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
