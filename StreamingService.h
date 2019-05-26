#ifndef STREAMINGSERVICE_H
#define STREAMINGSERVICE_H

#include <iostream>
#include <string>
#include <vector>

#include "Controller.h"

class StreamingService
{
public:
	StreamingService();
	void run();
	std::string get_input();
	void check_input(std::string input);
	void act_on_input(std::string input);

private:
	Controller controller;
};

#endif