#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/warmup/birthday_cake_candles.h>
#include <iostream>
#include <vector>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST_CASE("birthdayCakeCandles JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path =
      cwd.string() +
      "/unit/lib/hackerrank/warmup/birthday_cake_candles.testcases.json";

  INFO("birthdayCakeCandles JSON test cases FILE: " << path);

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    auto input_size = static_cast<int>(testcase["input"].size());
    std::vector<int> input_vector = testcase["input"];
    const int *input_array = input_vector.data();

    long result =
        HACKERRANK_WARMUP_birthdayCakeCandles(input_size, input_array);
    CHECK(result == testcase["expected"]);
  }
}
