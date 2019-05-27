#include "UsersRepository.h"

UsersRepository::UsersRepository()
{
	last_id = 2;
	users.push_back(new User(1, "admin@utflix.ir", "admin", "admin", 19, false));
}

User* UsersRepository::add_user(std::map<std::string, std::string>  informations)
{
	if(informations["publisher"] == "true")
	{
		users.push_back(new Publisher(id_generator(), email_adjust(informations["email"])
			, username_adjust(informations["username"]), password_adjust(informations["password"])
			, age_adjust(informations["age"]), true));
		last_id++;
		return users[last_id - 2];
	}
	else
	{
		users.push_back(new User(id_generator(), email_adjust(informations["email"])
			, username_adjust(informations["username"]), password_adjust(informations["password"])
			, age_adjust(informations["age"]), false));
		last_id++;
		return users[last_id - 2];
	}
}

User* UsersRepository::login_check(std::map<std::string, std::string> informations)
{
	if(informations["username"].size() == 0)
		throw BadRequest();
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->get_username() == informations["username"])
		{
			if(users[i]->get_password() == informations["password"]){
				return users[i];
			}
			throw BadRequest(); 
		}
	}
	throw NotFound();
}

void UsersRepository::print_by_ids(std::vector<int> ids)
{
	std::cout << "List of Followers" << std::endl 
		<< "#. User Id | User Username | User Email" << std::endl;
	int list_num = 1;
	for(int i = 0; i < users.size(); i++)
	{
		for(int j = 0; j < ids.size(); j++)
		{
			if(users[i]->get_id() == ids[j])
			{
				std::cout << list_num << ". " << users[i]->get_id() << " | " 
					<< users[i]->get_username() << " | " << users[i]->get_email() << std::endl;
				list_num++;
				break;
			}
		}
	}
}

void UsersRepository::add_follower_to_pub(std::string pub_id, int follower_id)
{
	if(pub_id.size() == 0)
		throw BadRequest();
	for(int i = 0; i < pub_id.size(); i++)
	{
		if(pub_id[i] > 57 || pub_id[i] < 48)
			throw BadRequest();
	}
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->get_id() == stoi(pub_id))
		{
			if(!(users[i]->is_publisher()))
				throw BadRequest();
			for(int j = 0; j < (users[i]->get_followers()).size(); j++)
			{
				if((users[i]->get_followers())[j] == follower_id)
				{
					return;
				}
			}
			users[i]->add_follower(follower_id);
		}
	}
}


void UsersRepository::add_system_debt(int pub_id, int whole_money, double rate)
{
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->get_id() == pub_id)
		{
			users[0]->add_money(std::to_string(whole_money));
			if(rate >= 8)
				users[i]->add_bank(whole_money * 0.95);
			else if(rate >= 5)
				users[i]->add_bank(whole_money * 0.9);
			else
				users[i]->add_bank(whole_money * 0.8);
			return;
		}
	}
}

void UsersRepository::notif_to_user(int user_id, std::string notif)
{
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->get_id() == user_id)
		{
			users[i]->add_notif(notif);
		}
	}
}

void UsersRepository::pay_debt_system(int debt)
{
	users[0]->recieve_money(debt);
}

int UsersRepository::id_generator()
{
	return last_id;
}

std::string UsersRepository::email_adjust(std::string _email)
{ 
   const std::regex email_pattern
   	("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   	if(std::regex_match(_email, email_pattern))
		return _email;
	throw BadRequest();
}

std::string UsersRepository::username_adjust(std::string _username)
{
	if(_username.size() == 0)
		throw BadRequest();
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->get_username() == _username)
			throw BadRequest(); 
	}
	return _username;
}

std::string UsersRepository::password_adjust(std::string _password)
{
	if(_password.size() == 0)
		throw BadRequest();
	return _password;
}

int UsersRepository::age_adjust(std::string _age)
{
	if(_age.size() == 0)
		throw BadRequest();
	for(int i = 0; i < _age.size(); i++)
	{
		if(_age[i] > 57 || _age[i] < 48)
			throw BadRequest();
	}
	return stoi(_age);
}

std::vector<int> UsersRepository::get_mutals(int film_id, int films_num)
{
	std::vector<int> mutals;
	for (int i = 0; i < films_num; ++i)
	{
		mutals.push_back(0);
	}
	std::vector<int> user_films;
	for (int i = 0; i < users.size(); ++i)
	{
		user_films = users[i]->get_purchased();
		for (int j = 0; j < user_films.size(); ++j)
		{
			if(user_films[j] == film_id)
			{
				for (int k = 0; k < user_films.size(); ++k)
				{
					if(k != j)
						mutals[user_films[k] - 1]++;
				}
			}
		}
	}
	return mutals;
}