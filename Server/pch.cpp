// pch.cpp: source file corresponding to the pre-compiled header
#pragma once 

#include "framework.h"
#include "pch.h"
#include <conio.h>



// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.

void solve_client(int sockClient, int order_client)
{
    user client;
    // dang ki luu do file code o day duoi cai if
    bool c = true;
    //Send flag
    send(sockClient, (char*)&c, sizeof(bool), 0);
    //Send numberous
    send(sockClient, (char*)&order_client, sizeof(int), 0);
    std::cout << "Connected with client " << order_client << std::endl;
    int q;
    recv(sockClient, (char*)&q, sizeof(int), 0);
    if (q == 0)
    {
        int tmp;
        do {
            int p;
            recv(sockClient, (char*)&p, sizeof(int), 0);
            std::cout << p;
            client.username = new char[p + 1];
            recv(sockClient, (char*)client.username, p, 0);
            client.username[p] = '\0';
            std::cout << client.username << std::endl;
            //password
            int k;
            recv(sockClient, (char*)&k, sizeof(int), 0);
            client.strpass = new char[k + 1];
            std::cout << k;
            recv(sockClient, (char*)client.strpass, k, 0);
            client.strpass[k] = '\0';
            std::cout << client.strpass << std::endl;
            //ID banking
            int r;
            recv(sockClient, (char*)&r, sizeof(int), 0);
            client.idBanking = new char[r + 1];
            recv(sockClient, (char*)client.idBanking, r, 0);
            std::cout << r;
            client.idBanking[r] = '\0';
            recv(sockClient, (char*)&tmp, sizeof(int), 0);
            std::cout << client.idBanking;
            std::cout << tmp;
            // tien hanh dang nhap sau khi dki
            if (tmp == 1) {
                int size_name;
                user clientB;
                recv(sockClient, (char*)&size_name, sizeof(int), 0);
                //std::cout << size_name;
                clientB.username = new char[size_name + 1];
                recv(sockClient, (char*)clientB.username, size_name, 0);
                clientB.username[size_name] = '\0';
                //std::cout << client.username << std::endl;
                //password
                int size_pass;
                recv(sockClient, (char*)&size_pass, sizeof(int), 0);
                clientB.strpass = new char[size_pass + 1];

                recv(sockClient, (char*)clientB.strpass, size_pass, 0);
                clientB.strpass[size_pass] = '\0';

                int flag;
                //DANG TEST CHO NAY
                //if (server.loginValid(client))
                if (1)
                {
                    flag = 1; // gui 1 xac nhan dang nhap thanh cong 
                    send(sockClient, (char*)&flag, sizeof(int), 0);
                }
                else
                {
                    flag = 0; // gui 0 dang nhap that bai.
                    send(sockClient, (char*)&flag, sizeof(int), 0);
                }
                // nhan flag = 1 dang nhap thanh cong
                recv(sockClient, (char*)&flag, sizeof(int), 0);
                if (flag == 1) {
                    getRequirefromMenu(sockClient);
                    break;
                }
            }
        } while (tmp != 1);
    }
    if (q == 1)
    {
        // ktra dang nhap
        while (1) {
            // username 
            int size_name;
            recv(sockClient, (char*)&size_name, sizeof(int), 0);
            //std::cout << size_name;
            client.username = new char[size_name + 1];
            recv(sockClient, (char*)client.username, size_name, 0);
            client.username[size_name] = '\0';
            //std::cout << client.username << std::endl;
            //password
            int size_pass;
            recv(sockClient, (char*)&size_pass, sizeof(int), 0);
            client.strpass = new char[size_pass + 1];

            recv(sockClient, (char*)client.strpass, size_pass, 0);
            client.strpass[size_pass] = '\0';
            //std::cout << client.strpass << std::endl;

            int flag;
            //DANG TEST CHO NAY
            //if (server.loginValid(client))
            if (1)
            {
                flag = 1; // gui 1 xac nhan dang nhap thanh cong 
                send(sockClient, (char*)&flag, sizeof(int), 0);
            }
            else
            {
                flag = 0; // gui 0 dang nhap that bai.
                send(sockClient, (char*)&flag, sizeof(int), 0);
            }
            // nhan flag = 1 dang nhap thanh cong
            recv(sockClient, (char*)&flag, sizeof(int), 0);
            if (flag == 1) {
                getRequirefromMenu(sockClient);
                break;
            }
            // tien hanh kiem tra lai tai client thu i
        }
        // }

    }

    std::cout << "Client " << order_client << " have done!" << std::endl;
    closesocket(sockClient);
    return;

}
Server::Server()
{
    const unsigned int port = 1234; // port server

    server = -1;
    server = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server, 10);
    int client_size = sizeof(sockaddr_in);

    std::cout << "Waiting for client access..." << std::endl;
    std::thread escape(Press_ESC);
    while (bESCPressed == 0)
    {
        sockaddr_in client_addr;
        int client_socket = accept(server, (sockaddr*)&client_addr, &client_size);
        if (client_socket != -1)
        {
            nClient++;
            idsocketclient.push_back(client_socket);
            threadclient.push_back(std::thread(solve_client, client_socket, nClient));
        }
    }
    escape.join();
    return;
}

void Press_ESC()
{
    bESCPressed = 0;
    do
    {
        bESCPressed = (_getch() == 27);
    } while (!bESCPressed);
    std::cout << "Waiting for all clients done!" << std::endl;
    for (int i = 0; i < threadclient.size(); i++)
    {
        threadclient[i].join();
    }
    shutdown(server, 2);
    closesocket(server);
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
    std::string tmp;
    if (number_Standard_room_available > 0)
    {
        std::string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + std::string("Number Standard room available: ") + int_to_string(number_Standard_room_available) + "\n";
        tmp = tmp + std::string("Price Standard room: ") + double_to_string(price_Standard_room) + " USD \n\n";
        count++;
    }

    if (number_Superior_room_available > 0)
    {
        std::string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + std::string("Number Superior room available: ") + int_to_string(number_Superior_room_available) + "\n";
        tmp = tmp + std::string("Price Superior room: ") + double_to_string(price_Superior_room) + " USD \n\n";
        count++;
    }

    if (number_Deluxe_room_available > 0)
    {
        std::string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + std::string("Number Deluxe room available: ") + int_to_string(number_Deluxe_room_available) + "\n";
        tmp = tmp + std::string("Price Deluxe room: ") + double_to_string(price_Deluxe_room) + " USD \n\n";
        count++;
    }


    if (number_Suite_room_available > 0)
    {
        std::string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + std::string("Number Suite room available: ") + int_to_string(number_Suite_room_available) + "\n";
        tmp = tmp + std::string("Price Suite room: ") + double_to_string(price_Suite_room) + " USD \n\n";
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
