#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "./server/server.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "UsersRepository.h"
#include "FilmsRepository.h"

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LogoutHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class FilmSubmitHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class FilmDetailHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class BuyHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class RateHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ChargeWalletHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ReceiveDebtHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowLogin : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowSignup : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowFilmSubmit : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowPubHome : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowPubProfile : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowCusHome : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowCusProfile : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowNotifications : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowPubBank : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowCusBank : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowPublishedFilms : public RequestHandler {
public:
  Response *callback(Request *);
};

#endif
