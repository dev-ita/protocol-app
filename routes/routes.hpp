#ifndef ROUTES_HPP
#define ROUTES_HPP

#include <crow.h>

// users
crow::response registerUser(const crow::request &req);
crow::response loginUser(const crow::request &req);
crow::response getUserByMatricula(const std::string &matricula);

#endif
