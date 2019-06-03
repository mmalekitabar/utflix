#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "./server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <string>
#include <map>

#include "UsersRepository.h"

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LogoutHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

class SignupHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowLogin : public RequestHandler {
public:
  Response *callback(Request *);
};

#endif
