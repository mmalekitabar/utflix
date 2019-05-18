#include "UsersRepository.h"

UsersRepository::UsersRepository()
{
	last_id = 0;
}

User* UsersRepository::add_user(std::map<std::string, std::string>  informations)
{
	if(informations["publisher"] == "true")
	{
		users.push_back(new Publisher(id_generator(), email_adjust(informations["email"]), username_adjust(informations["username"]), password_adjust(informations["password"]), age_adjust(informations["age"]), true));
		return users[last_id];
	}
	else
	{
		users.push_back(new User(id_generator(), email_adjust(informations["email"]), username_adjust(informations["username"]), password_adjust(informations["password"]), age_adjust(informations["age"]), false));
		return users[last_id];
	}
}

int UsersRepository::id_generator()
{
	last_id++;
	return (last_id - 1);
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
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->get_username() == _username)
			throw BadRequest(); 
	}
	return _username;
}

std::string UsersRepository::password_adjust(std::string _password)
{
	return _password;
}

int UsersRepository::age_adjust(std::string _age)
{
	for(int i = 0; i < _age.size(); i++)
	{
		if(_age[i] > 57 || _age[i] < 48)
			throw BadRequest();
	}
	return stoi(_age);
}