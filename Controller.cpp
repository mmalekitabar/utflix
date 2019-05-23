#include "Controller.h"

Controller::Controller():
users_repository(), comments_repository(), films_repository()
{
	loggedin = NULL;
}

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
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(loggedin->get_id() != films_repository.find_film_pub(informations["film_id"]))
				throw PermissionDenied();
			films_repository.edit_film(informations);
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

			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];

			loggedin = users_repository.add_user(informations);
			std::cout << "OK" << std::endl;
			
		}
		else if(input[1] == "login")
		{
			User* loggingin;
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			loggingin = users_repository.login_check(informations);
			if(loggingin != NULL)
				loggedin = loggingin;
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "films")
		{
			if(loggedin == NULL)
				throw PermissionDenied();
			if(!loggedin->is_publisher())
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			films_repository.add_film(informations, loggedin->get_id());
			std::cout << "OK" << std::endl;
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