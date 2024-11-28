#include "protocol_routes.hpp"
#include "../db/protocol.hpp"

crow::response addProtocol(const crow::request &req) {
  auto data = crow::json::load(req.body);
  if (!data)
    return crow::response(400, "Invalid JSON");

  if (ProtocolRepository::insertProtocol(data["data"].s(), data["matricula"].i(),
                                         data["categoria"].s(),
                                         data["assunto"].s(),
                                         data["justificativa"].s(),
                                         data["setor"].s(),
                                         data["status"].s())) {
    return crow::response(201, "Protocol added successfully");
  }
  return crow::response(500, "Error adding protocol");
}

crow::response listProtocols(const std::string &matricula) {
  int mat = std::stoi(matricula);
  auto protocols = ProtocolRepository::getProtocolsByMatricula(mat);
  return crow::json::wvalue(protocols);
}

crow::response updateProtocol(const crow::request &req, int id) {
  auto data = crow::json::load(req.body);
  if (!data || !data["status"])
    return crow::response(400, "Invalid JSON");

  if (ProtocolRepository::updateProtocol(id, data["status"].s())) {
    return crow::response(200, "Protocol updated successfully");
  }
  return crow::response(500, "Error updating protocol");
}

crow::response deleteProtocol(int id) {
  if (ProtocolRepository::deleteProtocol(id)) {
    return crow::response(200, "Protocol deleted successfully");
  }
  return crow::response(500, "Error deleting protocol");
}

crow::response getAllProtocols() {
  try {
    auto protocols = ProtocolRepository::getAllProtocols();
    return crow::json::wvalue(protocols);
  } catch (const std::exception &e) {
    return crow::response(500, e.what());
  }
}

crow::response getProtocolById(int id) {
  return ProtocolRepository::getProtocolById(id);
}
