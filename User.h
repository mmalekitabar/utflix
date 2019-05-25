#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>
#include "Exceptions.h"

class User
{
public:
	User(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher);
	std::string get_username();
	std::string get_password();
	std::string get_email();
	void add_money(std::string amount);
	void buy_film(int film_price, int film_id);
	int num_adjust(std::string num);
	std::vector<int> get_purchased();
	virtual std::vector<int> get_followers(){};
	virtual void add_follower(int follower_id){};
	virtual void receive_money(){};
	virtual std::vector<int> get_films(){};
	virtual void submit_film(int film_id){};
	int get_id();
	bool is_publisher();
	bool has_not_bought(std::string film_id);
private:
	int id;
	std::string email;
	std::string username;
	std::string password;
	int age;
	bool publisher;
	std::vector<int> purchased_id;
	std::vector<int> rate_purchased;
protected:
	int money;
};

#endif