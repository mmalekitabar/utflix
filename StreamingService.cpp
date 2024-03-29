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
		server.get("/profile.png", new ShowImage("profile.png"));
		server.get("/back.jpeg", new ShowImage("back.jpeg"));
		server.get("/", new ShowLogin());
		server.get("/login", new ShowLogin());
		server.post("/login", new LoginHandler());
		server.get("/signup", new ShowSignup());
		server.post("/signup", new SignupHandler());
		server.get("/logout", new LogoutHandler());
		server.post("/logout", new LogoutHandler());
		server.get("/pub_home", new ShowPubHome());
		server.get("/film_submit", new ShowFilmSubmit());
		server.post("/film_submit", new FilmSubmitHandler());
		server.get("/pub_profile", new ShowPubProfile());
		server.get("/cus_home", new ShowCusHome());
		server.get("/cus_profile", new ShowCusProfile());
		server.post("/film_detail", new FilmDetailHandler());
		server.get("/notifications", new ShowNotifications());
		server.post("/buy", new BuyHandler());
		server.post("/rate", new RateHandler());
		server.get("/pub_bank", new ShowPubBank());
		server.get("/cus_bank", new ShowCusBank());
		server.post("/charge_wallet", new ChargeWalletHandler());
		server.post("/receive_debt", new ReceiveDebtHandler());
		server.get("/published_films", new ShowPublishedFilms());
		server.post("/delete_film", new DeleteFilmHandler());
		server.post("/edit_film", new EditFilmHandler());
		server.get("/edit_film", new ShowEditFilm());
		server.post("/add_comment", new AddCommentHandler());
		server.run();
  } catch (Server::Exception e) {
    std::cerr << e.getMessage() << std::endl;
  }
}