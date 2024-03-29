#include "User.h"

#define START 0
#define HAS_BOUGHT 0
#define HAS_NOT_BOUGHT 1
#define ZERO 0
#define EMPTY 0
#define NOT_RATED -1
#define ONE 1
#define NUM_START 48
#define NUM_END 57
#define NOTIFICATION "Notification Message"
#define DOT_S ". "

User::User(int _id, std::string _email, std::string _username
	, std::string _password, int _age, bool _publisher)
{
	id = _id;
	email = _email;
	username = _username;
	password = _password;
	age = _age;
	publisher = _publisher;
	money = ZERO;
}

int User::buy_film(int film_price, int film_id)
{
	if(film_price > money)
		throw Server::Exception("You do not havbe enough money.");
	for(int i = START; i < purchased_id.size(); i++)
	{
		if(purchased_id[i] == film_id)
			return HAS_BOUGHT;
	}
	money -= film_price;
	purchased_id.push_back(film_id);
	rate_purchased.push_back(NOT_RATED);
	return HAS_NOT_BOUGHT;
}

std::string User::get_username()
{
	return username;
}

std::string User::get_password()
{
	return password;
}

std::vector<int> User::get_purchased()
{
	return purchased_id;
}

void User::add_money(std::string amount)
{
	money += num_adjust(amount);
}

void User::recieve_money(int amount)
{
	money -= amount;
}

int User::get_id()
{
	return id;
}

int User::get_money()
{
	return money;
}
int User::last_rate(int film_id)
{
	for(int i = START; i < purchased_id.size(); i++)
	{
		if(purchased_id[i] == film_id)
			return rate_purchased[i];
	}
	throw Server::Exception("nothing found.");
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
	if(num.size() == EMPTY)
		throw Server::Exception("Enter something.");
	for(int i = START; i < num.size(); i++)
	{
		if(num[i] > NUM_END || num[i] < NUM_START)
			throw Server::Exception("Kind of data you entered is not right.");
	}
	return stoi(num);
}

bool User::has_not_bought(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = START; i < purchased_id.size(); i++)
	{
		if(purchased_id[i] == num_adjust(film_id))
			return false;
	}
	return true;
}

void User::add_notif(std::string notif)
{
	notifications.insert(notifications.begin(), notif);
}

std::vector<std::string> User::get_notifs()
{
	std::vector<std::string> notif_temp;
	for (int i = START; i < notifications.size(); i++)
	{
		read_notifications.insert(read_notifications.begin(), notifications[i]);
		notif_temp.push_back(notifications[i]);
	}
	notifications.clear();
	return notif_temp;
}

std::vector<std::string> User::get_read_notifs()
{
	return read_notifications;
}