#include "Comment.h"

Comment::Comment(int _id, std::string _text)
{
	id = _id;
	text = _text;
}

void Comment::set_reply(std::string content)
{
	reply.push_back(content);
}

int Comment::get_id()
{
	return id;
}

std::string Comment::get_content()
{
	return text;
}

std::vector<std::string> Comment::get_replies()
{
	return reply;
}