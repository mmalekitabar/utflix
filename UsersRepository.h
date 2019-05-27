#ifndef USERSREPOSITORY_H
#define USERSREPOSITORY_H

#include <map>
#include <vector>
#include <iostream>
#include <regex>
#include "User.h"
#include "Publisher.h"

class exception;

class UsersRepository
{
public:
	UsersRepository();
	User* add_user(std::map<std::string, std::string> informations);
	User* login_check(std::map<std::string, std::string> informations);
	void print_by_ids(std::vector<int> ids);
	void add_follower_to_pub(std::string pub_id, int follower_id);
	void add_system_debt(int pub_id, int whole_money, double rate);
	void notif_to_user(int user_id, std::string notif);
	void pay_debt_system(int debt);
	int id_generator();
	std::string email_adjust(std::string _email);
	std::string username_adjust(std::string _username);
	std::string password_adjust(std::string _password);
	int age_adjust(std::string _age);
	std::vector<int> get_mutals(int film_id, int films_num);
private:
	std::vector<User*> users;
	int last_id;
};

#endif