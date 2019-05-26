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
		if(loggedin == NULL)
				throw PermissionDenied();
		if(input[1] == "followers")
		{
			if(!(loggedin->is_publisher()))
				throw PermissionDenied();
			users_repository.print_by_ids(loggedin->get_followers());
		}
		else if(input[1] == "published")
		{
			if(!(loggedin->is_publisher()))
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			films_repository.print_film_by_ids(informations, loggedin->get_films());
		}
		else if(input[1] == "films")
		{
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(informations["film_id"].size() == 0)
				films_repository.print_films(informations);
			else
				films_repository.print_film(informations["film_id"], loggedin->get_purchased());
		}
		else if(input[1] == "purchased")
		{
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			films_repository.print_film_by_ids(informations, loggedin->get_purchased());
		}
		else if(input[1] == "notifications" && input.size() == 2)
		{
			std::cout << "notifications" << std::endl;
		}
		else if(input[1] == "notifications" && input.size() > 2)
		{
			std::cout << "notifications read" << std::endl;
		}
	}
	else if(input[0] == "PUT")
	{
		if(loggedin == NULL)
				throw PermissionDenied();
		if(input[1] == "films")
		{
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(loggedin->get_id() != films_repository.find_film_pub(informations["film_id"]))
				throw PermissionDenied();
			films_repository.edit_film(informations);
			std::cout << "OK" << std::endl;
		}
	}
	else if(input[0] == "DELETE")
	{
		if(loggedin == NULL)
				throw PermissionDenied();
		if(input[1] == "films")
		{
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(loggedin->get_id() != films_repository.find_film_pub(informations["film_id"]))
				throw PermissionDenied();
			films_repository.delete_film(informations["film_id"]);
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "comments")
		{
			if(!(loggedin->is_publisher()))
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(loggedin->get_id() != films_repository.find_film_pub(informations["film_id"]))
				throw PermissionDenied();
			films_repository.delete_comment(stoi(informations["film_id"]), informations["comment_id"]);
			std::cout << "OK" << std::endl;
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
			int unsubmitted_film = films_repository.add_film(informations, loggedin->get_id());
			loggedin->submit_film(unsubmitted_film);
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "money")
		{
			if(loggedin == NULL)
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(!(loggedin->is_publisher()) && informations["amount"].size() == 0)
				throw PermissionDenied();
			else if(informations["amount"].size() > 0)
				loggedin->add_money(informations["amount"]);
			else
				loggedin->receive_money();
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "replies")
		{
			if(loggedin == NULL)
				throw PermissionDenied();
			if(!(loggedin->is_publisher()))
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(loggedin->get_id() != films_repository.find_film_pub(informations["film_id"]))
				throw PermissionDenied();
			films_repository.reply_to_comment(stoi(informations["film_id"]), informations["comment_id"], informations["content"]);
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "followers")
		{
			if(loggedin == NULL)
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			users_repository.add_follower_to_pub(informations["user_id"], loggedin->get_id());
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "buy")
		{
			if(loggedin == NULL)
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			loggedin->buy_film(films_repository.find_film_price(informations["film_id"]), stoi(informations["film_id"]));
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "rate")
		{
			if(loggedin == NULL)
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(loggedin->has_not_bought(informations["film_id"]))
				throw PermissionDenied();
			films_repository.rate_film(stoi(informations["film_id"]), informations["score"], 
				loggedin->last_rate(stoi(informations["film_id"])));
			std::cout << "OK" << std::endl;
		}
		else if(input[1] == "comments")
		{
			if(loggedin == NULL)
				throw PermissionDenied();
			for(int i = 4; i < input.size(); i += 2)
				informations[input[i - 1]] = input[i];
			if(loggedin->has_not_bought(informations["film_id"]))
				throw PermissionDenied();
			films_repository.comment_film(stoi(informations["film_id"]), informations["content"]);
			std::cout << "OK" << std::endl;
		}
	}
}





///after buy money to pub