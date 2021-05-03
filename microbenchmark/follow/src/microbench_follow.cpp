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

#include <buzzblog/account_client.h>
#include <buzzblog/follow_client.h>
#include <cppbench.h>
#include <cxxopts.hpp>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// UTILITIES ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// Return a connection to the Account service.
std::unique_ptr<account_service::Client> get_account_client(
    const std::string& host, const int port) {
  return std::move(std::make_unique<account_service::Client>(host, port, 10000));
}


// Return a connection to the Follow service.
std::unique_ptr<follow_service::Client> get_follow_client(
    const std::string& host, const int port) {
  return std::move(std::make_unique<follow_service::Client>(host, port, 10000));
}


// Create the specified number of follows.
void initialize_dataset(const std::string& account_host, const int account_port,
    const std::string& follow_host, const int follow_port, const int size) {
  // Create accounts.
  auto account_client = get_account_client(account_host, account_port);
  for (auto i = 1; i <= std::max(2, size + 1); i++)
    account_client->create_account("account_" + std::to_string(i), "passwd",
        "George", "Burdell");
  account_client->close();
  // Create follows.
  auto follow_client = get_follow_client(follow_host, follow_port);
  for (auto i = 1; i <= size; i++)
    follow_client->follow_account(1, i + 1);
  follow_client->close();
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class FollowAccountMicrobench {
 private:
  std::unique_ptr<follow_service::Client> follow_client;
  int follow_id;

 public:
  FollowAccountMicrobench(const std::string& host, const int port) {
    follow_client = get_follow_client(host, port);
  }

  ~FollowAccountMicrobench() {
    follow_client->close();
  }

  void set_up() {
  }

  void function() {
    follow_id = follow_client->follow_account(2, 1).id;
  }

  void tear_down() {
    follow_client->delete_follow(2, follow_id);
  }
};


class RetrieveStandardFollowMicrobench {
 private:
  std::unique_ptr<follow_service::Client> follow_client;
  int follow_id;

 public:
  RetrieveStandardFollowMicrobench(const std::string& host, const int port) {
    follow_client = get_follow_client(host, port);
    follow_id = follow_client->follow_account(2, 1).id;
  }

  ~RetrieveStandardFollowMicrobench() {
    follow_client->delete_follow(2, follow_id);
    follow_client->close();
  }

  void set_up() {
  }

  void function() {
    follow_client->retrieve_standard_follow(2, follow_id);
  }

  void tear_down() {
  }
};


class RetrieveExpandedFollowMicrobench {
 private:
  std::unique_ptr<follow_service::Client> follow_client;
  int follow_id;

 public:
  RetrieveExpandedFollowMicrobench(const std::string& host, const int port) {
    follow_client = get_follow_client(host, port);
    follow_id = follow_client->follow_account(2, 1).id;
  }

  ~RetrieveExpandedFollowMicrobench() {
    follow_client->delete_follow(2, follow_id);
    follow_client->close();
  }

  void set_up() {
  }

  void function() {
    follow_client->retrieve_expanded_follow(2, follow_id);
  }

  void tear_down() {
  }
};


class DeleteFollowMicrobench {
 private:
  std::unique_ptr<follow_service::Client> follow_client;
  int follow_id;

 public:
  DeleteFollowMicrobench(const std::string& host, const int port) {
    follow_client = get_follow_client(host, port);
  }

  ~DeleteFollowMicrobench() {
    follow_client->close();
  }

  void set_up() {
    follow_id = follow_client->follow_account(2, 1).id;
  }

  void function() {
    follow_client->delete_follow(2, follow_id);
  }

  void tear_down() {
  }
};


class ListFollowsMicrobench {
 private:
  std::unique_ptr<follow_service::Client> follow_client;
  TFollowQuery query;
  int follow_id;

 public:
  ListFollowsMicrobench(const std::string& host, const int port) {
    follow_client = get_follow_client(host, port);
    follow_id = follow_client->follow_account(2, 1).id;
    query.__set_follower_id(2);
  }

  ~ListFollowsMicrobench() {
    follow_client->delete_follow(2, follow_id);
    follow_client->close();
  }

  void set_up() {
  }

  void function() {
    follow_client->list_follows(2, query, 32, 0);
  }

  void tear_down() {
  }
};


class CheckFollowMicrobench {
 private:
  std::unique_ptr<follow_service::Client> follow_client;
  int follow_id;

 public:
  CheckFollowMicrobench(const std::string& host, const int port) {
    follow_client = get_follow_client(host, port);
    follow_id = follow_client->follow_account(2, 1).id;
  }

  ~CheckFollowMicrobench() {
    follow_client->delete_follow(2, follow_id);
    follow_client->close();
  }

  void set_up() {
  }

  void function() {
    follow_client->check_follow(2, 2, 1);
  }

  void tear_down() {
  }
};


class CountFollowersMicrobench {
 private:
  std::unique_ptr<follow_service::Client> follow_client;
  int follow_id;

 public:
  CountFollowersMicrobench(const std::string& host, const int port) {
    follow_client = get_follow_client(host, port);
    follow_id = follow_client->follow_account(2, 1).id;
  }

  ~CountFollowersMicrobench() {
    follow_client->delete_follow(2, follow_id);
    follow_client->close();
  }

  void set_up() {
  }

  void function() {
    follow_client->count_followers(2, 1);
  }

  void tear_down() {
  }
};


class CountFolloweesMicrobench {
 private:
  std::unique_ptr<follow_service::Client> follow_client;
  int follow_id;

 public:
  CountFolloweesMicrobench(const std::string& host, const int port) {
    follow_client = get_follow_client(host, port);
    follow_id = follow_client->follow_account(2, 1).id;
  }

  ~CountFolloweesMicrobench() {
    follow_client->delete_follow(2, follow_id);
    follow_client->close();
  }

  void set_up() {
  }

  void function() {
    follow_client->count_followees(2, 2);
  }

  void tear_down() {
  }
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv) {
  // Define command-line parameters.
  cxxopts::Options options("microbench_follow",
      "Follow microbenchmark");
  options.add_options()
      ("account_host", "Account service host",
          cxxopts::value<std::string>()->default_value("0.0.0.0"))
      ("account_port", "Account service port",
          cxxopts::value<int>())
      ("follow_host", "Follow service host",
          cxxopts::value<std::string>()->default_value("0.0.0.0"))
      ("follow_port", "Follow service port",
          cxxopts::value<int>())
      ("initial_dataset_size", "Initial number of follows",
          cxxopts::value<int>())
      ("output_dirpath", "Path to the output directory",
          cxxopts::value<std::string>())
      ("max_calls", "Max number of calls to a benchmarked function",
          cxxopts::value<int>()->default_value("1000000"))
      ("max_duration", "Max duration of a benchmark in seconds",
          cxxopts::value<int>()->default_value("600"));
  // Parse command-line arguments.
  auto result = options.parse(argc, argv);
  auto account_host = result["account_host"].as<std::string>();
  auto account_port = result["account_port"].as<int>();
  auto follow_host = result["follow_host"].as<std::string>();
  auto follow_port = result["follow_port"].as<int>();
  auto initial_dataset_size = result["initial_dataset_size"].as<int>();
  auto output_dirpath = result["output_dirpath"].as<std::string>();
  auto max_calls = result["max_calls"].as<int>();
  auto max_duration = result["max_duration"].as<int>();

  // Initialize random seed.
  srand(time(NULL));

  // Initialize dataset.
  initialize_dataset(account_host, account_port, follow_host, follow_port,
      initial_dataset_size);

  // Run 'follow_account' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("follow_account.csv");
    auto microbench = FollowAccountMicrobench(follow_host, follow_port);
    run_benchmark(std::bind(&FollowAccountMicrobench::function, &microbench),
        std::bind(&FollowAccountMicrobench::set_up, &microbench),
        std::bind(&FollowAccountMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'retrieve_standard_follow' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("retrieve_standard_follow.csv");
    auto microbench = RetrieveStandardFollowMicrobench(follow_host,
        follow_port);
    run_benchmark(std::bind(&RetrieveStandardFollowMicrobench::function,
        &microbench),
        std::bind(&RetrieveStandardFollowMicrobench::set_up, &microbench),
        std::bind(&RetrieveStandardFollowMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'retrieve_expanded_follow' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("retrieve_expanded_follow.csv");
    auto microbench = RetrieveExpandedFollowMicrobench(follow_host,
        follow_port);
    run_benchmark(std::bind(&RetrieveExpandedFollowMicrobench::function,
        &microbench),
        std::bind(&RetrieveExpandedFollowMicrobench::set_up, &microbench),
        std::bind(&RetrieveExpandedFollowMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'delete_follow' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("delete_follow.csv");
    auto microbench = DeleteFollowMicrobench(follow_host, follow_port);
    run_benchmark(std::bind(&DeleteFollowMicrobench::function, &microbench),
        std::bind(&DeleteFollowMicrobench::set_up, &microbench),
        std::bind(&DeleteFollowMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'list_follows' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("list_follows.csv");
    auto microbench = ListFollowsMicrobench(follow_host, follow_port);
    run_benchmark(std::bind(&ListFollowsMicrobench::function, &microbench),
        std::bind(&ListFollowsMicrobench::set_up, &microbench),
        std::bind(&ListFollowsMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'check_follow' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("check_follow.csv");
    auto microbench = CheckFollowMicrobench(follow_host, follow_port);
    run_benchmark(std::bind(&CheckFollowMicrobench::function, &microbench),
        std::bind(&CheckFollowMicrobench::set_up, &microbench),
        std::bind(&CheckFollowMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'count_followers' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("count_followers.csv");
    auto microbench = CountFollowersMicrobench(follow_host, follow_port);
    run_benchmark(std::bind(&CountFollowersMicrobench::function, &microbench),
        std::bind(&CountFollowersMicrobench::set_up, &microbench),
        std::bind(&CountFollowersMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'count_followees' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("count_followees.csv");
    auto microbench = CountFolloweesMicrobench(follow_host, follow_port);
    run_benchmark(std::bind(&CountFolloweesMicrobench::function, &microbench),
        std::bind(&CountFolloweesMicrobench::set_up, &microbench),
        std::bind(&CountFolloweesMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }

  return 0;
}
