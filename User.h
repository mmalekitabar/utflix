#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>
#include "Exceptions.h"
#include "./server/server.hpp"

class User
{
public:
	User(int _id, std::string _email, std::string _username
		, std::string _password, int _age, bool _publisher);
	std::string get_username();
	std::string get_password();
	std::string get_email();
	void add_money(std::string amount);
	void recieve_money(int amount);
	int buy_film(int film_price, int film_id);
	int num_adjust(std::string num);
	int last_rate(int film_id);
	std::vector<int> get_purchased();
	virtual std::vector<int> get_followers(){};
	virtual void add_follower(int follower_id){};
	virtual void receive_money(){};
	virtual std::vector<int> get_films(){};
	virtual void submit_film(int film_id){};
	virtual void add_bank(int amount){};
	virtual int get_debt(){};
	int get_id();
	int get_money();
	bool is_publisher();
	bool has_not_bought(std::string film_id);
	void add_notif(std::string notif);
	std::vector<std::string> get_notifs();
	std::vector<std::string> get_read_notifs();
private:
	int id;
	std::string email;
	std::string username;
	std::string password;
	int age;
	bool publisher;
	std::vector<int> purchased_id;
	std::vector<int> rate_purchased;
	std::vector<std::string> notifications;
	std::vector<std::string> read_notifications;
protected:
	int money;
};

#endif