#ifndef COMMENT_H
#define COMMENT_H


#include <iostream>
#include <string>
#include <vector>
#include "Exceptions.h"

class Comment
{
public:
	Comment(int _id, std::string _text);
	void set_reply(std::string content);
	int get_id();
	std::string get_content();
	std::vector<std::string> get_replies();
private:
	int id;
	std::string text;
	std::vector<std::string> reply;
};

#endif