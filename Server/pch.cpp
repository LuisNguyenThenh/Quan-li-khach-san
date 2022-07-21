// pch.cpp: source file corresponding to the pre-compiled header
#pragma once 

#include "framework.h"
#include "pch.h"
#include <conio.h>



// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.


void login(int sockClient)
{
    user* client = new user;
    while (1)
    {
        // username 
        int size_name;
        recv(sockClient, (char*)&size_name, sizeof(int), 0);
        //std::cout << size_name;
        char* temp1 = new char[size_name + 1];
        recv(sockClient, (char*)temp1, size_name, 0);
        client->username.assign(temp1, size_name);
        //std::cout << client.username << std::endl;
        //password
        int size_pass;
        recv(sockClient, (char*)&size_pass, sizeof(int), 0);
        char* temp2 = new char[size_pass + 1];

        recv(sockClient, (char*)temp2, size_pass, 0);
        client->strpass.assign(temp2, size_pass);
        delete[] temp2;
        //std::cout << client.strpass << std::endl;

        int flag;
        bool check = isValid(client);
        if (check == 1)
        {
            flag = 1; // gui 1 xac nhan dang nhap thanh cong 
            send(sockClient, (char*)&flag, sizeof(int), 0);
            while (1) {
                recv(sockClient, (char*)&flag, sizeof(int), 0);
                if (flag == 1) {
                    lookup(sockClient);
                }
                if (flag == 2) {
                    booking(sockClient);
                }
                if (flag == 3) {
                    cancel_booking(sockClient);
                }
                if (flag == 4)
                    break;
            }
            break;
        }
        else
        {
            flag = 0; // gui 0 dang nhap that bai.
            send(sockClient, (char*)&flag, sizeof(int), 0);
        }

    }
}

void solve_client(int sockClient, int order_client)
{
    user* client = new user;
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
            //std::cout << p;
            char* temp1 = new char[p + 1];
            recv(sockClient, (char*)temp1, p, 0);
            client->username.assign(temp1, p);
            std::cout << client->username << std::endl;
            delete[] temp1;
            //password
            int k;
            recv(sockClient, (char*)&k, sizeof(int), 0);
            char* temp2 = new char[k + 1];
            //std::cout << k;
            recv(sockClient, (char*)temp2, k, 0);
            client->strpass.assign(temp2, k);
            std::cout << client->strpass << std::endl;
            delete[] temp2;
            //ID banking
            int r;
            recv(sockClient, (char*)&r, sizeof(int), 0);
            char* temp3 = new char[r + 1];
            recv(sockClient, (char*)temp3, r, 0);
            //std::cout << r;
            client->idBanking.assign(temp3, r);
            recv(sockClient, (char*)&tmp, sizeof(int), 0);
            //std::cout << client->idBanking << std::endl;
            std::cout << tmp;
            delete[] temp3;
            USER->Push(client);
            // tien hanh dang nhap sau khi dki
            if (tmp == 1)
            {
                login(sockClient);
            }
        } while (tmp != 1);
    }
    if (q == 1)
    {
        // ktra dang nhap
        login(sockClient);
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

void Hotel::Send_image_of_room(int socket, int kind)
{
    cv::Mat image;
    std::string name_file;

    if (kind == 1)
    {
        name_file = name + " Standard.jpg";
    }
    if (kind == 2)
    {
        name_file = name + " Superior.jpg";
    }

    if (kind == 3)
    {
        name_file = name + " Deluxe.jpg";
    }
    if (kind == 4)
    {
        name_file = name + " Suite.jpg";
    }
    std::cout << name_file << std::endl;

    char* file;
    string_to_char(name_file,file);
    image = cv::imread(file, 1);
    int size_name_file = name_file.length();
    send(socket, (char*)&size_name_file, sizeof(int), 0);
    send(socket, (char*)file, size_name_file, 0);

    int image_row = image.rows;
    int image_col = image.cols;
    int image_size = image.total() * image.elemSize();
    send(socket, (char*)&image_row, sizeof(int), 0);
    send(socket, (char*)&image_col, sizeof(int), 0);
    send(socket, (char*)&image_size, sizeof(int), 0);
    send(socket, (char*)image.data, image_size, 0);
    return;
}

iii Hotel::Number_available_room_of_each_kind_on_date(date date1, date date2)
{
    int number_Standard_room_available = number_Standard_room;
    int number_Superior_room_available = number_Superior_room;
    int number_Deluxe_room_available = number_Deluxe_room;
    int number_Suite_room_available = number_Suite_room;
    for (customer* p = list_booking->head; p; p = p->next)
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
        tmp = tmp + std::string("Price Standard room: ") + double_to_string(price_Standard_room) + " USD \n";
        tmp = tmp + std::string("Description: ") + decription_Standard_room + "\n\n";
        count++;
    }

    if (number_Superior_room_available > 0)
    {
        std::string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + std::string("Number Superior room available: ") + int_to_string(number_Superior_room_available) + "\n";
        tmp = tmp + std::string("Price Superior room: ") + double_to_string(price_Superior_room) + " USD \n";
        tmp = tmp + std::string("Description: ") + decription_Suite_room + "\n\n";
        count++;
    }

    if (number_Deluxe_room_available > 0)
    {
        std::string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + std::string("Number Deluxe room available: ") + int_to_string(number_Deluxe_room_available) + "\n";
        tmp = tmp + std::string("Price Deluxe room: ") + double_to_string(price_Deluxe_room) + " USD \n";
        tmp = tmp + std::string("Description: ") + decription_Deluxe_room + "\n\n";
        count++;
    }


    if (number_Suite_room_available > 0)
    {
        std::string num = int_to_string(count);
        tmp = tmp + num + ".\n";

        tmp = tmp + std::string("Number Suite room available: ") + int_to_string(number_Suite_room_available) + "\n";
        tmp = tmp + std::string("Price Suite room: ") + double_to_string(price_Suite_room) + " USD \n";
        tmp = tmp + std::string("Description: ") + decription_Suite_room + "\n\n";
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
