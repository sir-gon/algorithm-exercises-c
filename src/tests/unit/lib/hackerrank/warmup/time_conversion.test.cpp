#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/warmup/time_conversion.h>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

TEST_CASE("time_conversion JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path =
      cwd.string() +
      "/unit/lib/hackerrank/warmup/time_conversion.testcases.json";

  INFO("time_conversion JSON test cases FILE: " << path);

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    std::string result_str(HACKERRANK_WARMUP_timeConversion(
        testcase["input"].get<std::string>().c_str()));
    CHECK(result_str == testcase["expected"]);
  }
}

TEST_CASE("time_conversion helper functions edge cases",
          "[hackerrank] [helper] [warmup]") {
  CHECK(HACKERRANK_WARMUP_firstN("", 10) == nullptr);
  CHECK(HACKERRANK_WARMUP_lastN("", 10) == nullptr);

  CHECK(HACKERRANK_WARMUP_firstN("", 0) == nullptr);
  CHECK(HACKERRANK_WARMUP_lastN("", 0) == nullptr);
}
