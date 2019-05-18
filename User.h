#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
	User(int id, std::string email,	std::string username, std::string password, int age, bool publisher);
	std::string get_username();
private:
	int id;
	std::string email;
	std::string username;
	std::string password;
	int age;
	bool publisher;
};

#endif