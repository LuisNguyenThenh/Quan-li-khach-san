    // pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"
#include "framework.h"

// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.


bool Server::loginValid(user clientA) {
    //for (int i = 0; i < 3; i++) {
    //    if (database[i].username == clientA.username) {
    //        for (int k = 0; k < clientA.strpass.length(); k++) {
    //            if (database[i].strpass[k] != clientA.strpass[k])
    //                return 0;
    //        }
    //        return 1;
    //    }
    //}
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
	user* s = new user;
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
                if (this->loginValid(client[j])) {
                    flag = 1; // gui 1 xac nhan dang nhap thanh cong 
                    sockClient[j].Send((char*)&flag, sizeof(int), 0);
                }
                else {
                    flag = 0; // gui 0 dang nhap that bai.
                    sockClient[j].Send((char*)&flag, sizeof(int), 0);
                }
                // nhan flag = 1 dang nhap thanh cong
                sockClient[j].Receive((char*)&flag, sizeof(int), 0);
                if (flag == 1) {
                    getRequirefromMenu(sockClient[i]);
                    break;
                }
                // tien hanh kiem tra lai tai client thu i
                else i = j;
            }
        }
    }
}

void Hotel::Load_info_hotel(ifstream& fin)
{
    char c[2];
    fin.getline(c, 1);

    fin.getline(name, 199);
    
    fin.getline(decription_Standard_room, 199);
    fin.getline(decription_Superior_room, 199);
    fin.getline(decription_Deluxe_room, 199);
    fin.getline(decription_Suite_room, 199);

    fin >> price_Standard_room;
    fin >> price_Superior_room;
    fin >> price_Deluxe_room;
    fin >> price_Suite_room;

    fin >> number_Standard_room;
    fin >> number_Superior_room;
    fin >> number_Deluxe_room;
    fin >> number_Suite_room;

    //TEST 

    //cout << name << endl;

    //cout << decription_Standard_room << endl;
    //cout << decription_Superior_room << endl;
    //cout << decription_Deluxe_room << endl;
    //cout << decription_Suite_room << endl;

    //cout << price_Standard_room << endl;
    //cout << price_Superior_room << endl;
    //cout << price_Deluxe_room << endl;
    //cout << price_Suite_room << endl;

    //cout << number_Standard_room_available << endl;
    //cout << number_Superior_room_available << endl;
    //cout << number_Deluxe_room_available << endl;
    //cout << number_Suite_room_available << endl;
    return;
}

iii Hotel::Number_available_room_of_each_kind_on_date(date date1, date date2)
{
    int number_Standard_room_available = number_Standard_room;
    int number_Superior_room_available = number_Superior_room;
    int number_Deluxe_room_available = number_Deluxe_room;
    int number_Suite_room_available = number_Suite_room;
    for (customer* p = list_customer.head; p; p = p->next)
    {
        bool date1_internal = (date_larger_than(date1, p->date_in) >= 0) & (date_larger_than(date1, p->date_out) <= 0);
        bool date2_internal = (date_larger_than(date2, p->date_in) >= 0) & (date_larger_than(date2, p->date_out) <= 0);
        bool date_in_and_date_out_internal = (date_larger_than(date1, p->date_in) <= 0) & (date_larger_than(date2, p->date_out) >= 0);
        if (date1_internal || date2_internal || date_in_and_date_out_internal)
        {
            if (p->room == "Standard")
            {
                number_Standard_room_available--;
            }
            if (p->room == "Superior")
            {
                number_Superior_room_available--;
            }
            if (p->room == "Deluxe")
            {
                number_Deluxe_room_available--;
            }
            if (p->room == "Suite")
            {
                number_Suite_room_available--;
            }
        }
    }
    return iii(ii(number_Standard_room_available, number_Superior_room_available), ii(number_Deluxe_room_available, number_Suite_room_available));
}



int Hotel::Number_room_available(date date1, date date2)
{
    iii number_kinds_of_room = Number_available_room_of_each_kind_on_date(date1, date2);

    int number_Standard_room_available = number_kinds_of_room.first.first;
    int number_Superior_room_available = number_kinds_of_room.first.second;
    int number_Deluxe_room_available = number_kinds_of_room.second.first;
    int number_Suite_room_available = number_kinds_of_room.second.second;


    int total_room_available = 0;
    total_room_available += number_Standard_room_available;
    total_room_available += number_Superior_room_available;
    total_room_available += number_Deluxe_room_available;
    total_room_available += number_Suite_room_available;
    return total_room_available;
}

char* Hotel::Get_info_hotel(date date1, date date2)
{    
    //int number_Superior_room_available;
    //int number_Deluxe_room_available;
    //int number_Suite_room_available;

    //double price_Standard_room;
    //double price_Superior_room;
    //double price_Deluxe_room;
    //double price_Suite_room;

    iii number_kinds_of_room = Number_available_room_of_each_kind_on_date(date1, date2);

    int number_Standard_room_available = number_kinds_of_room.first.first;
    int number_Superior_room_available = number_kinds_of_room.first.second;
    int number_Deluxe_room_available = number_kinds_of_room.second.first;
    int number_Suite_room_available = number_kinds_of_room.second.second;


    int count = 1;
    string tmp;
    if (number_Standard_room_available > 0)
    {
        string num = int_to_string(count);
        tmp = tmp + num + ".\n";
        
        tmp = tmp + string("Number Standard room available: ") + int_to_string(number_Standard_room_available) + "\n";
        tmp = tmp + string("Price Standard room: ") + double_to_string(price_Standard_room) + " USD \n\n";
        count++;
    }

    if (number_Superior_room_available > 0)
    {
        string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + string("Number Superior room available: ") + int_to_string(number_Superior_room_available) + "\n";
        tmp = tmp + string("Price Superior room: ") + double_to_string(price_Superior_room) + " USD \n\n";
        count++;
    }

    if (number_Deluxe_room_available > 0)
    {
        string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + string("Number Deluxe room available: ") + int_to_string(number_Deluxe_room_available) + "\n";
        tmp = tmp + string("Price Deluxe room: ") + double_to_string(price_Deluxe_room) + " USD \n\n";
        count++;
    }


    if (number_Suite_room_available > 0)
    {
        string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + string("Number Suite room available: ") + int_to_string(number_Suite_room_available) + "\n";
        tmp = tmp + string("Price Suite room: ") + double_to_string(price_Suite_room) + " USD \n\n";
        count++;
    }
    char* s;
    string_to_char(tmp, s);
    return s;
}

int Hotel::Number_room_available(date date1, date date2)
{
    iii number_kinds_of_room = Number_available_room_of_each_kind_on_date(date1, date2);

    int number_Standard_room_available = number_kinds_of_room.first.first;
    int number_Superior_room_available = number_kinds_of_room.first.second;
    int number_Deluxe_room_available = number_kinds_of_room.second.first;
    int number_Suite_room_available = number_kinds_of_room.second.second;

    int count = 0;
    if (number_Standard_room_available > 0)
    {
        count++;
    }
    if (number_Superior_room_available > 0)
    {
        count++;
    }
    if (number_Deluxe_room_available > 0)
    {
        count++;
    }
    if (number_Suite_room_available > 0)
    {
        count++;
    }
    return count;
}

//Request 4
