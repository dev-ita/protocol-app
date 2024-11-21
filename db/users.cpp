#include "users.hpp"
#include "db_connection.hpp"
#include <iostream>

void UserRepository::setupDatabase() {
  try {
    // Conexão com o PostgreSQL
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    // Tenta criar o banco de dados se ele não existir
    txn.exec("CREATE DATABASE protocol_app;");
    txn.commit();

    std::cout << "Database 'protocol_app' created or exists already.\n";
  } catch (const std::exception &e) {
    std::cerr << "Error creating or checking database: " << e.what()
              << std::endl;
  }

  try {
    // Conexão com o banco de dados criado
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    // Criação da tabela users
    txn.exec(R"(
            CREATE TABLE IF NOT EXISTS users (
                matricula SERIAL PRIMARY KEY,
                nome TEXT NOT NULL,
                email TEXT UNIQUE NOT NULL,
                senha TEXT NOT NULL,
                turma TEXT NOT NULL,
                endereco TEXT NOT NULL,
                tipo TEXT NOT NULL,
                data DATE NOT NULL
            );
        )");
    txn.commit();

    std::cout << "Table 'users' created or exists already.\n";
  } catch (const std::exception &e) {
    std::cerr << "Error creating table: " << e.what() << std::endl;
  }
}

bool UserRepository::insertUser(const std::string &matricula, const std::string &nome,
                          const std::string &email, const std::string &senha,
                          const std::string &turma, const std::string &endereco,
                          const std::string &tipo, const std::string &data) {
  try {

    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    txn.exec_params(
        "INSERT INTO users (matricula, nome, email, senha, turma, endereco, "
        "tipo, data) VALUES ($1, $2, $3, $4, $5, $6, $7, $8)",
        matricula, nome, email, senha, turma, endereco, tipo, data);
    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error inserting user: " << e.what() << std::endl;
    return false;
  }
}

bool UserRepository::authenticateUser(const std::string &email,
                                const std::string &senha) {
  try {
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    pqxx::result res = txn.exec_params(
        "SELECT * FROM users WHERE email = $1 AND senha = $2", email, senha);

    return !res.empty(); // Retorna verdadeiro se o resultado não estiver vazio.
  } catch (const std::exception &e) {
    std::cerr << "Error authenticating user: " << e.what() << std::endl;
    return false;
  }
}
