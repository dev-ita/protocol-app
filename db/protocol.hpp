#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <crow.h>
#include <pqxx/pqxx>
#include <vector>

class ProtocolRepository {
public:
  static void setupDatabase();
  static std::vector<crow::json::wvalue> getAllProtocols();
  static bool insertProtocol(const std::string &data, int matricula,
                             const std::string &categoria,
                             const std::string &assunto,
                             const std::string &justificativa,
                             const std::string &setor,
                             const std::string &status);

  static std::vector<crow::json::wvalue> getProtocolsByMatricula(int matricula);

  static bool updateProtocol(int id, const std::string &status);

  static bool deleteProtocol(int id);

  static crow::json::wvalue getProtocolById(int id);
};

#endif
