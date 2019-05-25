#ifndef COMMENT_H
#define COMMENT_H


#include <iostream>
#include <string>

class Comment
{
public:
	Comment(int _id, std::string _text);

private:
	int id;
	std::string text;
	std::string reply;
};

#endif