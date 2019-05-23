#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <string>
#include <map>
#include "Exceptions.h"

class Film
{
public:
	Film(int _id, std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director, int _publisher_id);
	void change_information(std::map<std::string, std::string> informations);
	void sell_out();
	int get_id();
	int get_pub_id();
	int is_num(std::string num);
	bool sell_status();
private:
	int id;
	std::string name;
	int year;
	int length;
	int price;
	std::string summary;
	std::string director;
	double rate;
	int publisher_id;
	bool sold_out;
};

#endif