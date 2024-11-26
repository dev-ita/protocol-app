
#include "protocol.hpp"
#include "db_connection.hpp"
#include <iostream>

void ProtocolRepository::setupDatabase() {
  try {
    // Conexão com o banco de dados criado
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    // Criação da tabela protocolos
    txn.exec(R"(
    CREATE TABLE IF NOT EXISTS protocolos (
        id SERIAL PRIMARY KEY,
        data DATE NOT NULL,
        matricula INT REFERENCES users(matricula),
        categoria TEXT NOT NULL,
        assunto TEXT NOT NULL,
        justificativa TEXT NOT NULL,
        setor TEXT NOT NULL,
        status TEXT NOT NULL
      );
    )");

    txn.commit();

    std::cout << "Table 'protocolos' created or exists already.\n";
  } catch (const std::exception &e) {
    std::cerr << "Error creating table: " << e.what() << std::endl;
  }
}

bool ProtocolRepository::insertProtocol(const std::string &data, int matricula,
                                        const std::string &categoria,
                                        const std::string &assunto,
                                        const std::string &justificativa,
                                        const std::string &setor,
                                        const std::string &status) {
  try {
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    txn.exec_params(
        "INSERT INTO protocolos (data, matricula, categoria, assunto, "
        "justificativa, setor, status) VALUES ($1, $2, $3, $4, $5, $6, $7)",
        data, matricula, categoria, assunto, justificativa, setor, status);

    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error inserting protocol: " << e.what() << std::endl;
    return false;
  }
}

std::vector<crow::json::wvalue>
ProtocolRepository::getProtocolsByMatricula(int matricula) {
  std::vector<crow::json::wvalue> protocols;
  try {
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    pqxx::result result = txn.exec_params(
        "SELECT * FROM protocolos WHERE matricula = $1", matricula);

    for (const auto &row : result) {
      crow::json::wvalue protocol;
      protocol["id"] = row["id"].as<int>();
      protocol["data"] = row["data"].as<std::string>();
      protocol["categoria"] = row["categoria"].as<std::string>();
      protocol["assunto"] = row["assunto"].as<std::string>();
      protocol["justificativa"] = row["justificativa"].as<std::string>();
      protocol["setor"] = row["setor"].as<std::string>();
      protocol["status"] = row["status"].as<std::string>();
      protocols.push_back(protocol);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error fetching protocols: " << e.what() << std::endl;
  }
  return protocols;
}

bool ProtocolRepository::updateProtocol(int id, const std::string &status) {
  try {
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    txn.exec_params("UPDATE protocolos SET status = $1 WHERE id = $2", status,
                    id);

    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error updating protocol: " << e.what() << std::endl;
    return false;
  }
}

bool ProtocolRepository::deleteProtocol(int id) {
  try {
    pqxx::connection conn = get_connection();
    pqxx::work txn(conn);

    txn.exec_params("DELETE FROM protocolos WHERE id = $1", id);

    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error deleting protocol: " << e.what() << std::endl;
    return false;
  }
}
