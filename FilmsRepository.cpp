#include "FilmsRepository.h"

FilmsRepository::FilmsRepository()
{
	last_id = 0;
}

void FilmsRepository::add_film(std::map<std::string, std::string> informations, int publisher_id)
{
	films.push_back(new Film(id_generator(), string_adjust(informations["name"]), num_adjust(informations["year"]), num_adjust(informations["length"]), num_adjust(informations["price"]), string_adjust(informations["summary"]), string_adjust(informations["director"]), publisher_id));
	last_id++;
}

void FilmsRepository::edit_film(std::map<std::string, std::string> informations)
{
	int f_id = num_adjust(informations["film_id"]);
	for(int i = 0; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id())
		{
			films[i]->change_information(informations);
			return;
		}
	}
}

int FilmsRepository::find_film_pub(std::string film_id)
{
	int f_id = num_adjust(film_id);
	for(int i = 0; i < films.size(); i++)
	{
		if(f_id == films[i]->get_id())
			return films[i]->get_pub_id();
	}
	throw NotFound();
}

int FilmsRepository::id_generator()
{
	return last_id;
}


int FilmsRepository::num_adjust(std::string num)
{
	if(num.size() == 0)
		throw BadRequest();
	for(int i = 0; i < num.size(); i++)
	{
		if(num[i] > 57 || num[i] < 48)
			throw BadRequest();
	}
	return stoi(num);
}

std::string FilmsRepository::string_adjust(std::string str)
{
	if(str.size() == 0)
		throw BadRequest();
	return str;
}