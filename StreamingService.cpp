#include "StreamingService.h"
#include "my_server.hpp"
#include "handlers.hpp"
#include <iostream>

#define ONE 1
#define START 0
#define EMPTY 0
#define SEPERATOR '?'
#define SPACE ' '
#define S_SPACE " "

StreamingService::StreamingService():
controller(){}

void StreamingService::run(int argc, char **argv)
{
	try {
		MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
		server.setNotFoundErrPage("static/404.html");
		server.get("/", new ShowPage("static/login.html"));
		server.get("/login", new ShowPage("static/login.html"));
		server.post("/login", new LoginHandler());
		server.get("/signup", new ShowPage("static/signup.html"));
		server.post("/signup", new SignupHandler());
		server.get("/pub_home", new ShowPage("static/pub_home.html"));
		//server.post("/pub_home", new LoginHandler());
		//server.get("/film_submit", new ShowPage("static/logincss.html"));
		//server.post("/film_submit", new LoginHandler());
		//server.get("/pub_profile", new ShowPage("static/logincss.html"));
		//server.post("/pub_profile", new LoginHandler());
		server.get("/cos_home", new ShowPage("static/cos_home.html"));
		//server.post("/cos_home", new LoginHandler());
		//server.get("/cos_profile", new ShowPage("static/logincss.html"));
		//server.post("/cos_profile", new LoginHandler());
		//server.get("/film_detail", new ShowPage("static/logincss.html"));
		//server.post("/film_detail", new LoginHandler());
		server.run();
  } catch (Server::Exception e) {
    std::cerr << e.getMessage() << std::endl;
  }
	/*std::string input;
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
	}*/
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
	std::string part2;
	if(input.find(SEPERATOR) != std::string::npos)
		part2 = input.substr(START, input.find(SEPERATOR) - ONE);
	else
		part2 = input.substr(START, input.find(SPACE));
	if(part1 == "GET")
	{
		if(part2 != "followers" && part2 != "published" 
			&& part2 != "films" && part2 != "purchased" && part2 != "money"
			&& part2 != "notifications" && part2 != "notifications read")
		{
			throw NotFound();
		}
	}
	else if(part1 == "POST")
	{

		if(part2 != "signup" && part2 != "login" && part2 != "films" 
			&& part2 != "money" && part2 != "replies" && part2 != "followers" 
			&& part2 != "buy" && part2 != "rate" && part2 != "comments" 
			&& part2 != "delete_films" && part2 != "delete_comments" 
			&& part2 != "put_films" && part2 != "logout")
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
		if(part != S_SPACE)
			temp.push_back(part);
		input.erase(START, temp[i].size() + ONE);
	}
	controller.act_on(temp);
}