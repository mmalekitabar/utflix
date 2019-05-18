#include "Controller.h"

Controller::Controller():
users_repository(), comments_repository(), films_repository(){}

void Controller::act_on(std::vector<std::string> input)
{
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
			std::map<std::string, std::string> informations;
			for(int i = 3; i < input.size(); i += 2)
				informations[input[i]] = input[i+1];
			loggedin = users_repository.add_user(informations);
			std::cout << loggedin->
			
		}
		else if(input[1] == "login")
		{
			std::map<std::string, std::string> informations;
			for(int i = 3; i < input.size(); i += 2)
				informations[input[i]] = input[i+1];
			
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