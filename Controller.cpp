#include "Controller.h"

Controller::Controller():
users_repository(), comments_repository(), films_repository(){}

void Controller::act_on(std::vector<std::string> input)
{
	std::map<std::string, std::string> informations;
	if(input[0] == "GET")
	{
		if(input[1] == "followers")
		{

		}
		else if(input[1] == "films")
		{

		}
		else if(input[1] == "purchased")
		{

		}
		else if(input[1] == "notifications" && input[2] != "read")
		{

		}
		else if(input[1] == "notifications" && input[2] == "read")
		{

		}
	}
	else if(input[0] == "PUT")
	{
		if(input[1] == "films")
		{
			
		}
	}
	else if(input[0] == "DELETE")
	{
		if(input[1] == "films")
		{
			
		}
		else if(input[1] == "comments")
		{

		}
	}
	else if(input[0] == "POST")
	{
		if(input[1] == "signup")
		{

			for(int i = 3; i < input.size(); i += 2)
				informations[input[i]] = input[i+1];

			loggedin = users_repository.add_user(informations);
			std::cout << "OK" << std::endl;
			
		}
		else if(input[1] == "login")
		{
			User* loggingin;
			for(int i = 3; i < input.size(); i += 2)
				informations[input[i]] = input[i+1];
			loggingin = users_repository.login_check(informations);
			if(loggingin != NULL)
				loggedin = loggingin;
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "films")
		{

		}
		else if(input[1] == "money")
		{

		}
		else if(input[1] == "replies")
		{

		}
		else if(input[1] == "followers")
		{

		}
		else if(input[1] == "buy")
		{

		}
		else if(input[1] == "rate")
		{

		}
		else if(input[1] == "comments")
		{

		}
	}
}