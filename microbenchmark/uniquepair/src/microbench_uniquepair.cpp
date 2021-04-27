// Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
// Systems

#include <stdlib.h>
#include <time.h>

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include <buzzblog/uniquepair_client.h>
#include <cppmicrobench.h>
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


// Add unique pairs to domain 'microbench' (Cartesian product of sets with the
// specified interval).
void initialize_dataset(const std::string& host, const int port,
    const int min_elem, const int max_elem) {
  auto uniquepair_client = get_uniquepair_client(host, port);
  for (auto first_elem = min_elem; first_elem <= max_elem; first_elem++)
    for (auto second_elem = min_elem; second_elem <= max_elem; second_elem++)
      uniquepair_client->add("microbench", first_elem, second_elem);
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
////////////////////////////////// OPERATIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// 'add' operation.
bool add_operation(const std::string& host, const int port, const int min_elem,
    const int max_elem) {
  bool status = true;
  auto uniquepair_client = get_uniquepair_client(host, port);
  try {
    uniquepair_client->add("microbench", RANDINT(min_elem, max_elem),
        RANDINT(min_elem, max_elem));
  }
  catch (...) {
    // Operation failed.
    status = false;
  }
  uniquepair_client->close();
  return status;
}


// 'get' operation.
bool get_operation(const std::string& host, const int port, const int min_id,
    const int max_id) {
  bool status = true;
  auto uniquepair_client = get_uniquepair_client(host, port);
  try {
    uniquepair_client->get(RANDINT(min_id, max_id));
  }
  catch (...) {
    // Operation failed.
    status = false;
  }
  uniquepair_client->close();
  return status;
}


// 'find' operation.
bool find_operation(const std::string& host, const int port, const int min_elem,
    const int max_elem) {
  bool status = true;
  auto uniquepair_client = get_uniquepair_client(host, port);
  try {
    uniquepair_client->find("microbench", RANDINT(min_elem, max_elem),
        RANDINT(min_elem, max_elem));
  }
  catch (...) {
    // Operation failed.
    status = false;
  }
  uniquepair_client->close();
  return status;
}


// 'fetch' operation.
bool fetch_operation(const std::string& host, const int port, const int limit,
    const int min_offset, const int max_offset) {
  bool status = true;
  auto uniquepair_client = get_uniquepair_client(host, port);
  TUniquepairQuery query;
  query.__set_domain("microbench");
  try {
    uniquepair_client->fetch(query, limit, RANDINT(min_offset, max_offset));
  }
  catch (...) {
    // Operation failed.
    status = false;
  }
  uniquepair_client->close();
  return status;
}


// 'count' operation.
bool count_operation(const std::string& host, const int port,
    const int min_first_elem, const int max_first_elem) {
  bool status = true;
  auto uniquepair_client = get_uniquepair_client(host, port);
  TUniquepairQuery query;
  query.__set_domain("microbench");
  query.__set_first_elem(RANDINT(min_first_elem, max_first_elem));
  try {
    uniquepair_client->count(query);
  }
  catch (...) {
    // Operation failed.
    status = false;
  }
  uniquepair_client->close();
  return status;
}


// 'remove' operation.
bool remove_operation(const std::string& host, const int port, const int min_id,
    const int max_id) {
  bool status = true;
  auto uniquepair_client = get_uniquepair_client(host, port);
  try {
    uniquepair_client->remove(RANDINT(min_id, max_id));
  }
  catch (...) {
    // Operation failed.
    status = false;
  }
  uniquepair_client->close();
  return status;
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
      ("output_dirpath", "Path to the output directory",
          cxxopts::value<std::string>())
      ("n_worker_threads", "Number of worker threads to execute the tasks",
          cxxopts::value<int>()->default_value("4"))
      // 'add' microbenchmark parameters.
      ("add_max_rate", "Max number of requests per second ('add')",
          cxxopts::value<double>()->default_value("32.0"))
      ("add_duration_sec", "Duration in seconds ('add')",
          cxxopts::value<int>()->default_value("60"))
      ("add_ramp_up_time_sec", "Ramp up time in seconds ('add')",
          cxxopts::value<int>()->default_value("60"))
      ("add_ramp_down_time_sec", "Ramp down time in seconds ('add')",
          cxxopts::value<int>()->default_value("60"))
      // 'get' microbenchmark parameters.
      ("get_max_rate", "Max number of requests per second ('get')",
          cxxopts::value<double>()->default_value("32.0"))
      ("get_duration_sec", "Duration in seconds ('get')",
          cxxopts::value<int>()->default_value("60"))
      ("get_ramp_up_time_sec", "Ramp up time in seconds ('get')",
          cxxopts::value<int>()->default_value("60"))
      ("get_ramp_down_time_sec", "Ramp down time in seconds ('get')",
          cxxopts::value<int>()->default_value("60"))
      // 'find' microbenchmark parameters.
      ("find_max_rate", "Max number of requests per second ('find')",
          cxxopts::value<double>()->default_value("32.0"))
      ("find_duration_sec", "Duration in seconds ('find')",
          cxxopts::value<int>()->default_value("60"))
      ("find_ramp_up_time_sec", "Ramp up time in seconds ('find')",
          cxxopts::value<int>()->default_value("60"))
      ("find_ramp_down_time_sec", "Ramp down time in seconds ('find')",
          cxxopts::value<int>()->default_value("60"))
      // 'fetch' microbenchmark parameters.
      ("fetch_max_rate", "Max number of requests per second ('fetch')",
          cxxopts::value<double>()->default_value("32.0"))
      ("fetch_duration_sec", "Duration in seconds ('fetch')",
          cxxopts::value<int>()->default_value("60"))
      ("fetch_ramp_up_time_sec", "Ramp up time in seconds ('fetch')",
          cxxopts::value<int>()->default_value("60"))
      ("fetch_ramp_down_time_sec", "Ramp down time in seconds ('fetch')",
          cxxopts::value<int>()->default_value("60"))
      // 'count' microbenchmark parameters.
      ("count_max_rate", "Max number of requests per second ('count')",
          cxxopts::value<double>()->default_value("32.0"))
      ("count_duration_sec", "Duration in seconds ('count')",
          cxxopts::value<int>()->default_value("60"))
      ("count_ramp_up_time_sec", "Ramp up time in seconds ('count')",
          cxxopts::value<int>()->default_value("60"))
      ("count_ramp_down_time_sec", "Ramp down time in seconds ('count')",
          cxxopts::value<int>()->default_value("60"))
      // 'remove' microbenchmark parameters.
      ("remove_max_rate", "Max number of requests per second ('remove')",
          cxxopts::value<double>()->default_value("32.0"))
      ("remove_duration_sec", "Duration in seconds ('remove')",
          cxxopts::value<int>()->default_value("60"))
      ("remove_ramp_up_time_sec", "Ramp up time in seconds ('remove')",
          cxxopts::value<int>()->default_value("60"))
      ("remove_ramp_down_time_sec", "Ramp down time in seconds ('remove')",
          cxxopts::value<int>()->default_value("60"));

  // Parse command-line arguments.
  auto result = options.parse(argc, argv);
  auto host = result["host"].as<std::string>();
  auto port = result["port"].as<int>();
  auto output_dirpath = result["output_dirpath"].as<std::string>();
  auto n_worker_threads = result["n_worker_threads"].as<int>();
  // 'add' microbenchmark parameters.
  auto add_max_rate = result["add_max_rate"].as<double>();
  auto add_duration_sec = result["add_duration_sec"].as<int>();
  auto add_ramp_up_time_sec = result["add_ramp_up_time_sec"].as<int>();
  auto add_ramp_down_time_sec = result["add_ramp_down_time_sec"].as<int>();
  // 'get' microbenchmark parameters.
  auto get_max_rate = result["get_max_rate"].as<double>();
  auto get_duration_sec = result["get_duration_sec"].as<int>();
  auto get_ramp_up_time_sec = result["get_ramp_up_time_sec"].as<int>();
  auto get_ramp_down_time_sec = result["get_ramp_down_time_sec"].as<int>();
  // 'find' microbenchmark parameters.
  auto find_max_rate = result["find_max_rate"].as<double>();
  auto find_duration_sec = result["find_duration_sec"].as<int>();
  auto find_ramp_up_time_sec = result["find_ramp_up_time_sec"].as<int>();
  auto find_ramp_down_time_sec = result["find_ramp_down_time_sec"].as<int>();
  // 'fetch' microbenchmark parameters.
  auto fetch_max_rate = result["fetch_max_rate"].as<double>();
  auto fetch_duration_sec = result["fetch_duration_sec"].as<int>();
  auto fetch_ramp_up_time_sec = result["fetch_ramp_up_time_sec"].as<int>();
  auto fetch_ramp_down_time_sec = result["fetch_ramp_down_time_sec"].as<int>();
  // 'count' microbenchmark parameters.
  auto count_max_rate = result["count_max_rate"].as<double>();
  auto count_duration_sec = result["count_duration_sec"].as<int>();
  auto count_ramp_up_time_sec = result["count_ramp_up_time_sec"].as<int>();
  auto count_ramp_down_time_sec = result["count_ramp_down_time_sec"].as<int>();
  // 'remove' microbenchmark parameters.
  auto remove_max_rate = result["remove_max_rate"].as<double>();
  auto remove_duration_sec = result["remove_duration_sec"].as<int>();
  auto remove_ramp_up_time_sec = result["remove_ramp_up_time_sec"].as<int>();
  auto remove_ramp_down_time_sec = result["remove_ramp_down_time_sec"].as<int>();

  // Initialize random seed.
  srand(time(NULL));

  // Initialize microbench dataset.
  const int initial_dataset_min_elem = 1;
  const int initial_dataset_max_elem = 64;
  initialize_dataset(host, port, initial_dataset_min_elem,
      initial_dataset_max_elem);

  // Run 'add' microbenchmark.
  {
    const int min_elem = initial_dataset_max_elem + 1;
    const int max_elem = 4294967295;
    run_microbenchmark(n_worker_threads, output_dirpath,
        MicrobenchmarkWorkloadSpec{
            MicrobenchmarkTask{"add", std::bind(add_operation, host, port,
                min_elem, max_elem)},
            add_max_rate, add_duration_sec, add_ramp_up_time_sec,
            add_ramp_down_time_sec});
  }
  // Run 'get' microbenchmark.
  {
    const int min_id = 1;
    const int max_id = dataset_size(host, port);
    run_microbenchmark(n_worker_threads, output_dirpath,
        MicrobenchmarkWorkloadSpec{
            MicrobenchmarkTask{"get", std::bind(get_operation, host, port,
                min_id, max_id)},
            get_max_rate, get_duration_sec, get_ramp_up_time_sec,
            get_ramp_down_time_sec});
  }
  // Run 'find' microbenchmark.
  {
    const int min_elem = initial_dataset_min_elem;
    const int max_elem = initial_dataset_max_elem;
    run_microbenchmark(n_worker_threads, output_dirpath,
        MicrobenchmarkWorkloadSpec{
            MicrobenchmarkTask{"find", std::bind(find_operation, host, port,
                min_elem, max_elem)},
            find_max_rate, find_duration_sec, find_ramp_up_time_sec,
            find_ramp_down_time_sec});
  }
  // Run 'fetch' microbenchmark.
  {
    const int limit = 32;
    const int min_offset = 1;
    const int max_offset = dataset_size(host, port) - limit;
    run_microbenchmark(n_worker_threads, output_dirpath,
        MicrobenchmarkWorkloadSpec{
            MicrobenchmarkTask{"fetch", std::bind(fetch_operation, host, port,
                limit, min_offset, max_offset)},
            fetch_max_rate, fetch_duration_sec, fetch_ramp_up_time_sec,
            fetch_ramp_down_time_sec});
  }
  // Run 'count' microbenchmark.
  {
    const int min_first_elem = initial_dataset_min_elem;
    const int max_first_elem = initial_dataset_max_elem;
    run_microbenchmark(n_worker_threads, output_dirpath,
        MicrobenchmarkWorkloadSpec{
            MicrobenchmarkTask{"count", std::bind(count_operation, host, port,
                min_first_elem, max_first_elem)},
            count_max_rate, count_duration_sec, count_ramp_up_time_sec,
            count_ramp_down_time_sec});
  }
  // Run 'remove' microbenchmark.
  {
    const int min_id = 1;
    const int max_id = dataset_size(host, port);
    run_microbenchmark(n_worker_threads, output_dirpath,
        MicrobenchmarkWorkloadSpec{
            MicrobenchmarkTask{"remove", std::bind(remove_operation, host, port,
                min_id, max_id)},
            remove_max_rate, remove_duration_sec, remove_ramp_up_time_sec,
            remove_ramp_down_time_sec});
  }

  return 0;
}
