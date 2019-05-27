#include "Controller.h"

#define FIRST_PART 0
#define SECOND_PART 1
#define START 4
#define S_START 5
#define NEXT 2
#define PREV 1
#define EMPTY 0
#define UNREAD_SIZE 2
#define READ_SIZE 3
#define O_START 0
#define GET "GET"
#define FOLLOWERS "followers"
#define PUBLISHED "published"
#define FILMS "films"
#define FILM_ID "film_id"
#define PURCHASED "purchased"
#define LIMIT "limit"
#define NOTIFICATIONS "notifications"
#define PUT "PUT"
#define DELETE "DELETE"
#define OK "OK"
#define COMMENTS "comments"
#define COMMENT_ID "comment_id"
#define POST "POST"
#define SIGNUP "signup"
#define LOGIN "login"
#define PUBLISHER "Publisher "
#define ID " with id "
#define REGISTER_FILM " register new film."
#define MONEY "money"
#define AMOUNT "amount"
#define CONTENT "content"
#define REPLIES "replies"
#define REPLY_COMMENT " reply to your comment."
#define USER "User "
#define USER_ID "user_id"
#define FOLLOW " follow you."
#define BUY "buy"
#define BUY_FILM " buy your film "
#define DOT "."
#define RATE_FILM " rate your film "
#define COMMENT_FILM " comment on your film "
#define RATE "rate"
#define SCORE "score"
#define PUT_FILMS "put_films"
#define DELETE_FILMS "delete_films"
#define DELETE_COMMENTS "delete_comments"
#define LOGOUT "logout"

Controller::Controller():
users_repository(), comments_repository(), films_repository()
{
	loggedin = NULL;
}

void Controller::act_on(std::vector<std::string> input)
{
	std::string notif;
	std::map<std::string, std::string> informations;
	if(input[FIRST_PART] == GET)
	{
		if(loggedin == NULL)
				throw PermissionDenied();
		if(input[SECOND_PART] == FOLLOWERS)
		{
			if(!(loggedin->is_publisher()))
				throw PermissionDenied();
			users_repository.print_by_ids(loggedin->get_followers());
		}
		else if(input[SECOND_PART] == PUBLISHED)
		{
			if(!(loggedin->is_publisher()))
				throw PermissionDenied();
			for(int i = START; i < input.size(); i += NEXT)
				informations[input[i - PREV]] = input[i];
			films_repository.print_film_by_ids(informations, loggedin->get_films());
		}
		else if(input[SECOND_PART] == FILMS)
		{
			for(int i = START; i < input.size(); i += NEXT)
				informations[input[i - PREV]] = input[i];
			if(informations[FILM_ID].size() == EMPTY)
				films_repository.print_films(informations);
			else
				films_repository.print_film(informations[FILM_ID], loggedin->get_purchased());
		}
		else if(input[SECOND_PART] == PURCHASED)
		{
			for(int i = START; i < input.size(); i += NEXT)
				informations[input[i - PREV]] = input[i];
			films_repository.print_film_by_ids(informations, loggedin->get_purchased());
		}
		else if(input[SECOND_PART] == NOTIFICATIONS && input.size() == UNREAD_SIZE)
		{
			loggedin->show_notifs();
		}
		else if(input[SECOND_PART] == NOTIFICATIONS && input.size() >= READ_SIZE)
		{
			for(int i = S_START; i < input.size(); i += NEXT)
				informations[input[i - PREV]] = input[i];
			loggedin->show_read_notifs(informations[LIMIT]);
		}
	}
	else if(input[FIRST_PART] == POST)
	{
		if(loggedin == NULL)
		{
			if(input[SECOND_PART] == SIGNUP)
			{
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				loggedin = users_repository.add_user(informations);
				std::cout << OK << std::endl;
			}
			else if(input[SECOND_PART] == LOGIN)
			{
				User* loggingin;
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				loggingin = users_repository.login_check(informations);
				if(loggingin != NULL)
					loggedin = loggingin;
				std::cout << OK << std::endl;
			}
			else
				throw PermissionDenied();
		}
		else
		{
			if(input[SECOND_PART] == LOGOUT)
			{
				loggedin = NULL;
				std::cout << OK << std::endl;
			}
			else if(input[SECOND_PART] == FILMS)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				if(!loggedin->is_publisher())
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				int unsubmitted_film = films_repository.add_film(informations, loggedin->get_id());
				loggedin->submit_film(unsubmitted_film);
				std::cout << OK << std::endl;
				notif = PUBLISHER;
				notif += loggedin->get_username();
				notif += ID;
				notif += std::to_string(loggedin->get_id());
				notif += REGISTER_FILM;
				std::vector<int> followers = loggedin->get_followers();
				for (int i = O_START; i < followers.size(); ++i)
				{
					users_repository.notif_to_user(followers[i], notif);
				}
			}
			else if(input[SECOND_PART] == PUT_FILMS)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				if(loggedin->get_id() != films_repository.find_film_pub(informations[FILM_ID]))
					throw PermissionDenied();
				films_repository.edit_film(informations);
				std::cout << OK << std::endl;
			}
			else if(input[SECOND_PART] == DELETE_FILMS)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				if(loggedin->get_id() != films_repository.find_film_pub(informations[FILM_ID]))
					throw PermissionDenied();
				films_repository.delete_film(informations[FILM_ID]);
				std::cout << OK << std::endl;
			}
			else if(input[SECOND_PART] == MONEY)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				if(!(loggedin->is_publisher()) && informations[AMOUNT].size() == EMPTY)
					throw PermissionDenied();
				else if(informations[AMOUNT].size() > EMPTY)
					loggedin->add_money(informations[AMOUNT]);
				else
				{
					users_repository.pay_debt_system(loggedin->get_debt());
					loggedin->receive_money();
				}
				std::cout << OK << std::endl;
			}
			else if(input[SECOND_PART] == REPLIES)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				if(!(loggedin->is_publisher()))
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				if(loggedin->get_id() != films_repository.find_film_pub(informations[FILM_ID]))
					throw PermissionDenied();
				int commenter_id = films_repository.reply_to_comment(stoi(informations[FILM_ID])
					, informations[COMMENT_ID], informations[CONTENT]);
				std::cout << OK << std::endl;
				notif = PUBLISHER;
				notif += loggedin->get_username();
				notif += ID;
				notif += std::to_string(loggedin->get_id());
				notif += REPLY_COMMENT;
				users_repository.notif_to_user(commenter_id, notif);
			}
			else if(input[SECOND_PART] == FOLLOWERS)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				users_repository.add_follower_to_pub(informations[USER_ID], loggedin->get_id());
				std::cout << OK << std::endl;
				notif = USER;
				notif += loggedin->get_username();
				notif += ID;
				notif += std::to_string(loggedin->get_id());
				notif += FOLLOW;
				users_repository.notif_to_user(stoi(informations[USER_ID]), notif);
			}
			else if(input[SECOND_PART] == BUY)
			{
				int money_trans;
				if(loggedin == NULL)
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				money_trans = loggedin->buy_film(films_repository.find_film_price(informations[FILM_ID])
					, stoi(informations[FILM_ID]));
				users_repository.add_system_debt(films_repository.find_film_pub(informations[FILM_ID])
					, films_repository.find_film_price(informations[FILM_ID]) * money_trans
					, films_repository.find_film_rate(informations[FILM_ID]));
				std::cout << OK << std::endl;
				notif = USER;
				notif += loggedin->get_username();
				notif += ID;
				notif += std::to_string(loggedin->get_id());
				notif += BUY_FILM;
				notif += films_repository.find_film_name(informations[FILM_ID]);
				notif += ID;
				notif += informations[FILM_ID];
				notif += DOT;
				users_repository.notif_to_user(films_repository.find_film_pub(informations[FILM_ID]), notif);
			}
			else if(input[SECOND_PART] == RATE)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				if(loggedin->has_not_bought(informations[FILM_ID]))
					throw PermissionDenied();
				films_repository.rate_film(stoi(informations[FILM_ID]), informations[SCORE], 
					loggedin->last_rate(stoi(informations[FILM_ID])));
				std::cout << OK << std::endl;
				notif = USER;
				notif += loggedin->get_username();
				notif += ID;
				notif += std::to_string(loggedin->get_id());
				notif += RATE_FILM;
				notif += films_repository.find_film_name(informations[FILM_ID]);
				notif += ID;
				notif += informations[FILM_ID];
				notif += DOT;
				users_repository.notif_to_user(films_repository.find_film_pub(informations[FILM_ID]), notif);
			}
			else if(input[SECOND_PART] == COMMENTS)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				if(loggedin->has_not_bought(informations[FILM_ID]))
					throw PermissionDenied();
				films_repository.comment_film(stoi(informations[FILM_ID]), informations[CONTENT], loggedin->get_id());
				std::cout << OK << std::endl;
				notif = USER;
				notif += loggedin->get_username();
				notif += ID;
				notif += std::to_string(loggedin->get_id());
				notif += COMMENT_FILM;
				notif += films_repository.find_film_name(informations[FILM_ID]);
				notif += ID;
				notif += informations[FILM_ID];
				notif += DOT;
				users_repository.notif_to_user(films_repository.find_film_pub(informations[FILM_ID]), notif);
			}
			else if(input[SECOND_PART] == DELETE_COMMENTS)
			{
				if(loggedin == NULL)
					throw PermissionDenied();
				if(!(loggedin->is_publisher()))
					throw PermissionDenied();
				for(int i = START; i < input.size(); i += NEXT)
					informations[input[i - PREV]] = input[i];
				if(loggedin->get_id() != films_repository.find_film_pub(informations[FILM_ID]))
					throw PermissionDenied();
				films_repository.delete_comment(stoi(informations[FILM_ID]), informations[COMMENT_ID]);
				std::cout << OK << std::endl;
			}
			else
				throw BadRequest();
		}
	}
}