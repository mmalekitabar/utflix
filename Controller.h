#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "UsersRepository.h"
#include "CommentsRepository.h"
#include "FilmsRepository.h"
#include "Exceptions.h"

class Controller
{
public:
	Controller();
	void act_on(std::vector<std::string> input);

private:
	UsersRepository users_repository;
	CommentsRepository comments_repository;
	FilmsRepository films_repository;
	User* loggedin;
};


#endif