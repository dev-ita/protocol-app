#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <crow.h>
#include <pqxx/pqxx>

class UserRepository {
public:
  static void setupDatabase();
  static bool insertUser(const std::string &matricula, const std::string &nome,
                         const std::string &email, const std::string &senha,
                         const std::string &turma, const std::string &endereco,
                         const std::string &tipo, const std::string &data, const std::string &telefone);
  static bool authenticateUser(const std::string &email,
                               const std::string &senha);
  static crow::json::wvalue getUserByMatricula(const std::string &matricula);
  
  static crow::json::wvalue
  getUserByEmail(const std::string &email); };

#endif // !DATABASE_HPP
