// Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
// Systems

#include <sstream>
#include <string>

#include <cxxopts.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>

#include <buzzblog/gen/TUniquepairService.h>

/******************************** COMMENTED OUT ********************************
#include <pqxx/pqxx>
#include <buzzblog/base_server.h>
*******************************************************************************/

/********************************* ADDED BEGIN ********************************/
#include <filesystem>
#include <functional>
#include <memory>
#include <vector>
#include <utility>
#include <cppbench.h>
/********************************** ADDED END *********************************/


using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace gen;


class TUniquepairServiceHandler : public TUniquepairServiceIf {
private:
  std::string build_where_clause(const TUniquepairQuery& query) {
    std::ostringstream where_clause;
    where_clause << "domain = '" << query.domain << "'";
    if (query.__isset.first_elem)
      where_clause << " AND first_elem = " << query.first_elem;
    if (query.__isset.second_elem)
      where_clause << " AND second_elem = " << query.second_elem;
    return where_clause.str();
  }

public:
/******************************** COMMENTED OUT ********************************
  TUniquepairServiceHandler(const std::string& backend_filepath,
      const std::string& postgres_user, const std::string& postgres_password,
      const std::string& postgres_dbname)
  : BaseServer(backend_filepath, postgres_user, postgres_password,
      postgres_dbname) {
  }
*******************************************************************************/

  void get(TUniquepair& _return, const int32_t uniquepair_id) {
    // Build query string.
    char query_str[1024];
    const char *query_fmt = \
        "SELECT created_at, domain, first_elem, second_elem "
        "FROM Uniquepairs "
        "WHERE id = %d";
    sprintf(query_str, query_fmt, uniquepair_id);

/******************************** COMMENTED OUT ********************************
    // Execute query.
    pqxx::connection conn(uniquepair_db_conn_str);
    pqxx::work txn(conn);
    pqxx::result db_res(txn.exec(query_str));
    txn.commit();
    conn.disconnect();

    // Check if unique pair exists.
    if (db_res.begin() == db_res.end())
      throw TUniquepairNotFoundException();

    // Build unique pair.
    _return.id = uniquepair_id;
    _return.created_at = db_res[0][0].as<int>();
    _return.domain = db_res[0][1].as<std::string>();
    _return.first_elem = db_res[0][2].as<int>();
    _return.second_elem = db_res[0][3].as<int>();
*******************************************************************************/

/********************************* ADDED BEGIN ********************************/
    // Build unique pair.
    _return.id = uniquepair_id;
    _return.created_at = 0;
    _return.domain = "domain";
    _return.first_elem = 1;
    _return.second_elem = 2;
/********************************** ADDED END *********************************/
  }

  void add(TUniquepair& _return, const std::string& domain,
      const int32_t first_elem, const int32_t second_elem) {
    // Build query string.
    char query_str[1024];
    const char *query_fmt = \
        "INSERT INTO Uniquepairs (domain, first_elem, second_elem, created_at) "
        "VALUES ('%s', %d, %d, extract(epoch from now())) "
        "RETURNING id, created_at";
    sprintf(query_str, query_fmt, domain.c_str(), first_elem, second_elem);

/******************************** COMMENTED OUT ********************************
    // Execute query.
    pqxx::connection conn(uniquepair_db_conn_str);
    pqxx::work txn(conn);
    pqxx::result db_res;
    try {
      db_res = txn.exec(query_str);
    }
    catch (pqxx::sql_error& e) {
      throw TUniquepairAlreadyExistsException();
    }
    txn.commit();
    conn.disconnect();

    // Build unique pair.
    _return.id = db_res[0][0].as<int>();
    _return.created_at = db_res[0][1].as<int>();
    _return.domain = domain;
    _return.first_elem = first_elem;
    _return.second_elem = second_elem;
*******************************************************************************/

/********************************* ADDED BEGIN ********************************/
    // Build unique pair.
    _return.id = 1;
    _return.created_at = 0;
    _return.domain = domain;
    _return.first_elem = first_elem;
    _return.second_elem = second_elem;
/********************************** ADDED END *********************************/
  }

  void remove(const int32_t uniquepair_id) {
    // Build query string.
    char query_str[1024];
    const char *query_fmt = \
        "DELETE FROM Uniquepairs "
        "WHERE id = %d "
        "RETURNING id";
    sprintf(query_str, query_fmt, uniquepair_id);

/******************************** COMMENTED OUT ********************************
    // Execute query.
    pqxx::connection conn(uniquepair_db_conn_str);
    pqxx::work txn(conn);
    pqxx::result db_res(txn.exec(query_str));
    txn.commit();
    conn.disconnect();

    // Check if unique pair exists.
    if (db_res.begin() == db_res.end())
      throw TUniquepairNotFoundException();
*******************************************************************************/
  }

  void find(TUniquepair& _return, const std::string& domain,
      const int32_t first_elem, const int32_t second_elem) {
    // Build query string.
    char query_str[1024];
    const char *query_fmt = \
        "SELECT id, created_at "
        "FROM Uniquepairs "
        "WHERE domain = '%s' AND first_elem = %d AND second_elem = %d";
    sprintf(query_str, query_fmt, domain.c_str(), first_elem, second_elem);

/******************************** COMMENTED OUT ********************************
    // Execute query.
    pqxx::connection conn(uniquepair_db_conn_str);
    pqxx::work txn(conn);
    pqxx::result db_res(txn.exec(query_str));
    txn.commit();
    conn.disconnect();

    // Check if unique pair exists.
    if (db_res.begin() == db_res.end())
      throw TUniquepairNotFoundException();

    // Build unique pair.
    _return.id = db_res[0][0].as<int>();
    _return.created_at = db_res[0][1].as<int>();
    _return.domain = domain;
    _return.first_elem = first_elem;
    _return.second_elem = second_elem;
*******************************************************************************/

/********************************* ADDED BEGIN ********************************/
    // Build unique pair.
    _return.id = 1;
    _return.created_at = 0;
    _return.domain = domain;
    _return.first_elem = first_elem;
    _return.second_elem = second_elem;
/********************************** ADDED END *********************************/
  }

  void fetch(std::vector<TUniquepair>& _return, const TUniquepairQuery& query,
      const int32_t limit, const int32_t offset) {
    // Build query string.
    char query_str[1024];
    const char *query_fmt = \
        "SELECT id, created_at, first_elem, second_elem "
        "FROM Uniquepairs "
        "WHERE %s "
        "ORDER BY created_at DESC "
        "LIMIT %d "
        "OFFSET %d";
    sprintf(query_str, query_fmt, build_where_clause(query).c_str(), limit,
        offset);

/******************************** COMMENTED OUT ********************************
    // Execute query.
    pqxx::connection conn(uniquepair_db_conn_str);
    pqxx::work txn(conn);
    pqxx::result db_res(txn.exec(query_str));
    txn.commit();
    conn.disconnect();

    // Build unique pairs.
    for (auto row : db_res) {
      // Build unique pair.
      TUniquepair uniquepair;
      uniquepair.id = row["id"].as<int>();
      uniquepair.created_at = row["created_at"].as<int>();
      uniquepair.domain = query.domain;
      uniquepair.first_elem = row["first_elem"].as<int>();
      uniquepair.second_elem = row["second_elem"].as<int>();
      _return.push_back(uniquepair);
    }
*******************************************************************************/

/********************************* ADDED BEGIN ********************************/
    // Build unique pairs.
    for (int i = 1; i <= limit; i++) {
      // Build unique pair.
      TUniquepair uniquepair;
      uniquepair.id = i;
      uniquepair.created_at = 0;
      uniquepair.domain = query.domain;
      uniquepair.first_elem = 1;
      uniquepair.second_elem = 2;
      _return.push_back(uniquepair);
    }
/********************************** ADDED END *********************************/
  }

  int32_t count(const TUniquepairQuery& query) {
    // Build query string.
    char query_str[1024];
    const char *query_fmt = \
        "SELECT COUNT(*) "
        "FROM Uniquepairs "
        "WHERE %s";
    sprintf(query_str, query_fmt, build_where_clause(query).c_str());

/******************************** COMMENTED OUT ********************************
    // Execute query.
    pqxx::connection conn(uniquepair_db_conn_str);
    pqxx::work txn(conn);
    pqxx::result db_res(txn.exec(query_str));
    txn.commit();
    conn.disconnect();

    return db_res[0][0].as<int>();
*******************************************************************************/

/********************************* ADDED BEGIN ********************************/
    return 0;
/********************************** ADDED END *********************************/
  }
};


int main(int argc, char** argv) {
  // Define command-line parameters.
  cxxopts::Options options("uniquepair_baseline_server",
      "Uniquepair baseline server");
  options.add_options()
      ("server", "Server flag",
          cxxopts::value<bool>()->default_value("true"))
      ("host", "", cxxopts::value<std::string>()->default_value("0.0.0.0"))
      ("port", "", cxxopts::value<int>()->default_value("9094"))
      ("output_dirpath", "Path to the output directory",
          cxxopts::value<std::string>()->default_value(""))
      ("max_calls", "Max number of calls to a benchmarked function",
          cxxopts::value<int>()->default_value("0"))
      ("max_duration", "Max duration of a benchmark in seconds",
          cxxopts::value<int>()->default_value("0"));
  // Parse command-line arguments.
  auto result = options.parse(argc, argv);
  auto server_flag = result["server"].as<bool>();
  auto host = result["host"].as<std::string>();
  auto port = result["port"].as<int>();
  auto output_dirpath = result["output_dirpath"].as<std::string>();
  auto max_calls = result["max_calls"].as<int>();
  auto max_duration = result["max_duration"].as<int>();

  if (!output_dirpath.empty() && max_calls > 0 && max_duration > 0) {
    // Run 'get' microbenchmark.
    {
      auto output_filepath = std::filesystem::path(output_dirpath) /
          std::filesystem::path("get.csv");
      auto microbench = TUniquepairServiceHandler();
      TUniquepair _return;
      run_benchmark(
          std::bind(&TUniquepairServiceHandler::get, &microbench, _return, 1),
          nullptr, nullptr,
          max_calls, max_duration, output_filepath.string());
    }
    // Run 'add' microbenchmark.
    {
      auto output_filepath = std::filesystem::path(output_dirpath) /
          std::filesystem::path("add.csv");
      auto microbench = TUniquepairServiceHandler();
      TUniquepair _return;
      run_benchmark(
          std::bind(&TUniquepairServiceHandler::add, &microbench, _return,
              "domain", 1, 2),
          nullptr, nullptr,
          max_calls, max_duration, output_filepath.string());
    }
    // Run 'remove' microbenchmark.
    {
      auto output_filepath = std::filesystem::path(output_dirpath) /
          std::filesystem::path("remove.csv");
      auto microbench = TUniquepairServiceHandler();
      run_benchmark(
          std::bind(&TUniquepairServiceHandler::remove, &microbench, 1),
          nullptr, nullptr,
          max_calls, max_duration, output_filepath.string());
    }
    // Run 'find' microbenchmark.
    {
      auto output_filepath = std::filesystem::path(output_dirpath) /
          std::filesystem::path("find.csv");
      auto microbench = TUniquepairServiceHandler();
      TUniquepair _return;
      run_benchmark(
          std::bind(&TUniquepairServiceHandler::find, &microbench, _return,
              "domain", 1, 2),
          nullptr, nullptr,
          max_calls, max_duration, output_filepath.string());
    }
    // Run 'fetch' microbenchmark.
    {
      auto output_filepath = std::filesystem::path(output_dirpath) /
          std::filesystem::path("fetch.csv");
      auto microbench = TUniquepairServiceHandler();
      std::vector<TUniquepair> _return;
      TUniquepairQuery query;
      query.__set_domain("domain");
      run_benchmark(
          std::bind(&TUniquepairServiceHandler::fetch, &microbench, _return,
              query, 32, 0),
          nullptr, nullptr,
          max_calls, max_duration, output_filepath.string());
    }
    // Run 'count' microbenchmark.
    {
      auto output_filepath = std::filesystem::path(output_dirpath) /
          std::filesystem::path("count.csv");
      auto microbench = TUniquepairServiceHandler();
      TUniquepairQuery query;
      query.__set_domain("domain");
      run_benchmark(
          std::bind(&TUniquepairServiceHandler::count, &microbench, query),
          nullptr, nullptr,
          max_calls, max_duration, output_filepath.string());
    }
  }
  if (server_flag) {
    // Create server.
    TThreadedServer server(
        std::make_shared<TUniquepairServiceProcessor>(
            std::make_shared<TUniquepairServiceHandler>()),
        std::make_shared<TServerSocket>(host, port),
        std::make_shared<TBufferedTransportFactory>(),
        std::make_shared<TBinaryProtocolFactory>());
    server.setConcurrentClientLimit(1);
    // Serve requests.
    server.serve();
  }

  return 0;
}
