// pch.cpp: source file corresponding to the pre-compiled header
#pragma once 
#include "framework.h"
#include "pch.h"
#include <conio.h>



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


void solve_client(CSocket* sockclient)
{
    CSocket* sockClient = (CSocket*)sockclient;
    cout << nClient << endl;
    sockClient->Send((char*)&nClient, sizeof(int), 0);
    int q = 0;
    sockClient->Receive((char*)&q, sizeof(int), 0);
    // user* s = new user;
    // bool check = true;
    // //sockClient;
    // //
    // //
    // nClient++;
    // cout << "Connected to client " << nClient << endl;
    // sockClient->Send((char*)&nClient, sizeof(int), 0);
    // int q=0;
    // 
    // int i = 0;
    //// sockClient->Receive((char*)&q, sizeof(int), 0);
    //// return;
    // user client;
    // // dang ki luu do file code o day duoi cai if
    // if (q == 0)
    // {
    //     int p;
    //     sockClient->Receive((char*)&p, sizeof(int), 0);
    //   //  sockClient->Receive(&client.username, sizeof(p), 0);
    //     int q;
    //   //  sockClient->Receive((char*)&q, sizeof(int), 0);
    //   //  sockClient->Receive(&client.strpass, sizeof(q), 0);
    // }
    // if (q == 1)
    // {
    //     // ktra dang nhap
    //     while (1) {
    //         // username 
    //         int p;
    //         sockClient->Receive((char*)&p, sizeof(int), 0);
    //         sockClient->Receive(&client.username, sizeof(p), 0);
    //         //password
    //         int q;
    //         sockClient->Receive((char*)&q, sizeof(int), 0);
    //         sockClient->Receive(&client.strpass, sizeof(q), 0);
    //         int flag;
    //         //DANG TEST CHO NAY
    //        // if (server.loginValid(client))
    //         if (1)
    //         {
    //             flag = 1; // gui 1 xac nhan dang nhap thanh cong 
    //             sockClient->Send((char*)&flag, sizeof(int), 0);
    //         }
    //         else
    //         {
    //             flag = 0; // gui 0 dang nhap that bai.
    //             sockClient->Send((char*)&flag, sizeof(int), 0);
    //         }
    //         // nhan flag = 1 dang nhap thanh cong
    //         sockClient->Receive((char*)&flag, sizeof(int), 0);
    //         if (flag == 1) {
    //             getRequirefromMenu(sockClient);
    //             break;
    //         }
    //         // tien hanh kiem tra lai tai client thu i
    //     }
    // }
    return;
}
Server::Server()
{

    const unsigned int port = 1234; // port server

    cout << "Waiting for client access..." << endl;
    int n = 2;
    AfxSocketInit(NULL);
    cserver.Create(1234);
    cserver.Listen(5);


    while (1)
    {
        CSocket* new_client = new CSocket;
        //    // cout << "OKEE" << endl;
        cserver.Accept(*new_client);

        thread first(solve_client, new_client);
    }
    // thread Exit(Press_ESC);

    //// pthread_create()
    // while (bESCPressed == 0)
    // {
    //     CSocket* new_client=new CSocket;
    //    // cout << "OKEE" << endl;
    //     cserver.Accept(*new_client);
    //     
    //     if (bESCPressed == 1) break;
    //     

    //    // p_client->Send((char*)&nClient, sizeof(int), 0);
    //     socketclients.push_back(new_client);
    //    threadclient.push_back(thread(solve_client, new_client));
    // }
    // 
    // for (int i = 0; i < threadclient.size(); i++)
    // {
    //     threadclient[i].join();
    // }
    // for (int i = 0; i < socketclients.size(); i++)
    // {
    //     socketclients[i]->Close();
    // }



    // while (1);
    return;
}


void Hotel::Load_info_hotel(ifstream& fin)
{
    char c[2];

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

    int number_customer;
    fin >> number_customer;
    fin.getline(c, 1);

    for (int i = 0; i < number_customer; i++)
    {
        customer* p = new customer;
        p->user_name = new char[200];
        p->note = new char[200];
        fin.getline(p->user_name, 199);

        fin >> p->date_in.d;
        fin >> p->date_in.m;
        fin >> p->date_in.y;
        fin >> p->date_out.d;
        fin >> p->date_out.m;
        fin >> p->date_out.y;
        fin >> p->kind_room;

        fin.getline(c, 1);
        fin.getline(p->note, 199);

        Add_customer(p);

        //Test
        //cout << p->user_name << endl;
        //cout << p->date_in.d << endl;
        //cout << p->date_in.m << endl;
        //cout << p->date_in.y << endl;
        //cout << p->date_out.d << endl;
        //cout << p->date_out.m << endl;
        //cout << p->date_out.y << endl;
        //cout << p->room << endl;
        //cout << p->note << endl;
    }

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
    //cout << number_Standard_room << endl;
    //cout << number_Superior_room<< endl;
    //cout << number_Deluxe_room << endl;
    //cout << number_Suite_room << endl;

    return;
}

iii Hotel::Number_available_room_of_each_kind_on_date(date date1, date date2)
{
    int number_Standard_room_available = number_Standard_room;
    int number_Superior_room_available = number_Superior_room;
    int number_Deluxe_room_available = number_Deluxe_room;
    int number_Suite_room_available = number_Suite_room;
    for (customer* p = list_booking.head; p; p = p->next)
    {
        bool date1_internal = (date_larger_than(date1, p->date_in) >= 0) & (date_larger_than(date1, p->date_out) <= 0);
        bool date2_internal = (date_larger_than(date2, p->date_in) >= 0) & (date_larger_than(date2, p->date_out) <= 0);
        bool date_in_and_date_out_internal = (date_larger_than(date1, p->date_in) <= 0) & (date_larger_than(date2, p->date_out) >= 0);
        if (date1_internal || date2_internal || date_in_and_date_out_internal)
        {
            if (p->kind_room == 1)
            {
                number_Standard_room_available--;
            }
            if (p->kind_room == 2)
            {
                number_Superior_room_available--;
            }
            if (p->kind_room == 3)
            {
                number_Deluxe_room_available--;
            }
            if (p->kind_room == 4)
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

int Hotel::Number_kind_of_room_available(date date1, date date2)
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

void Hotel::Add_customer(customer* p)
{
    list_booking.add(p);
    return;
}
bool Hotel::Is_kind_of_room_available_on_date(date date1, date date2, int kind)
{
    iii number_kinds_of_room = Number_available_room_of_each_kind_on_date(date1, date2);

    int number_Standard_room_available = number_kinds_of_room.first.first;
    int number_Superior_room_available = number_kinds_of_room.first.second;
    int number_Deluxe_room_available = number_kinds_of_room.second.first;
    int number_Suite_room_available = number_kinds_of_room.second.second;
    if (kind == 1)
    {
        return (number_Standard_room_available > 0);
    }
    if (kind == 2)
    {
        return (number_Superior_room_available > 0);
    }
    if (kind == 3)
    {
        return (number_Deluxe_room_available > 0);
    }
    if (kind == 4)
    {
        return (number_Suite_room_available > 0);
    }

}

double Hotel::Price_of_kind_room(int kind)
{
    if (kind == 1)
    {
        return price_Standard_room;
    }
    if (kind == 2)
    {
        return price_Superior_room;
    }
    if (kind == 3)
    {
        return price_Deluxe_room;
    }
    if (kind == 4)
    {
        return price_Suite_room;
    }
}
//Request 4
