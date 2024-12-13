#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/warmup/staircase.h>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

TEST_CASE("staircase", "[warmup]") {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path =
      cwd.string() + "/unit/lib/hackerrank/warmup/staircase.testcases.json";

  INFO("staircase JSON test cases FILE: " << path);

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    auto input = static_cast<int>(testcase["input"]);

    char **result = HACKERRANK_WARMUP_staircaseCalculate(input);

    std::vector<std::string> result_as_vector;

    for (int i = 0; i < input; i++) {
      result_as_vector.emplace_back(result[i]);
    }

    HACKERRANK_WARMUP_freeStaircase(result, input);

    CHECK(result_as_vector == testcase["expected"]);

    // Just call void function, to collect coverage
    HACKERRANK_WARMUP_staircase(input);
  }
}
