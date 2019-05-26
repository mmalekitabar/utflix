#include "Comment.h"

Comment::Comment(int _id, std::string _text, int commenter)
{
	id = _id;
	commenter_id = commenter;
	text = _text;
}

int Comment::set_reply(std::string content)
{
	reply.push_back(content);
	return commenter_id;
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