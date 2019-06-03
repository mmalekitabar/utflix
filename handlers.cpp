#include "handlers.hpp"
#define NUM_START 48
#define NUM_END 57
#define START 0
#define EMPTY 0

using namespace std;

int to_num(string snum) {
  if(snum.size() == EMPTY)
    return 0;
  for(int i = START; i < snum.size(); i++)
  {
    if(snum[i] > NUM_END || snum[i] < NUM_START)
      return -1;
  }
  return stoi(snum);
}

Response *LoginHandler::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  if(to_num(req->getSessionId()) < end_id && to_num(req->getSessionId()) > 0)
    throw Server::Exception("There is someone loggedin at the moment.");
  map<string, string> informations;
  informations["username"] = req->getBodyParam("username");
  informations["password"] = req->getBodyParam("password");
  User* loggingin = users_repository->login_check(informations);
  int sid = loggingin->get_id();
  Response *res;
  if(loggingin->is_publisher())
    res = Response::redirect("/pub_home");
  else
    res = Response::redirect("/cus_home");
  res->setSessionId(to_string(sid));
  return res;
}

Response *SignupHandler::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  if(to_num(req->getSessionId()) < end_id && to_num(req->getSessionId()) > 0)
    throw Server::Exception("There is someone loggedin at the moment.");
  map<string, string> informations;
  informations["username"] = req->getBodyParam("username");
  informations["password"] = req->getBodyParam("password");
  string r_password = req->getBodyParam("r_password");
  informations["age"] = req->getBodyParam("age");
  informations["email"] = req->getBodyParam("email");
  informations["publisher"] = req->getBodyParam("publisher");
  int sid = (users_repository->add_user(informations))->get_id();
  if(r_password.size() == 0)
    throw Server::Exception("Please enter the repeat of your password.");
  else if(r_password != informations["password"])
    throw Server::Exception("The repeat of your password is not right, try again.");
  Response *res;
  if(informations["publisher"] == "true")
    res = Response::redirect("/pub_home");
  else
    res = Response::redirect("/cus_home");
  res->setSessionId(to_string(sid));
  return res;
}

Response *FilmSubmitHandler::callback(Request *req) {
  FilmsRepository* films_repository = films_repository->get_films_rep();
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  if(to_num(req->getSessionId()) >= end_id && to_num(req->getSessionId()) <= 0)
    throw Server::Exception("Login first.");
  if(!(users_repository->check_is_publisher(stoi(req->getSessionId()))))
    throw Server::Exception("You can not reach this page.");
  map<string, string> informations;
  informations["name"] = req->getBodyParam("name");
  informations["price"] = req->getBodyParam("price");
  informations["director"] = req->getBodyParam("director");
  informations["length"] = req->getBodyParam("length");
  informations["year"] = req->getBodyParam("year");
  informations["summary"] = req->getBodyParam("summary");
  films_repository->add_film(informations, stoi(req->getSessionId()));
  Response *res = Response::redirect("/pub_home");
  return res;
}

Response *FilmDetailHandler::callback(Request *req) {
  FilmsRepository* films_repository = films_repository->get_films_rep();
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  if(to_num(req->getSessionId()) >= end_id || to_num(req->getSessionId()) <= 0)
    throw Server::Exception("Login first.");
  int film_id = stoi(req->getBodyParam("id"));
  Film* showing_film = films_repository->get_film(film_id);
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  if(!(users_repository->check_is_publisher(stoi(req->getSessionId()))))
    body += "<a href=\"http://localhost:5000/cus_home\">back</a>";
  else
    body += "<a href=\"http://localhost:5000/pub_home\">back</a>";
  body += "<h1>UTFLIX</h1>";
  body += "<h2>film ";
  body += to_string(film_id);
  body += " detail</h2>";
  body += "<p style = \"font-size: 30px;\">Name: ";
  body += showing_film->get_name();
  body += "</p><p style = \"font-size: 30px;\">Length: ";
  body += to_string(showing_film->get_length());
  body += "</p><p style = \"font-size: 30px;\">Price: ";
  body += to_string(showing_film->get_price());
  body += "</p><p style = \"font-size: 30px;\">Rate: ";
  body += to_string(showing_film->get_rate());
  body += "</p><p style = \"font-size: 30px;\">Production Year: ";
  body += to_string(showing_film->get_year());
  body += "</p><p style = \"font-size: 30px;\">Director: ";
  body += showing_film->get_director();
  body += "</p><p style = \"font-size: 30px;\">Summary: ";
  body += showing_film->get_summary();
  body += "</p></body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *LogoutHandler::callback(Request *req) {
  if(req->getSessionId().size() == 0)
    throw Server::Exception("There is nobody loggedin at the moment.");
  Response *res = Response::redirect("/login");
  res->setSessionId("");
  return res;
}

Response *ShowLogin::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  if(to_num(req->getSessionId()) < end_id && to_num(req->getSessionId()) > 0)
    throw Server::Exception("There is someone loggedin at the moment.");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>UTFLIX</h1>";
  body += "<div style=\"background-color: lightblue; padding: 1%; max-width: 300px; border-radius: 3px; margin: auto; \">";
  body += "<form action=\"/login\" method=\"post\">";
  body += "<p>Login</p>";
  body += "<input name=\"username\" type=\"text\" required placeholder=\"Username\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%; \"  />";
  body += "<input name=\"password\" type=\"password\" required placeholder=\"Password\" style=\"display:block; margin: auto; margin-bottom: 30px; padding: 5px; width: 94%; \" />";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Login</button>";
  body += "<a href=\"http://localhost:5000/signup\">Signup</a>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowSignup::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  if(to_num(req->getSessionId()) < end_id && to_num(req->getSessionId()) > 0)
    throw Server::Exception("There is someone loggedin at the moment.");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>UTFLIX</h1>";
  body += "<div style=\"background-color: lightblue; padding: 1%; max-width: 300px; border-radius: 3px; margin: auto; \">";
  body += "<form action=\"/signup\" method=\"post\">";
  body += "<p>signup</p>";
  body += "<input name=\"username\" type=\"text\" required placeholder=\"Username\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"password\" type=\"password\" required placeholder=\"Password\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"r_password\" type=\"password\" required placeholder=\"Repeat Password\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"age\" type=\"text\" required placeholder=\"Age\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"email\" type=\"text\" required placeholder=\"Email\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "Publisher?";
  body += "<span>";
  body += "<input type=\"radio\" name=\"publisher\" value=\"true\"> YES";
  body += "<input type=\"radio\" name=\"publisher\" value=\"false\" checked> NO";
  body += "</span>";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Signup</button>";
  body += "<a href=\"http://localhost:5000/login\">Login</a>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowFilmSubmit::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  if(to_num(req->getSessionId()) >= end_id || to_num(req->getSessionId()) <= 0)
    throw Server::Exception("Login first.");
  if(!(users_repository->check_is_publisher(stoi(req->getSessionId()))))
    throw Server::Exception("You can not reach this page.");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>UTFLIX</h1>";
  body += "<div style=\"background-color: lightblue; padding: 1%; max-width: 300px; border-radius: 3px; margin: auto; \">";
  body += "<form action=\"/film_submit\" method=\"post\">";
  body += "<p>Film Submit</p>";
  body += "<input name=\"name\" type=\"text\" required placeholder=\"Name\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"price\" type=\"text\" required placeholder=\"Price\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"director\" type=\"text\" required placeholder=\"Director\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"length\" type=\"text\" required placeholder=\"Length\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"year\" type=\"text\" required placeholder=\"Production Year\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"summary\" type=\"text\" required placeholder=\"Summary\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Submit</button>";
  body += "<a href=\"http://localhost:5000/pub_home\">back</a>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowPubHome::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  FilmsRepository* films_repository = films_repository->get_films_rep();
  vector<Film*> all_films = films_repository->get_films();
  if(to_num(req->getSessionId()) >= end_id || to_num(req->getSessionId()) <= 0)
    throw Server::Exception("Login first.");
  if(!(users_repository->check_is_publisher(stoi(req->getSessionId()))))
    throw Server::Exception("You can not reach this page.");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>table, td, th {  border: 1px solid #ddd;text-align: left;}table {border-collapse: collapse;width: 100%;}th, td {padding: 15px;}</style></head>";
  body += "<body style=\"text-align: center;\">";
  body += "<a href=\"http://localhost:5000/logout\">Logout</a>";
  body += "<h1>HOME PAGE</h1>";
  body += "<h2>publisher</h2>";
  body += "<table>";
  body += "<tr>";
  body += "<th><-></th>";
  body += "<th>Name</th>";
  body += "<th>Price</th>";
  body += "<th>Production Year</th>";
  body += "<th>Length</th>";
  body += "<th>Rate</th>";
  body += "<th>Director</th>";
  body += "</tr>";
  for (int i = 0; i < all_films.size(); ++i)
  {
    body += "<tr><td>";
    body += "<form action=\"/film_detail\" method=\"post\">";
    body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">show detail</button>";
    body += "<input type=\"hidden\" name=\"id\" value=\"";
    body += to_string(all_films[i]->get_id());
    body += "\">";
    body += "</form>";
    body += "</td><td>";
    body += all_films[i]->get_name();
    body += "</td><td>";
    body += to_string(all_films[i]->get_price());
    body += "</td><td>";
    body += to_string(all_films[i]->get_year());
    body += "</td><td>";
    body += to_string(all_films[i]->get_length());
    body += "</td><td>";
    body += to_string(all_films[i]->get_rate());
    body += "</td><td>";
    body += all_films[i]->get_director();
    body += "</td></tr>";
  }
  body += "</table>";
  body += "<a href=\"http://localhost:5000/film_submit\">Submit Film  /</a>";
  body += "<a href=\"http://localhost:5000/pub_profile\">/  My Profile  /</a>";
  body += "<a href=\"http://localhost:5000/notifications\">/  Notifications</a>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowPubProfile::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  FilmsRepository* films_repository = films_repository->get_films_rep();
  vector<Film*> all_films = films_repository->get_films();
  if(to_num(req->getSessionId()) >= end_id || to_num(req->getSessionId()) <= 0)
    throw Server::Exception("Login first.");
  if(!(users_repository->check_is_publisher(stoi(req->getSessionId()))))
    throw Server::Exception("You can not reach this page.");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>table, td, th {  border: 1px solid #ddd;text-align: left;}table {border-collapse: collapse;width: 100%;}th, td {padding: 15px;}</style></head>";
  body += "<body style=\"text-align: center;\">";
  body += "<a href=\"http://localhost:5000/pub_home\">back</a>";
  body += "<h1>PROFILE</h1>";
  body += "<h2>publisher</h2>";
  body += "<table>";
  body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Price</th>";
  body += "<th>Production Year</th>";
  body += "<th>Length</th>";
  body += "<th>Rate</th>";
  body += "<th>Director</th>";
  body += "</tr>";
  for (int i = 0; i < all_films.size(); ++i)
  {
    body += "<tr><td>";
    body += all_films[i]->get_name();
    body += "</td><td>";
    body += to_string(all_films[i]->get_price());
    body += "</td><td>";
    body += to_string(all_films[i]->get_year());
    body += "</td><td>";
    body += to_string(all_films[i]->get_length());
    body += "</td><td>";
    body += to_string(all_films[i]->get_rate());
    body += "</td><td>";
    body += all_films[i]->get_director();
    body += "</td></tr>";
  }
  body += "</table>";
  
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowCusHome::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  FilmsRepository* films_repository = films_repository->get_films_rep();
  vector<Film*> all_films = films_repository->get_films();
  if(to_num(req->getSessionId()) >= end_id || to_num(req->getSessionId()) <= 0)
    throw Server::Exception("Login first.");
  if(users_repository->check_is_publisher(stoi(req->getSessionId())))
    throw Server::Exception("You can not reach this page.");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>table, td, th {  border: 1px solid #ddd;text-align: left;}table {border-collapse: collapse;width: 100%;}th, td {padding: 15px;}</style></head>";
  body += "<body style=\"text-align: center;\">";
  body += "<a href=\"http://localhost:5000/logout\">Logout</a>";
  body += "<h1>HOME PAGE</h1>";
  body += "<h2>costumer</h2>";
  body += "<table>";
  body += "<tr>";
  body += "<th><-></th>";
  body += "<th>Name</th>";
  body += "<th>Price</th>";
  body += "<th>Production Year</th>";
  body += "<th>Length</th>";
  body += "<th>Rate</th>";
  body += "<th>Director</th>";
  body += "</tr>";
  for (int i = 0; i < all_films.size(); ++i)
  {
    body += "<tr><td>";
    body += "<form action=\"/film_detail\" method=\"post\">";
    body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">show detail</button>";
    body += "<input type=\"hidden\" name=\"id\" value=\"";
    body += to_string(all_films[i]->get_id());
    body += "\">";
    body += "</form>";
    body += "</td><td>";
    body += all_films[i]->get_name();
    body += "</td><td>";
    body += to_string(all_films[i]->get_price());
    body += "</td><td>";
    body += to_string(all_films[i]->get_year());
    body += "</td><td>";
    body += to_string(all_films[i]->get_length());
    body += "</td><td>";
    body += to_string(all_films[i]->get_rate());
    body += "</td><td>";
    body += all_films[i]->get_director();
    body += "</td></tr>";
  }
  body += "</table>";
  body += "<a href=\"http://localhost:5000/cus_profile\">My Profile  /</a>";
  body += "<a href=\"http://localhost:5000/notifications\">/  Notifications</a>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowCusProfile::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  FilmsRepository* films_repository = films_repository->get_films_rep();
  vector<Film*> all_films = films_repository->get_films();
  if(to_num(req->getSessionId()) >= end_id || to_num(req->getSessionId()) <= 0)
    throw Server::Exception("Login first.");
  if(users_repository->check_is_publisher(stoi(req->getSessionId())))
    throw Server::Exception("You can not reach this page.");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>table, td, th {  border: 1px solid #ddd;text-align: left;}table {border-collapse: collapse;width: 100%;}th, td {padding: 15px;}</style></head>";
  body += "<body style=\"text-align: center;\">";
  body += "<a href=\"http://localhost:5000/cus_home\">back</a>";
  body += "<h1>PROFILE</h1>";
  body += "<h2>costumer</h2>";
  body += "<table>";
  body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Price</th>";
  body += "<th>Production Year</th>";
  body += "<th>Length</th>";
  body += "<th>Rate</th>";
  body += "<th>Director</th>";
  body += "</tr>";
  for (int i = 0; i < all_films.size(); ++i)
  {
    body += "<tr><td>";
    body += all_films[i]->get_name();
    body += "</td><td>";
    body += to_string(all_films[i]->get_price());
    body += "</td><td>";
    body += to_string(all_films[i]->get_year());
    body += "</td><td>";
    body += to_string(all_films[i]->get_length());
    body += "</td><td>";
    body += to_string(all_films[i]->get_rate());
    body += "</td><td>";
    body += all_films[i]->get_director();
    body += "</td></tr>";
  }
  body += "</table>";
  
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowNotifications::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
  int end_id = users_repository->get_last_id();
  FilmsRepository* films_repository = films_repository->get_films_rep();
  vector<Film*> all_films = films_repository->get_films();
  if(to_num(req->getSessionId()) >= end_id || to_num(req->getSessionId()) <= 0)
    throw Server::Exception("Login first.");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>table, td, th {  border: 1px solid #ddd;text-align: left;}table {border-collapse: collapse;width: 100%;}th, td {padding: 15px;}</style></head>";
  body += "<body style=\"text-align: center;\">";
  if(!(users_repository->check_is_publisher(stoi(req->getSessionId()))))
    body += "<a href=\"http://localhost:5000/cus_home\">back</a>";
  else
    body += "<a href=\"http://localhost:5000/pub_home\">back</a>";
  body += "<h1>Notifications</h1>";
  body += "<h2>...</h2>";
  body += "<table>";  
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}