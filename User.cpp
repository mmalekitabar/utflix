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

std::string User::get_username()
{
	return username;
}

std::string User::get_password()
{
	return password;
}

void User::add_money(std::string amount)
{
	money += num_adjust(amount);
}

int User::get_id()
{
	return id;
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