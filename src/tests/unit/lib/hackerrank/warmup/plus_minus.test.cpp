#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/warmup/plus_minus.h>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST_CASE("plusMinus JSON Test Cases", "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path =
      cwd.string() + "/unit/lib/hackerrank/warmup/plus_minus.testcases.json";

  INFO("plusMinus JSON test cases FILE: " << path);

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    auto input_size = static_cast<int>(testcase["input"].size());
    std::vector<int> input_vector = testcase["input"];
    int *input_array = input_vector.data();

    HACKERRANK_WARMUP_plusMinus(input_size, input_array);

    char **result =
        HACKERRANK_WARMUP_plusMinusCalculate(input_size, input_array);

    std::vector<std::string> result_as_vector(result, result + input_size);

    CHECK(result_as_vector == testcase["expected"]);
  }
}
