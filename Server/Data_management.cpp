#include "pch.h"
std::ifstream fin("hotel.json");
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
void to_json(json& j, const user& p) {
    j = json{
        {"username", p.username},
        {"strpass", p.strpass },
        {"idBanking", p.idBanking }
    };
}
void from_json(const json& j, user& p) {
    j.at("username").get_to(p.username);
    j.at("strpass").get_to(p.strpass);
    j.at("idBanking").get_to(p.idBanking);
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
bool link_list::is_empty()
{
    if (this->head == NULL)
        return true;
    return false;
}
customer* link_list::find(char* s)
{
    if (this == NULL) return NULL;
    for (customer* p = this->head; p; p = p->next)
        if (p->user_name == s)
            return p;
    return NULL;
}
void link_list::add(customer* p)
{
    number_customer++;
    if (this->head == NULL)
    {
        this->head = this->tail = p;
        return;
    }
    else
    {
        this->tail->next = p;
        p->pre = this->tail;
        this->tail = p;
        return;
    }
}
void link_list::remove(char* s)
{
    number_customer--;
    customer* x = NULL;
    for (customer* p = this->head; p; p = p->next)
        if (p->user_name == s)
        {
            x = p;
            break;
        }
    if (x == NULL)
        return;
    else
    {
        if (x == this->head)
        {
            if (this->head != this->tail)
            {
                this->head = this->head->next;
                this->head->pre = NULL;
            }
            else
            {
                this->head = NULL;
                this->tail = NULL;
            }
            delete x;
            return;
        }
        if (x == this->tail)
        {
            this->tail = this->tail->pre;
            this->tail->next = NULL;
            delete x;
            return;
        }
        else
        {
            x->next->pre = x->pre;
            x->pre->next = x->next;
            delete x;
            x = NULL;
            return;
        }
    }
}
bool StackUser::IsEmpty()
{
    if (this->Head == NULL)
        return true;
    return false;
}
void StackUser::RemoveNode(user* p)
{
    if (this->Head == p)
        this->Head = p->Next;
    else
    {
        user* temp = this->Head;
        while (temp->Next != p)
            temp = temp->Next;
        temp->Next = p->Next;
    }
    delete p;
}
void StackUser::Push(user* temp)
{
    temp->Next = this->Head;
    this->Head = temp;
    this->number_user++;
}
void StackUser::Input(json j)
{
    user* temp = new user;
    j.get_to(*temp);
    this->Push(temp);
}
void StackUser::Pop()
{
    if (IsEmpty())
        return;
    RemoveNode(this->Head);
}
StackUser::StackUser()
{
    std::ifstream inp("user.json");
    json j;
    int number;
    inp >> number;
    for (int i = 0; i < number; i++)
    {
        inp >> j;
        this->Input(j);
    }
    inp.close();
}

StackUser::~StackUser()
{
    if (this == NULL || this->Head == NULL)
        return;
    std::ofstream out("user.json", std::ios::trunc);
    json j;
    out << this->number_user;
    while (this->Head!=NULL)
    {
        j = *this->Head;
        out << j;
        this->Pop();
    }
    out.close();
}
Hotel::Hotel()
{
    json j;
    fin >> j;
    j.get_to(*this);
    this->list_booking = new link_list;
}
Hotel::~Hotel()
{
    std::ofstream out("hotel.json", std::ios::out | std::ios::app | std::ios::in);
    json j = *this;
    out << j;
    out.close();
    this->list_booking->~link_list();
}
void link_list::addtolist(const json j)
{
    customer* temp = new customer;
    j.get_to(*temp);
    this->add(temp);
}
link_list::link_list()
{
    json j;
    int number;
    fin >> number;
    for (int i = 0; i < number; i++)
    {
        fin >> j;
        this->addtolist(j);
    }
}
link_list::~link_list()
{
    if (this == NULL || this->head == NULL)
        return;
    std::ofstream out("hotel.json", std::ios::out | std::ios::app | std::ios::in);
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
void Load_data()
{
    int number;
    fin >> number;
    fin.ignore();
    list_hotel = new Hotel[number];
    list_hotel->num_hotel = number;
    USER = new StackUser;
    fin.close();
    return;
}
void Finish(Hotel* a)
{
    std::ofstream out("hotel.json", std::ios::trunc);
    out << a->num_hotel << " ";
    out.close();
    delete[] a;
    USER->~StackUser();
}