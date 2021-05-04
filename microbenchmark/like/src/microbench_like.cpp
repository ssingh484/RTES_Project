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
#include <buzzblog/post_client.h>
#include <buzzblog/like_client.h>
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


// Return a connection to the Post service.
std::unique_ptr<post_service::Client> get_post_client(
    const std::string& host, const int port) {
  return std::move(std::make_unique<post_service::Client>(host, port, 10000));
}


// Return a connection to the Like service.
std::unique_ptr<like_service::Client> get_like_client(
    const std::string& host, const int port) {
  return std::move(std::make_unique<like_service::Client>(host, port, 10000));
}


// Create the specified number of likes.
void initialize_dataset(const std::string& account_host, const int account_port,
    const std::string& post_host, const int post_port,
    const std::string& like_host, const int like_port, const int size) {
  // Create account.
  auto account_client = get_account_client(account_host, account_port);
  account_client->create_account("gburdell", "passwd", "George", "Burdell");
  account_client->close();
  // Create posts.
  auto post_client = get_post_client(post_host, post_port);
  for (auto i = 1; i <= size + 1; i++)
    post_client->create_post(1, "Lorem ipsum dolor sit amet.");
  post_client->close();
  // Create likes.
  auto like_client = get_like_client(like_host, like_port);
  for (auto i = 2; i <= size + 1; i++)
    like_client->like_post(1, i);
  like_client->close();
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class LikePostMicrobench {
 private:
  std::unique_ptr<like_service::Client> like_client;
  int like_id;

 public:
  LikePostMicrobench(const std::string& host, const int port) {
    like_client = get_like_client(host, port);
  }

  ~LikePostMicrobench() {
    like_client->close();
  }

  void set_up() {
  }

  void function() {
    like_id = like_client->like_post(1, 1).id;
  }

  void tear_down() {
    like_client->delete_like(1, like_id);
  }
};


class RetrieveStandardLikeMicrobench {
 private:
  std::unique_ptr<like_service::Client> like_client;
  int like_id;

 public:
  RetrieveStandardLikeMicrobench(const std::string& host, const int port) {
    like_client = get_like_client(host, port);
    like_id = like_client->like_post(1, 1).id;
  }

  ~RetrieveStandardLikeMicrobench() {
    like_client->delete_like(1, like_id);
    like_client->close();
  }

  void set_up() {
  }

  void function() {
    like_client->retrieve_standard_like(1, like_id);
  }

  void tear_down() {
  }
};


class RetrieveExpandedLikeMicrobench {
 private:
  std::unique_ptr<like_service::Client> like_client;
  int like_id;

 public:
  RetrieveExpandedLikeMicrobench(const std::string& host, const int port) {
    like_client = get_like_client(host, port);
    like_id = like_client->like_post(1, 1).id;
  }

  ~RetrieveExpandedLikeMicrobench() {
    like_client->delete_like(1, like_id);
    like_client->close();
  }

  void set_up() {
  }

  void function() {
    like_client->retrieve_expanded_like(1, like_id);
  }

  void tear_down() {
  }
};


class DeleteLikeMicrobench {
 private:
  std::unique_ptr<like_service::Client> like_client;
  int like_id;

 public:
  DeleteLikeMicrobench(const std::string& host, const int port) {
    like_client = get_like_client(host, port);
  }

  ~DeleteLikeMicrobench() {
    like_client->close();
  }

  void set_up() {
    like_id = like_client->like_post(1, 1).id;
  }

  void function() {
    like_client->delete_like(1, like_id);
  }

  void tear_down() {
  }
};


class ListLikesMicrobench {
 private:
  std::unique_ptr<like_service::Client> like_client;
  TLikeQuery query;
  int like_id;

 public:
  ListLikesMicrobench(const std::string& host, const int port) {
    like_client = get_like_client(host, port);
    like_id = like_client->like_post(1, 1).id;
    query.__set_post_id(1);
  }

  ~ListLikesMicrobench() {
    like_client->delete_like(1, like_id);
    like_client->close();
  }

  void set_up() {
  }

  void function() {
    like_client->list_likes(1, query, 32, 0);
  }

  void tear_down() {
  }
};


class CountLikesByAccountMicrobench {
 private:
  std::unique_ptr<like_service::Client> like_client;
  int like_id;

 public:
  CountLikesByAccountMicrobench(const std::string& host, const int port) {
    like_client = get_like_client(host, port);
    like_id = like_client->like_post(1, 1).id;
  }

  ~CountLikesByAccountMicrobench() {
    like_client->delete_like(1, like_id);
    like_client->close();
  }

  void set_up() {
  }

  void function() {
    like_client->count_likes_by_account(1, 1);
  }

  void tear_down() {
  }
};


class CountLikesOfPostMicrobench {
 private:
  std::unique_ptr<like_service::Client> like_client;
  int like_id;

 public:
  CountLikesOfPostMicrobench(const std::string& host, const int port) {
    like_client = get_like_client(host, port);
    like_id = like_client->like_post(1, 1).id;
  }

  ~CountLikesOfPostMicrobench() {
    like_client->delete_like(1, like_id);
    like_client->close();
  }

  void set_up() {
  }

  void function() {
    like_client->count_likes_of_post(1, 1);
  }

  void tear_down() {
  }
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv) {
  // Define command-line parameters.
  cxxopts::Options options("microbench_like",
      "Like microbenchmark");
  options.add_options()
      ("account_host", "Account service host",
          cxxopts::value<std::string>()->default_value("0.0.0.0"))
      ("account_port", "Account service port",
          cxxopts::value<int>())
      ("post_host", "Post service host",
          cxxopts::value<std::string>()->default_value("0.0.0.0"))
      ("post_port", "Post service port",
          cxxopts::value<int>())
      ("like_host", "Like service host",
          cxxopts::value<std::string>()->default_value("0.0.0.0"))
      ("like_port", "Like service port",
          cxxopts::value<int>())
      ("initial_dataset_size", "Initial number of likes",
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
  auto post_host = result["post_host"].as<std::string>();
  auto post_port = result["post_port"].as<int>();
  auto like_host = result["like_host"].as<std::string>();
  auto like_port = result["like_port"].as<int>();
  auto initial_dataset_size = result["initial_dataset_size"].as<int>();
  auto output_dirpath = result["output_dirpath"].as<std::string>();
  auto max_calls = result["max_calls"].as<int>();
  auto max_duration = result["max_duration"].as<int>();

  // Initialize random seed.
  srand(time(NULL));

  // Initialize dataset.
  initialize_dataset(account_host, account_port, post_host, post_port,
      like_host, like_port, initial_dataset_size);

  // Run 'like_post' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("like_post.csv");
    auto microbench = LikePostMicrobench(like_host, like_port);
    run_benchmark(std::bind(&LikePostMicrobench::function, &microbench),
        std::bind(&LikePostMicrobench::set_up, &microbench),
        std::bind(&LikePostMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'retrieve_standard_like' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("retrieve_standard_like.csv");
    auto microbench = RetrieveStandardLikeMicrobench(like_host, like_port);
    run_benchmark(std::bind(&RetrieveStandardLikeMicrobench::function,
        &microbench),
        std::bind(&RetrieveStandardLikeMicrobench::set_up, &microbench),
        std::bind(&RetrieveStandardLikeMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'retrieve_expanded_like' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("retrieve_expanded_like.csv");
    auto microbench = RetrieveExpandedLikeMicrobench(like_host, like_port);
    run_benchmark(std::bind(&RetrieveExpandedLikeMicrobench::function,
        &microbench),
        std::bind(&RetrieveExpandedLikeMicrobench::set_up, &microbench),
        std::bind(&RetrieveExpandedLikeMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'delete_like' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("delete_like.csv");
    auto microbench = DeleteLikeMicrobench(like_host, like_port);
    run_benchmark(std::bind(&DeleteLikeMicrobench::function, &microbench),
        std::bind(&DeleteLikeMicrobench::set_up, &microbench),
        std::bind(&DeleteLikeMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'list_likes' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("list_likes.csv");
    auto microbench = ListLikesMicrobench(like_host, like_port);
    run_benchmark(std::bind(&ListLikesMicrobench::function, &microbench),
        std::bind(&ListLikesMicrobench::set_up, &microbench),
        std::bind(&ListLikesMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'count_likes_by_account' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("count_likes_by_account.csv");
    auto microbench = CountLikesByAccountMicrobench(like_host, like_port);
    run_benchmark(std::bind(&CountLikesByAccountMicrobench::function,
        &microbench),
        std::bind(&CountLikesByAccountMicrobench::set_up, &microbench),
        std::bind(&CountLikesByAccountMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }
  // Run 'count_likes_of_post' microbenchmark.
  {
    auto output_filepath = std::filesystem::path(output_dirpath) /
        std::filesystem::path("count_likes_of_post.csv");
    auto microbench = CountLikesOfPostMicrobench(like_host, like_port);
    run_benchmark(std::bind(&CountLikesOfPostMicrobench::function, &microbench),
        std::bind(&CountLikesOfPostMicrobench::set_up, &microbench),
        std::bind(&CountLikesOfPostMicrobench::tear_down, &microbench),
        max_calls, max_duration, output_filepath.string());
  }

  return 0;
}
