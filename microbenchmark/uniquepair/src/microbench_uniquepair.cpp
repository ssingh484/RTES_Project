// Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
// Systems

#include <stdlib.h>
#include <time.h>

#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include <buzzblog/uniquepair_client.h>
#include <cppbench.h>
#include <cxxopts.hpp>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// UTILITIES ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


#define RANDINT(a, b) (rand() % ((b) - (a) + 1) + (a))


// Return a connection to the Uniquepair service.
std::unique_ptr<uniquepair_service::Client> get_uniquepair_client(
    const std::string& host, const int port) {
  return std::move(std::make_unique<uniquepair_service::Client>(host, port,
      10000));
}


// Add the specified number of unique pairs (with negative values) to domain
// 'microbench'.
void initialize_dataset(const std::string& host, const int& port,
    const int& size) {
  auto uniquepair_client = get_uniquepair_client(host, port);
  for (auto i = 1; i <= size; i++)
    uniquepair_client->add("microbench", -RANDINT(1, 2147483647),
        -RANDINT(1, 2147483647));
  uniquepair_client->close();
}


// Return the number of unique pairs in domain 'microbench'.
int dataset_size(const std::string& host, const int port) {
  TUniquepairQuery query;
  query.__set_domain("microbench");
  auto uniquepair_client = get_uniquepair_client(host, port);
  auto count = uniquepair_client->count(query);
  uniquepair_client->close();
  return count;
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// 'get'
void get_function(const std::string& host, const int& port, const int& id) {
  auto uniquepair_client = get_uniquepair_client(host, port);
  uniquepair_client->get(id);
  uniquepair_client->close();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv) {
  // Define command-line parameters.
  cxxopts::Options options("microbench_uniquepair",
      "Uniquepair microbenchmark");
  options.add_options()
      ("host", "Uniquepair service host",
          cxxopts::value<std::string>()->default_value("0.0.0.0"))
      ("port", "Uniquepair service port",
          cxxopts::value<int>())
      ("initial_dataset_size", "Initial number of unique pairs",
          cxxopts::value<int>())
      ("output_dirpath", "Path to the output directory",
          cxxopts::value<std::string>())
      // 'add' microbenchmark parameters.
      ("add_count", "Number of calls to function 'add'",
          cxxopts::value<int>()->default_value("1000000"))
      // 'get' microbenchmark parameters.
      ("get_count", "Number of calls to function 'get'",
          cxxopts::value<int>()->default_value("1000000"))
      // 'find' microbenchmark parameters.
      ("find_count", "Number of calls to function 'find'",
          cxxopts::value<int>()->default_value("1000000"))
      // 'fetch' microbenchmark parameters.
      ("fetch_count", "Number of calls to function 'fetch'",
          cxxopts::value<int>()->default_value("1000000"))
      // 'count' microbenchmark parameters.
      ("count_count", "Number of calls to function 'count'",
          cxxopts::value<int>()->default_value("1000000"))
      // 'remove' microbenchmark parameters.
      ("remove_count", "Number of calls to function 'remove'",
          cxxopts::value<int>()->default_value("1000000"));
  // Parse command-line arguments.
  auto result = options.parse(argc, argv);
  auto host = result["host"].as<std::string>();
  auto port = result["port"].as<int>();
  auto initial_dataset_size = result["initial_dataset_size"].as<int>();
  auto output_dirpath = result["output_dirpath"].as<std::string>();
  auto add_count = result["add_count"].as<int>();
  auto get_count = result["get_count"].as<int>();
  auto find_count = result["find_count"].as<int>();
  auto fetch_count = result["fetch_count"].as<int>();
  auto count_count = result["count_count"].as<int>();
  auto remove_count = result["remove_count"].as<int>();

  // Initialize random seed.
  srand(time(NULL));

  // Initialize dataset.
  initialize_dataset(host, port, initial_dataset_size);

  // Run 'add' microbenchmark.
  {
  }
  // Run 'get' microbenchmark.
  {
    int id = 1;
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("get.csv");
    run_benchmark(std::bind(get_function, host, port, id), nullptr, nullptr,
        get_count, 120, output_filepath.string());
  }
  // Run 'find' microbenchmark.
  {
  }
  // Run 'fetch' microbenchmark.
  {
  }
  // Run 'count' microbenchmark.
  {
  }
  // Run 'remove' microbenchmark.
  {
  }

  return 0;
}
