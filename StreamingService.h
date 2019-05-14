#ifndef STREAMINGSERVICE_H
#define STREAMINGSERVICE_H

#include <iostream>
#include <string>

#include "UsersRepository.h"
#include "CommentsRepository.h"
#include "FilmsRepository.h"
#include "Exceptions.h"

class StreamingService
{
public:
	void run();
	std::string get_input();
	void check_input(std::string input);
	void act_on_input(std::string input);

private:
	UsersRepository users;
	FilmsRepository films;
	CommentsRepository comments;
};


#endif