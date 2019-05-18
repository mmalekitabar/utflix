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