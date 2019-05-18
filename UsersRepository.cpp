#include "UsersRepository.h"

UsersRepository::UsersRepository()
{
	last_id = 0;
	std::cout << users.size() << std::endl;
}

void UsersRepository::add_user(std::map<std::string, std::string>  informations)
{
	if(informations["publisher"] == "true")
	{
		users.push_back(new Publisher(id_generator(), email_adjust(informations["email"]), username_adjust(informations["username"]), password_adjust(informations["password"]), age_adjust(informations["age"]), true));
	}
	else
	{
		users.push_back(new User(id_generator(), email_adjust(informations["email"]), username_adjust(informations["username"]), password_adjust(informations["password"]), age_adjust(informations["age"]), false));
	}
}

int UsersRepository::id_generator()
{
	std::cout << "id" << std::endl;
	last_id++;
	std::cout << "id e" << std::endl;
	return (last_id - 1);
}

std::string UsersRepository::email_adjust(std::string _email)
{ 
   const std::regex pattern ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   	if(std::regex_match(_email, pattern))
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