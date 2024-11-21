#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <pqxx/pqxx>

class UserRepository {
public:
  static void setupDatabase();
  static bool insertUser(const std::string &matricula, const std::string &nome, const std::string &email,
                         const std::string &senha, const std::string &turma,
                         const std::string &endereco, const std::string &tipo,
                         const std::string &data);
  static bool authenticateUser(const std::string &email,
                               const std::string &senha);
};

#endif // !DATABASE_HPP
