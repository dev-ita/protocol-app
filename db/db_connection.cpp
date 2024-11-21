#include <pqxx/pqxx>

pqxx::connection get_connection() {
  pqxx::connection conn(
      "dbname=protocol_app user=postgres password=password123");
  return conn;
}
