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
    char *result = HACKERRANK_WARMUP_timeConversion(
        testcase["input"].get<std::string>().c_str());

    std::string result_as_string(result);

    free(result);

    CHECK(result_as_string == testcase["expected"]);
  }
}

TEST_CASE("time_conversion edge cases", "[hackerrank] [helper] [warmup]") {
  CHECK(HACKERRANK_WARMUP_timeConversion(nullptr) == nullptr);

  CHECK(HACKERRANK_WARMUP_timeConversion("") == nullptr);

  CHECK(HACKERRANK_WARMUP_timeConversion("aa:bb:ccXM") == nullptr);
}
