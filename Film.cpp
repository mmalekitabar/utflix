#include "Film.h"


Film::Film(int _id, std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director, int _publisher_id)
{
	id = _id;
	name = _name;
	year = _year;
	length = _length;
	price = _price;
	summary = _summary;
	director = _director;
	rate = 0;
	publisher_id = _publisher_id;
}

void Film::change_information(std::map<std::string, std::string> informations)
{
	if(!is_num(informations["year"]) || !is_num(informations["length"]))
		throw BadRequest();
	if(informations["name"].size() > 0)
		name = informations["name"];
	if(informations["year"].size() > 0)
		year = stoi(informations["year"]);
	if(informations["length"].size() > 0)
		length = stoi(informations["length"]);
	if(informations["summary"].size() > 0)
		summary = informations["summary"];
	if(informations["director"].size() > 0)
		director = informations["director"];
}

int Film::get_id()
{
	return id;
}

int Film::get_pub_id()
{
	return publisher_id;
}

int Film::is_num(std::string num)
{
	for(int i = 0; i < num.size(); i++)
	{
		if(num[i] > 57 || num[i] < 48)
			return 0;
	}
	return 1;
}