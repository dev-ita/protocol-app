#include <pqxx/pqxx>

#ifndef DB_CONNECTION_HPP
#define DB_CONNECTION_HPP

pqxx::connection get_connection();

#endif // !DB_CONNECTION_HPP

