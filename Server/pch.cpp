// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"
#include "framework.h"
// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.


bool Server::loginValid(user clientA, user* database) {
    for (int i = 0; i < 3; i++) {
        if (database[i].username == clientA.username) {
            for (int k = 0; k < clientA.strpass.length(); k++) {
                if (database[i].strpass[k] != clientA.strpass[k])
                    return 0;
            }
            return 1;
        }
    }
    return 1;
}
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
    user* s = Getuser();
    CSocket* sockClient = new CSocket[nClient];
    for (int i = 0; i < nClient; i++) {
        server.Accept(sockClient[i]);
        cout << "Connected to client " << i + 1 << "/" << nClient << endl;
        sockClient[i].Send((char*)&i, sizeof(int), 0);
    }
    int q; 
    
    int i = 0;
    for (int j = i; j < nClient; j++) {
        sockClient[j].Receive((char*)&q, sizeof(int), 0);
        user* client = new user[nClient];
        // dang ki luu do file code o day duoi cai if
        if (q == 0) {
            int p;
            sockClient[j].Receive((char*)&p, sizeof(int), 0);
            sockClient[j].Receive(&client[j].username, sizeof(p), 0);
            int q;
            sockClient[j].Receive((char*)&q, sizeof(int), 0);
            sockClient[j].Receive(&client[j].strpass, sizeof(q), 0);
        }
        if (q == 1) {
            // ktra dang nhap
            while (1) {
                // username 
                int p;
                sockClient[j].Receive((char*)&p, sizeof(int), 0);
                sockClient[j].Receive(&client[j].username, sizeof(p), 0);
                //password
                int q;
                sockClient[j].Receive((char*)&q, sizeof(int), 0);
                sockClient[j].Receive(&client[j].strpass, sizeof(q), 0);
                int flag;
                if (this->loginValid(client[j], s)) {
                    flag = 1; // gui 1 xac nhan dang nhap thanh cong 
                    sockClient[j].Send((char*)&flag, sizeof(int), 0);
                }
                else {
                    flag = 0; // gui 0 dang nhap that bai.
                    sockClient[j].Send((char*)&flag, sizeof(int), 0);
                }
                // nhan flag = 1 dang nhap thanh cong
                sockClient[j].Receive((char*)&flag, sizeof(int), 0);
                if (flag == 1)
                    break;
                // tien hanh kiem tra lai tai client thu i
                else i = j;
            }
        }
    }
}