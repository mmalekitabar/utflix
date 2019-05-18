#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "User.h"

class Publisher : public User
{
public:
	Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher);
private:

};

#endif