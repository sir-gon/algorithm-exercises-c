#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/warmup/mini_max_sum.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include <stdio.h> // malloc

using json = nlohmann::json;

TEST_CASE("miniMaxSum JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path =
      cwd.string() + "/unit/lib/hackerrank/warmup/mini_max_sum.testcases.json";

  INFO("miniMaxSum JSON test cases FILE: " << path);

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    auto input_size = static_cast<int>(testcase["input"].size());
    std::vector<int> input_vector = testcase["input"];
    const int *input_array = input_vector.data();

    char *result =
        HACKERRANK_WARMUP_miniMaxSumCalculate(input_size, input_array);
    HACKERRANK_WARMUP_miniMaxSum(input_size, input_array);

    std::string result_as_string(result);

    free(result);

    CHECK(result_as_string == testcase["expected"]);
  }
}

TEST_CASE("miniMaxSum Edge Cases", "[hackerrank] [warmup]") {
  std::vector<int> empty({});

  const char *result = HACKERRANK_WARMUP_miniMaxSumCalculate(0, empty.data());

  CHECK(result == nullptr);
}
