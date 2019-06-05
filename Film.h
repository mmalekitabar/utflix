#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Comment.h"
#include "Exceptions.h"

class Film
{
public:
	Film(int _id, std::string _name, int _year, int _length, int _price
		, std::string _summary, std::string _director, int _publisher_id);
	void change_information(std::map<std::string, std::string> informations);
	void sell_out();
	std::string get_name();
	std::string get_director();
	std::string get_summary();
	int get_price();
	int get_year();
	double get_rate();
	int get_rated_num();
	int get_length();
	int get_id();
	int get_pub_id();
	int is_num(std::string num);
	bool sell_status();
	void set_rate(int _rate);
	void increase_rated_num();
	void add_rate(int _rate);
	void update_rate(int _rate, int last_rate);
	void add_comment(std::string content, int commenter);
	int add_reply(int comment_id, std::string content);
	void erase_comment(int comment_id);
	std::vector<std::string> get_comments();
private:
	int id;
	std::string name;
	int year;
	int length;
	int price;
	std::string summary;
	std::string director;
	double rate;
	int rated_num;
	int publisher_id;
	bool sold_out;
	std::vector<Comment*> comments;
	int last_comment_id;
};

#endif