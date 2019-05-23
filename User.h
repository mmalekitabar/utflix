#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>

class User
{
public:
	User(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher);
	std::string get_username();
	std::string get_password();
	std::string get_email();
	//virtual std::vector<int> get_followers();
	int get_id();
	bool is_publisher();
private:
	int id;
	std::string email;
	std::string username;
	std::string password;
	int age;
	bool publisher;
};

#endif