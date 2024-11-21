#ifndef ROUTES_HPP
#define ROUTES_HPP

#include <crow.h>

crow::response registerUser(const crow::request &req);
crow::response loginUser(const crow::request &req);

#endif
