#include "pch.h"

void to_json(json& j, const user& p) {
	j = json{ {"username", p.username}, {"strpass", p.strpass} , {"idBanking",p.idBanking} };
};

void from_json(const json& j, user& p) {
	j.at("username").get_to(p.username);
	j.at("strpass").get_to(p.strpass);
	j.at("idBanking").get_to(p.idBanking);
};

user* Getuser()
{
	user* temp = new user[50];
	ifstream in("Userdata.json");
	json j;
	for (int i = 0; i < 50; i++)
	{
		in >> j;
		temp[i] = j;
	}
	return temp;
}


