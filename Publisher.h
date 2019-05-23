#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "User.h"
//#include <vector>

class Publisher : public User
{
public:
	Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher);
	std::vector<int> get_followers();
private:
	std::vector<int> followers_id;
};

#endif