#include "../routes/routes.hpp"
#include "../db/users.hpp"

crow::response registerUser(const crow::request &req) {
  auto data = crow::json::load(req.body);
  if (!data)
    return crow::response(400, "Invalid JSON");

  if (UserRepository::insertUser(data["matricula"].s(), data["nome"].s(), data["email"].s(),
                           data["senha"].s(), data["turma"].s(),
                           data["endereco"].s(), data["tipo"].s(),
                           data["data"].s())) {
    return crow::response(201, "User registered successfully");
  }
  return crow::response(500, "Error registering user");
}

crow::response loginUser(const crow::request &req) {
  auto data = crow::json::load(req.body);
  if (!data)
    return crow::response(400, "Invalid JSON");

  if (UserRepository::authenticateUser(data["email"].s(), data["senha"].s())) {
    return crow::response(200, "Login successful");
  }
  return crow::response(401, "Invalid credentials");
}
