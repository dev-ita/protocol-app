#include "db/users.hpp"
#include "routes/routes.hpp"
#include <crow.h>

int main() {

  UserRepository::setupDatabase();

  crow::SimpleApp app;

  CROW_ROUTE(app, "/register").methods("POST"_method)(registerUser);
  CROW_ROUTE(app, "/login").methods("POST"_method)(loginUser);

  app.port(8080).multithreaded().run();
}
