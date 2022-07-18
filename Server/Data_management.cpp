#include "pch.h"
void to_json(json& j, const date& p) {
    j = json{
        {"d", p.d},
        {"m", p.m },
        {"y", p.y }
    };
}
void from_json(const json& j, date& p) {
    j.at("d").get_to(p.d);
    j.at("m").get_to(p.m);
    j.at("y").get_to(p.y);
};
void to_json(json& j, const customer& p) {
    j = json{
        {"user_name", p.user_name},
        {"note", p.note },
        {"date_in", p.date_in},
        {"date_out", p.date_out},
        {"kind_room", p.kind_room }
    };
}
void from_json(const json& j, customer& p) {
    j.at("user_name").get_to(p.user_name);
    j.at("note").get_to(p.note);
    j.at("date_in").get_to(p.date_in);
    j.at("date_out").get_to(p.date_out);
    j.at("kind_room").get_to(p.kind_room);
};
void to_json(json& j, const Hotel& p) {
    j = json{ {"name", p.name},
        {"number_Standard_room", p.number_Standard_room },
        {"number_Superior_room", p.number_Superior_room },
        {"number_Deluxe_room", p.number_Deluxe_room },
        {"number_Suite_room", p.number_Suite_room },
        {"price_Superior_room", p.price_Superior_room},
        {"price_Standard_room", p.price_Standard_room },
        {"price_Deluxe_room", p.price_Deluxe_room },
        {"price_Suite_room", p.price_Suite_room },
        {"decription_Standard_room", p.decription_Standard_room },
        {"decription_Superior_room", p.decription_Superior_room },
        {"decription_Deluxe_room", p.decription_Deluxe_room },
        {"decription_Suite_room", p.decription_Suite_room },
    };
}
void from_json(const json& j, Hotel& p) {
    j.at("name").get_to(p.name);
    j.at("number_Standard_room").get_to(p.number_Standard_room);
    j.at("number_Superior_room").get_to(p.number_Superior_room);
    j.at("number_Deluxe_room").get_to(p.number_Deluxe_room);
    j.at("number_Suite_room").get_to(p.number_Suite_room);
    j.at("price_Superior_room").get_to(p.price_Superior_room);
    j.at("price_Standard_room").get_to(p.price_Standard_room);
    j.at("price_Deluxe_room").get_to(p.price_Deluxe_room);
    j.at("price_Suite_room").get_to(p.price_Suite_room);
    j.at("decription_Standard_room").get_to(p.decription_Standard_room);
    j.at("decription_Superior_room").get_to(p.decription_Superior_room);
    j.at("decription_Deluxe_room").get_to(p.decription_Deluxe_room);
    j.at("decription_Suite_room").get_to(p.decription_Suite_room);
};
Hotel::Hotel(std::string Hotelname)
{
    Hotelname += ".json";
    std::ifstream fin(Hotelname.c_str(), std::ios::in);
    json j;
    fin >> j;
    j.get_to(*this);
    this->list_booking = new link_list;
    fin.close();
}
Hotel::~Hotel()
{
    std::string temp = this->name + ".json";
    std::ofstream out(temp.c_str(), std::ios::trunc);
    json j = *this;
    out << j;
    out.close();
}
void link_list::addtolist(const json j)
{
    customer* temp = new customer;
    j.get_to(*temp);
    this->add(temp);
}
link_list::link_list()
{
    std::ifstream fin("customer.json", std::ios::beg);
    json j;
    int number;
    fin >> number;
    for (int i = 0; i < number; i++)
    {
        fin >> j;
        this->addtolist(j);
    }
    fin.close();
}
link_list::~link_list()
{
    if (this->head == NULL)
        return;
    std::ofstream out("customer.json", std::ios::trunc);
    json j;
    out << this->number_customer;
    customer* temp = this->head;
    while (temp != this->tail)
    {
        j = *temp;
        out << j;
        temp = temp->next;
        delete temp->pre;
    }
    j = *temp;
    out << j;
    delete temp;
    out.close();
}
