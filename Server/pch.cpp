// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"
#include "framework.h"
// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.

Server::Server() {
    CSocket server;
    const unsigned int port = 1234; // port server
    AfxSocketInit(NULL);

    server.Create(port);
    server.Listen(5); // maximum queue = 5

    // so luong socket ket noi den server
    int nClient = 0;
    cout << "Enter the number of clients: ";
    cin >> nClient;

    CSocket* sockClient = new CSocket[nClient];
    for (int i = 0; i < nClient; i++) {
        server.Accept(sockClient[i]);
        cout << "Connected to client " << i + 1 << "/" << nClient << endl;
        sockClient[i].Send((char*)&i, sizeof(int), 0);
    }

    user* client = new user[nClient];
    // ktra dang nhap
    // username 
    for (int i = 0; i < nClient; i++) {
        int p;
        sockClient[i].Receive((char*)&p, sizeof(int), 0);
        sockClient[i].Receive(&client[i].username, sizeof(p), 0);
    }
    //password
    for (int i = 0; i < nClient; i++) {
        int q;
        sockClient[i].Receive((char*)&q, sizeof(int), 0);
        sockClient[i].Receive(&client[i].strpass, sizeof(q), 0);
    }

    for (int i = 0; i < nClient; i++) {
        if (loginValid(client[i])) {
            int flag = 1; // gui 1 xac nhan dang nhap thanh cong 
            sockClient[i].Send((char*)&flag, sizeof(int), 0);
        }
        else {
            int flag = 0; // gui 0 dang nhap that bai.
            sockClient[i].Send((char*)&flag, sizeof(int), 0);
        }
    }
}

bool Server::loginValid(user clientA) {
    user s[3];
    s[0].username = "thanh";
    s[1].username = "phuoc";
    s[2].username = "thai";
    s[0].strpass = "thanh123";
    s[1].strpass = "thanh123";
    s[2].strpass = "thanh123";

    for (int i = 0; i < 3; i++) {
        if (s[i].username == clientA.username) {
            for (int k = 0; k < clientA.strpass.length(); k++) {
                if (s[i].strpass[k] != clientA.strpass[k])
                    return 0;
            }
            return 1;
        }
    }
    return 1;
}