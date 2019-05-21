#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <string>

class Film
{
public:
	Film(int _id, std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director);

private:
	int id;
	std::string name;
	int year;
	int length;
	int price;
	std::string summary;
	std::string director;
	double rate;
};

#endif