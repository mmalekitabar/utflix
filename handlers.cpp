#include "handlers.hpp"
#define NUM_START 48
#define NUM_END 57
#define START 0
#define EMPTY 0

using namespace std;

int to_num(string snum)
{
  if(snum.size() == EMPTY)
    return 0;
  for(int i = START; i < snum.size(); i++)
  {
    if(snum[i] > NUM_END || snum[i] < NUM_START)
      return -1;
  }
  return stoi(snum);
}

Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
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
  int sid;
  if(!loggingin)
    sid = loggingin->get_id();
  Response *res;
  if(loggingin->is_publisher())
    res = Response::redirect("/pub_home");
  else
    res = Response::redirect("/cos_home");
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
    res = Response::redirect("/cos_home");
  res->setSessionId(to_string(sid));
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

Response *UploadHandler::callback(Request *req) {
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");
  cout << name << " (" << file.size() << "B):\n" << file << endl;
  Response *res = Response::redirect("/");
  return res;
}

ColorHandler::ColorHandler(string filePath) : TemplateHandler(filePath) {}

map<string, string> ColorHandler::handle(Request *req) {
  map<string, string> context;
  string newName = "I am " + req->getQueryParam("name");
  context["name"] = newName;
  context["color"] = req->getQueryParam("color");
  return context;
}
