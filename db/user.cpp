#include "user.hpp"
#include "db_connection.hpp"
#include <crow.h>
#include <exception>
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
                data DATE NOT NULL,
                telefone TEXT NOT NULL,
                campus TEXT NOT NULL,
                curso TEXT NOT NULL
            );
        )");
    txn.commit();

    std::cout << "Table 'users' created or exists already.\n";
  } catch (const std::exception &e) {
    std::cerr << "Error creating table: " << e.what() << std::endl;
  }
}

bool UserRepository::insertUser(
    const std::string &matricula, const std::string &nome,
    const std::string &email, const std::string &senha,
    const std::string &turma, const std::string &endereco,
    const std::string &tipo, const std::string &data, const std::string &telefone, const std::string &campus, const std::string &curso) {
  try {

    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    txn.exec_params(
        "INSERT INTO users (matricula, nome, email, senha, turma, endereco, "
        "tipo, data, telefone, campus, curso) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11)",
        matricula, nome, email, senha, turma, endereco, tipo, data, telefone);
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

crow::json::wvalue
UserRepository::getUserByMatricula(const std::string &matricula) {
  try {
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    // Query para buscar o usuário pela matrícula
    std::string query = "SELECT * FROM users WHERE matricula = $1";
    pqxx::result result = txn.exec_params(query, matricula);

    if (result.empty()) {
      return {{"error", "Usuário não encontrado"}};
    }

    // Obtendo os dados do usuário
    const auto &row = result[0];
    crow::json::wvalue user;
    user["matricula"] = row["matricula"].as<std::string>();
    user["nome"] = row["nome"].as<std::string>();
    user["email"] = row["email"].as<std::string>();
    user["turma"] = row["turma"].as<std::string>();
    user["endereco"] = row["endereco"].as<std::string>();
    user["tipo"] = row["tipo"].as<std::string>();
    user["data"] = row["data"].as<std::string>();
    user["telefone"] = row["telefone"].as<std::string>();
    user["campus"] = row["campus"].as<std::string>();
    user["curso"] = row["curso"].as<std::string>();
    return user;

  } catch (const std::exception &e) {
    return {{"error", e.what()}};
  }
}

crow::json::wvalue UserRepository::getUserByEmail(const std::string &email) {
  try {
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    // Query para buscar o usuário pela matrícula
    std::string query = "SELECT * FROM users WHERE email = $1";
    pqxx::result result = txn.exec_params(query, email);

    if (result.empty()) {
      return {{"error", "Usuário não encontrado"}};
    }

    // Obtendo os dados do usuário
    const auto &row = result[0];
    crow::json::wvalue user;
    user["matricula"] = row["matricula"].as<std::string>();
    user["nome"] = row["nome"].as<std::string>();
    user["email"] = row["email"].as<std::string>();
    user["turma"] = row["turma"].as<std::string>();
    user["endereco"] = row["endereco"].as<std::string>();
    user["tipo"] = row["tipo"].as<std::string>();
    user["data"] = row["data"].as<std::string>();
    user["telefone"] = row["telefone"].as<std::string>();
    user["campus"] = row["campus"].as<std::string>();
    user["curso"] = row["curso"].as<std::string>();
    return user;

  } catch (const std::exception &e) {
    return {{"error", e.what()}};
  }
}
