#ifndef COMMENT_H
#define COMMENT_H


#include <iostream>
#include <string>

class Comment
{
public:
	Comment(std::string _text);

private:
	std::string text;
	std::string reply;
};

#endif