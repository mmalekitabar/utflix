#include "StreamingService.h"

#define ONE 1
#define START 0
#define EMPTY 0
#define SEPERATOR '?'
#define SPACE ' '

StreamingService::StreamingService():
controller(){}

void StreamingService::run()
{
	std::string input;
	while(true)
	{
		try
		{
			input = get_input();
			check_input(input);
			act_on_input(input);
		}
		catch(std::exception& error)
		{
			std::cout << error.what() << std::endl;
		}
	}
}

std::string StreamingService::get_input()
{
	std::string input;
	getline(std::cin, input);
	return input;
}

void StreamingService::check_input(std::string input)
{
	std::string part1 = input.substr(START, input.find(SPACE));
	input.erase(START, input.find(SPACE) + ONE);
	std::string part2 = input.substr(START, input.find(SEPERATOR) - ONE);
	if(part1 == "GET")
	{
		if(part2 != "followers" && part2 != "published" 
			&& part2 != "films" && part2 != "purchased" 
			&& part2 != "notifications" && part2 != "notifications read")
		{
			throw NotFound();
		}
	}
	else if(part1 == "PUT")
	{
		if(part2 != "films")
		{
			throw NotFound();
		}
	}
	else if(part1 == "DELETE")
	{
		if(part2 != "films" && part2 != "comments")
		{
			throw NotFound();
		}
	}
	else if(part1 == "POST")
	{
		if(part2 != "signup" &&  part2 != "login" && part2 != "films" 
			&& part2 != "money" && part2 != "replies" && part2 != "followers" 
			&& part2 != "buy" && part2 != "rate" && part2 != "comments")
		{
			throw NotFound();
		}
	}
	else if(part1.size() == EMPTY)
	{
		return;
	}
	else
	{
		throw BadRequest();
	}
}

void StreamingService::act_on_input(std::string input)
{
	if((input.substr(START, input.find(SPACE))).size() == EMPTY)
		return;
	std::vector<std::string> temp;
	for(int i = START; input.size() > EMPTY; i++)
	{
		std::string part = input.substr(START, input.find(SPACE));
		if(part.size() > EMPTY)
			temp.push_back(part);
		input.erase(START, temp[i].size() + ONE);
	}
	controller.act_on(temp);
}