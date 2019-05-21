#ifndef USERSREPOSITORY_H
#define USERSREPOSITORY_H

#include "User.h"
#include "Publisher.h"
#include <map>
#include <vector>
#include <iostream>
#include "Exceptions.h"
#include <regex>

class UsersRepository
{
public:
	UsersRepository();
	User* add_user(std::map<std::string, std::string> informations);
	User* login_check(std::map<std::string, std::string> informations);
	int id_generator();
	std::string email_adjust(std::string _email);
	std::string username_adjust(std::string _username);
	std::string password_adjust(std::string _password);
	int age_adjust(std::string _age);
private:
	std::vector<User*> users;
	int last_id;
};

#endif