// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#include <exercises/hackerrank/warmup/solve_me_first.h>

// std libs
#include <filesystem>
#include <fstream>

using json = nlohmann::json;

TEST_CASE("solveMeFirst JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path path = std::filesystem::path(__FILE__).parent_path() /
                               "solve_me_first.testcases.json";

  INFO("solveMeFirst JSON test cases FILE: " << path.string());

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    int result = HACKERRANK_WARMUP_solveMeFirst(testcase["a"], testcase["b"]);
    CHECK(result == testcase["expected"]);
  }
}
