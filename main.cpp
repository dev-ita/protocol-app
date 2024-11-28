#include "db/protocol.hpp"
#include "db/user.hpp"
#include "routes/protocol_routes.hpp"
#include "routes/user_routes.hpp"
#include <crow.h>
#include <crow/app.h>
#include <crow/middlewares/cors.h>

int main() {

  UserRepository::setupDatabase();
  ProtocolRepository::setupDatabase();

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

  CROW_ROUTE(app, "/protocol").methods("POST"_method)(addProtocol);
  CROW_ROUTE(app, "/protocols/<string>").methods("GET"_method)(listProtocols);
  CROW_ROUTE(app, "/protocol/<int>").methods("PUT"_method)(updateProtocol);
  CROW_ROUTE(app, "/protocol/<int>").methods("DELETE"_method)(deleteProtocol);
  CROW_ROUTE(app, "/protocols").methods("GET"_method)(getAllProtocols);
  CROW_ROUTE(app, "/protocol/<int>").methods("GET"_method)(getProtocolById);

  app.port(8080).multithreaded().run();
}
