#include "User.h"

User::User(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher)
{
	id = _id;
	email = _email;
	username = _username;
	password = _password;
	age = _age;
	publisher = _publisher;
	money = 0;
}

void User::buy_film(int film_price, int film_id)
{
	if(film_price > money)
		throw PermissionDenied();
	for(int i = 0; i < purchased_id.size(); i++)
	{
		if(purchased_id[i] == film_id)
			return;
	}
	money -= film_price;
	purchased_id.push_back(film_id);
	rate_purchased.push_back(-1);
}

std::string User::get_username()
{
	return username;
}

std::string User::get_password()
{
	return password;
}

std::vector<int> User::get_purchased()
{
	return purchased_id;
}

void User::add_money(std::string amount)
{
	money += num_adjust(amount);
}

int User::get_id()
{
	return id;
}

int User::last_rate(int film_id)
{
	for(int i = 0; i < purchased_id.size(); i++)
	{
		if(purchased_id[i] == film_id)
			return rate_purchased[i];
	}
	throw NotFound();
}

bool User::is_publisher()
{
	return publisher;
}

std::string User::get_email()
{
	return email;
}

int User::num_adjust(std::string num)
{
	if(num.size() == 0)
		throw BadRequest();
	for(int i = 0; i < num.size(); i++)
	{
		if(num[i] > 57 || num[i] < 48)
			throw BadRequest();
	}
	return stoi(num);
}

bool User::has_not_bought(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = 0; i < purchased_id.size(); i++)
	{
		if(purchased_id[i] == num_adjust(film_id))
			return false;
	}
	return true;
}