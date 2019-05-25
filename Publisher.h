#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "User.h"
//#include <vector>

class Publisher : public User
{
public:
	Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher);
	virtual std::vector<int> get_followers();
	virtual void add_follower(int follower_id);
	virtual std::vector<int> get_films();
	virtual void submit_film(int film_id);
	virtual void receive_money();
private:
	std::vector<int> followers_id;
	std::vector<int> films_id;
	int unreceived_money;
};

#endif