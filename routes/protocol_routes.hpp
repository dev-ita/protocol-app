#ifndef PROTOCOL_ROUTES_HPP
#define PROTOCOL_ROUTES_HPP

#include <crow.h>

crow::response addProtocol(const crow::request &req);
crow::response listProtocols(const std::string &matricula);
crow::response updateProtocol(const crow::request &req, int id);
crow::response deleteProtocol(int id);
crow::response getAllProtocols();
crow::response getProtocolById(int id);

#endif
