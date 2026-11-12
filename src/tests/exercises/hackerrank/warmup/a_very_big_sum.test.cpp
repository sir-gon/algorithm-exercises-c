// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#include <exercises/hackerrank/warmup/a_very_big_sum.h>

// std libs
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("aVeryBigSum JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path path = std::filesystem::path(__FILE__).parent_path() /
                               "a_very_big_sum.testcases.json";

  INFO("aVeryBigSum JSON test cases FILE: " << path.string());

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    auto size = static_cast<int>(testcase["input"].size());
    std::vector<long> input_vector = testcase["input"];
    const long *input_array = input_vector.data();

    long long result = HACKERRANK_WARMUP_aVeryBigSum(size, input_array);
    CHECK(result == testcase["expected"]);
  }
}
