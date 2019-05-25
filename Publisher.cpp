#include "Publisher.h"

Publisher::Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher):
User(_id, _email, _username, _password, _age, _publisher){}

std::vector<int> Publisher::get_followers()
{
	return followers_id;
}

void Publisher::add_follower(int follower_id)
{
	followers_id.push_back(follower_id);
}

void Publisher::receive_money()
{
	money += unreceived_money;
	unreceived_money = 0;
}

std::vector<int> Publisher::get_films()
{
	return films_id;
}

void Publisher::submit_film(int film_id)
{
	films_id.push_back(film_id);
}