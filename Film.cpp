#include "Film.h"


Film::Film(int _id, std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director)
{
	id = _id;
	name = _name;
	year = _year;
	length = _length;
	price = _price;
	summary = _summary;
	director = _director;
	rate = 0;
}