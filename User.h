#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User
{
public:
	User(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher);
	std::string get_username();
	std::string get_password();
private:
	int id;
	std::string email;
	std::string username;
	std::string password;
	int age;
	bool publisher;
};

#endif