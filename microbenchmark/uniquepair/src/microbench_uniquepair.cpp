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


// Return a connection to the Uniquepair service.
std::unique_ptr<uniquepair_service::Client> get_client(const std::string& host,
    const int& port) {
  return std::move(std::make_unique<uniquepair_service::Client>(host, port,
      10000));
}


// Add the specified number of (random) unique pairs to the domain.
void initialize_dataset(const std::string& host, const int& port,
    const std::string& domain, const int& size) {
  auto client = get_client(host, port);
  for (auto i = 1; i <= size; i++)
    client->add(domain, i, i);
  client->close();
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class GetMicrobench {
 private:
  std::unique_ptr<uniquepair_service::Client> client;
  int id;

 public:
  GetMicrobench(const std::string& host, const int& port) {
    client = get_client(host, port);
    id = client->add("microbench", 0, 0).id;
  }

  ~GetMicrobench() {
    client->remove(id);
    client->close();
  }

  void set_up() {
  }

  void function() {
    client->get(id);
  }

  void tear_down() {
  }
};


class AddMicrobench {
 private:
  std::unique_ptr<uniquepair_service::Client> client;
  int id;

 public:
  AddMicrobench(const std::string& host, const int& port) {
    client = get_client(host, port);
  }

  ~AddMicrobench() {
    client->close();
  }

  void set_up() {
  }

  void function() {
    id = client->add("microbench", 0, 0).id;
  }

  void tear_down() {
    client->remove(id);
  }
};


class RemoveMicrobench {
 private:
  std::unique_ptr<uniquepair_service::Client> client;
  int id;

 public:
  RemoveMicrobench(const std::string& host, const int& port) {
    client = get_client(host, port);
  }

  ~RemoveMicrobench() {
    client->close();
  }

  void set_up() {
    id = client->add("microbench", 0, 0).id;
  }

  void function() {
    client->remove(id);
  }

  void tear_down() {
  }
};


class FindMicrobench {
 private:
  std::unique_ptr<uniquepair_service::Client> client;
  int id;

 public:
  FindMicrobench(const std::string& host, const int& port) {
    client = get_client(host, port);
    id = client->add("microbench", 0, 0).id;
  }

  ~FindMicrobench() {
    client->remove(id);
    client->close();
  }

  void set_up() {
  }

  void function() {
    client->find("microbench", 0, 0);
  }

  void tear_down() {
  }
};


class FetchMicrobench {
 private:
  std::unique_ptr<uniquepair_service::Client> client;
  TUniquepairQuery query;
  std::vector<int> ids;

 public:
  FetchMicrobench(const std::string& host, const int& port) {
    client = get_client(host, port);
    for (auto i = 1; i <= 32; i++)
      ids.push_back(client->add("fetch", i, i).id);
    query.__set_domain("fetch");
  }

  ~FetchMicrobench() {
    for (auto id : ids)
      client->remove(id);
    client->close();
  }

  void set_up() {
  }

  void function() {
    client->fetch(query, 32, 0);
  }

  void tear_down() {
  }
};


class CountMicrobench {
 private:
  std::unique_ptr<uniquepair_service::Client> client;
  TUniquepairQuery query;
  std::vector<int> ids;

 public:
  CountMicrobench(const std::string& host, const int& port) {
    client = get_client(host, port);
    for (auto i = 1; i <= 1024; i++)
      ids.push_back(client->add("count", i, i).id);
    query.__set_domain("count");
  }

  ~CountMicrobench() {
    for (auto id : ids)
      client->remove(id);
    client->close();
  }

  void set_up() {
  }

  void function() {
    client->count(query);
  }

  void tear_down() {
  }
};


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
      ("max_calls", "Max number of calls to a benchmarked function",
          cxxopts::value<int>()->default_value("1000000"))
      ("max_duration", "Max duration of a benchmark in seconds",
          cxxopts::value<int>()->default_value("600"));
  // Parse command-line arguments.
  auto result = options.parse(argc, argv);
  auto host = result["host"].as<std::string>();
  auto port = result["port"].as<int>();
  auto initial_dataset_size = result["initial_dataset_size"].as<int>();
  auto output_dirpath = result["output_dirpath"].as<std::string>();
  auto max_calls = result["max_calls"].as<int>();
  auto max_duration = result["max_duration"].as<int>();

  // Initialize random seed.
  srand(time(NULL));

  // Initialize dataset.
  initialize_dataset(host, port, "microbench", initial_dataset_size);

  // Run 'get' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("get.csv");
    auto microbench = GetMicrobench(host, port);
    run_benchmark(std::bind(&GetMicrobench::function, &microbench),
        std::bind(&GetMicrobench::set_up, &microbench),
        std::bind(&GetMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'add' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("add.csv");
    auto microbench = AddMicrobench(host, port);
    run_benchmark(std::bind(&AddMicrobench::function, &microbench),
        std::bind(&AddMicrobench::set_up, &microbench),
        std::bind(&AddMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }

  // Run 'remove' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("remove.csv");
    auto microbench = RemoveMicrobench(host, port);
    run_benchmark(std::bind(&RemoveMicrobench::function, &microbench),
        std::bind(&RemoveMicrobench::set_up, &microbench),
        std::bind(&RemoveMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }

  // Run 'find' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("find.csv");
    auto microbench = FindMicrobench(host, port);
    run_benchmark(std::bind(&FindMicrobench::function, &microbench),
        std::bind(&FindMicrobench::set_up, &microbench),
        std::bind(&FindMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'fetch' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("fetch.csv");
    auto microbench = FetchMicrobench(host, port);
    run_benchmark(std::bind(&FetchMicrobench::function, &microbench),
        std::bind(&FetchMicrobench::set_up, &microbench),
        std::bind(&FetchMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'count' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("count.csv");
    auto microbench = CountMicrobench(host, port);
    run_benchmark(std::bind(&CountMicrobench::function, &microbench),
        std::bind(&CountMicrobench::set_up, &microbench),
        std::bind(&CountMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }

  return 0;
}
