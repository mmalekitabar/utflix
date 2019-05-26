#include "Film.h"


Film::Film(int _id, std::string _name, int _year, int _length, int _price
	, std::string _summary, std::string _director, int _publisher_id)
{
	id = _id;
	name = _name;
	year = _year;
	length = _length;
	price = _price;
	summary = _summary;
	director = _director;
	rate = 0;
	rated_num = 0;
	publisher_id = _publisher_id;
	sold_out = false;
	last_comment_id = 1;
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

void Film::sell_out()
{
	sold_out = true;
}

void Film::set_rate(int _rate)
{
	rate = _rate;
}

void Film::increase_rated_num()
{
	rated_num++;
}

int Film::get_rated_num()
{
	return rated_num;
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

bool Film::sell_status()
{
	return !sold_out;
}

int Film::get_price()
{
	return price;
}

int Film::get_year()
{
	return year;
}

double Film::get_rate()
{
	return rate;
}

int Film::get_length()
{
	return length;
}

std::string Film::get_name()
{
	return name;
}

std::string Film::get_director()
{
	return director;
}

std::string Film::get_summary()
{
	return summary;
}

void Film::add_rate(int _rate)
{
	rate = (rate*rated_num +_rate)/(double)(rated_num + 1);
	rated_num++;
}

void Film::update_rate(int _rate, int last_rate)
{
	rate = (rate*rated_num - last_rate +_rate)/((double)rated_num);
}

void Film::add_comment(std::string content, int commenter)
{
	comments.push_back(new Comment(last_comment_id, content, commenter));
	last_comment_id++;
}

int Film::add_reply(int comment_id, std::string content)
{
	for(int i = 0; i < comments.size(); i++)
	{
		if(comments[i]->get_id() == comment_id)
		{
			return comments[i]->set_reply(content);
		}
	}
	throw NotFound();
}

void Film::erase_comment(int comment_id)
{
	for(int i = 0; i < comments.size(); i++)
	{
		if(comments[i]->get_id() == comment_id)
		{
			comments.erase(comments.begin() + i);
			return;
		}
	}
	throw NotFound();
}

void Film::print_comments()
{
	int comment_num = 1;
	for(int i = 0; i < comments.size(); i++)
	{
		std::cout << comments[i]->get_id() << ". " << comments[i]->get_content() << std::endl;
		std::vector<std::string> replies = comments[i]->get_replies();
		for(int j = 0; j < replies.size(); j++)
		{
			std::cout << comments[i]->get_id() << "." << j + 1 << ". " << replies[j] << std::endl;
		}
	}
}