#include "User.h"

User::User(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher)
{
	id = _id;
	email = _email;
	username = _username;
	password = _password;
	age = _age;
	publisher = _publisher;
}

std::string User::get_username()
{
	return username;
}

std::string User::get_password()
{
	return password;
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