#ifndef FILMSREPOSITORY_H
#define FILMSREPOSITORY_H

#include "Film.h"
#include <vector>
#include <map>
#include "Exceptions.h"
#include <string>

//class std::exception;

class FilmsRepository
{
public:
	FilmsRepository();
	void add_film(std::map<std::string, std::string> informations, int publisher_id);
	void edit_film(std::map<std::string, std::string> informations);
	void delete_film(std::string film_id);
	int find_film_pub(std::string film_id);
	int id_generator();
	int num_adjust(std::string num);
	std::string string_adjust(std::string str);

private:
	int last_id;
	std::vector<Film*> films;
};

#endif