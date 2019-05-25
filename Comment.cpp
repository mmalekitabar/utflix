#include "Comment.h"

Comment::Comment(int _id, std::string _text)
{
	id = _id;
	text = _text;
	reply = "";
}