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
	int add_film(std::map<std::string, std::string> informations, int publisher_id);
	void edit_film(std::map<std::string, std::string> informations);
	void delete_film(std::string film_id);
	void print_film_by_ids(std::map<std::string, std::string> informations, std::vector<int> films_id);
	void print_films(std::map<std::string, std::string> informations);
	void print_film(std::string film_id);
	void rate_film(int film_id, std::string s_rate, int last_rate);
	int find_film_pub(std::string film_id);
	int find_film_price(std::string film_id);
	int id_generator();
	int num_adjust(std::string num);
	std::string string_adjust(std::string str);
	bool name_check(std::string s_name, std::string name);
	bool rate_check(std::string s_rate, double rate);
	bool year_check(std::string min_year, std::string max_year, int year);
	bool price_check(std::string s_price, int price);
	bool director_check(std::string s_director, std::string director);
private:
	int last_id;
	std::vector<Film*> films;
};

#endif