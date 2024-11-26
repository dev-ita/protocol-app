#include <crow.h>
#include "../routes/user_routes.hpp"
#include "../db/user.hpp"

crow::response registerUser(const crow::request &req) {
  auto data = crow::json::load(req.body);
  if (!data)
    return crow::response(400, "Invalid JSON");

  if (UserRepository::insertUser(data["matricula"].s(), data["nome"].s(),
                                 data["email"].s(), data["senha"].s(),
                                 data["turma"].s(), data["endereco"].s(),
                                 data["tipo"].s(), data["data"].s())) {
    return crow::response(201, "User registered successfully");
  }
  return crow::response(500, "Error registering user");
}

crow::response loginUser(const crow::request &req) {
  auto data = crow::json::load(req.body);
  if (!data)
    return crow::response(400, "Invalid JSON");

  if (UserRepository::authenticateUser(data["email"].s(), data["senha"].s())) {
    auto user = UserRepository::getUserByEmail(data["email"].s());

    user["status"] = "Login successful";

    return user;
  }
  return crow::response(401, "Invalid credentials");
}

crow::response getUserByMatricula(const std::string &matricula) {
  return UserRepository::getUserByMatricula(matricula);
}
