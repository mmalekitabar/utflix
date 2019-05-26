#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Exceptions.h"

class Comment
{
public:
	Comment(int _id, std::string _text, int commenter);
	int set_reply(std::string content);
	int get_id();
	std::string get_content();
	std::vector<std::string> get_replies();
private:
	int id;
	int commenter_id;
	std::string text;
	std::vector<std::string> reply;
};

#endif