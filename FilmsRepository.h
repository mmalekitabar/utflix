#ifndef FILMSREPOSITORY_H
#define FILMSREPOSITORY_H

#include <vector>
#include <map>
#include <string>
#include "Exceptions.h"
#include "Film.h"
#include "./server/server.hpp"

class FilmsRepository
{
public:
	FilmsRepository();
	static FilmsRepository* get_films_rep();
	std::vector<Film*> get_films();
	Film* get_film(int film_id);
	int add_film(std::map<std::string, std::string> informations, int publisher_id);
	void recom_table_expand(int curr_id);
	void edit_film(std::map<std::string, std::string> informations);
	void delete_film(std::string film_id);
	void print_film_by_ids(std::map<std::string, std::string> informations, std::vector<int> films_id);
	void print_films(std::map<std::string, std::string> informations);
	void print_film(std::string film_id, std::vector<int> purchased_id);
	void rate_film(int film_id, std::string s_rate, int last_rate);
	void comment_film(int film_id, std::string content, int commenter_id);
	int reply_to_comment(int film_id, std::string comment_id, std::string content);
	void delete_comment(int film_id, std::string comment_id);
	void recommendation_print(int film_id, std::vector<int> purchased_id);
	int find_film_pub(std::string film_id);
	int find_film_price(std::string film_id);
	double find_film_rate(std::string film_id);
	std::string find_film_name(std::string film_id);
	int id_generator();
	int num_adjust(std::string num);
	std::string string_adjust(std::string str);
	bool name_check(std::string s_name, std::string name);
	bool rate_check(std::string s_rate, double rate);
	bool year_check(std::string min_year, std::string max_year, int year);
	bool price_check(std::string s_price, int price);
	bool director_check(std::string s_director, std::string director);
	int get_film_num();
	void update_recom_table(int film_id, std::vector<int> mutals);
private:
	static FilmsRepository* main_repository;
	int last_id;
	std::vector<Film*> films;
	std::vector<std::vector<int>> recom_table;
};

#endif