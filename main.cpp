#include "db/users.hpp"
#include "routes/routes.hpp"
#include <crow.h>
#include <crow/app.h>
#include <crow/middlewares/cors.h>

int main() {

  UserRepository::setupDatabase();

  crow::App<crow::CORSHandler> app;

  auto &cors = app.get_middleware<crow::CORSHandler>();

  cors.global()
      .headers("X-Custom-Header", "Upgrade-Insecure-Requests", "Content-Type",
               "Origin", "Accept", "Authorization", "Refresh")
      .methods("POST"_method, "GET"_method, "PUT"_method, "DELETE"_method)
      .origin("*");

  CROW_ROUTE(app, "/register").methods("POST"_method)(registerUser);
  CROW_ROUTE(app, "/login").methods("POST"_method)(loginUser);
  CROW_ROUTE(app, "/user/<string>").methods("GET"_method)(getUserByMatricula);


  app.port(8080).multithreaded().run();
}
