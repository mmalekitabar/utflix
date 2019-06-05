#include "Film.h"
#include "./server/server.hpp"

#define DOT "."
#define DOT_S ". "
#define YEAR "year"
#define LENGTH "length"
#define NAME "name"
#define SUMMARY "summary"
#define DIRECTOR "director"
#define EMPTY 0
#define ZERO 0
#define NUM_START 48
#define NUM_END 57
#define YES 1
#define NO 0
#define START 0
#define ONE 1

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
	rate = ZERO;
	rated_num = ZERO;
	publisher_id = _publisher_id;
	sold_out = false;
	last_comment_id = ONE;
}

void Film::change_information(std::map<std::string, std::string> informations)
{
	if(!is_num(informations[YEAR]) || !is_num(informations[LENGTH]))
		throw Server::Exception("Type of data you entered is not right.");
	if(informations[NAME].size() > EMPTY)
		name = informations[NAME];
	if(informations[YEAR].size() > EMPTY)
		year = stoi(informations[YEAR]);
	if(informations[LENGTH].size() > EMPTY)
		length = stoi(informations[LENGTH]);
	if(informations[SUMMARY].size() > EMPTY)
		summary = informations[SUMMARY];
	if(informations[DIRECTOR].size() > EMPTY)
		director = informations[DIRECTOR];
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

	for(int i = START; i < num.size(); i++)
	{
		if(num[i] > NUM_END || num[i] < NUM_START)
			return NO;
	}
	return YES;
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
	rate = (rate*rated_num +_rate)/(double)(rated_num + ONE);
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
	for(int i = START; i < comments.size(); i++)
	{
		if(comments[i]->get_id() == comment_id)
		{
			return comments[i]->set_reply(content);
		}
	}
	throw Server::Exception("Comment not found.");
}

void Film::erase_comment(int comment_id)
{
	for(int i = START; i < comments.size(); i++)
	{
		if(comments[i]->get_id() == comment_id)
		{
			comments.erase(comments.begin() + i);
			return;
		}
	}
	throw Server::Exception("Comment not found.");
}

void Film::print_comments()
{
	int comment_num = ONE;
	for(int i = START; i < comments.size(); i++)
	{
		std::cout << comments[i]->get_id() << DOT_S << comments[i]->get_content() << std::endl;
		std::vector<std::string> replies = comments[i]->get_replies();
		for(int j = START; j < replies.size(); j++)
		{
			std::cout << comments[i]->get_id() << DOT << j + ONE << DOT_S << replies[j] << std::endl;
		}
	}
}