#include "handlers.hpp"

using namespace std;

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
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  //int sid = 
  Response *res = Response::redirect("/pub_home");
  res->setSessionId("SID");
  return res;
}

Response *SignupHandler::callback(Request *req) {
  UsersRepository* users_repository = users_repository->get_users_rep();
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
