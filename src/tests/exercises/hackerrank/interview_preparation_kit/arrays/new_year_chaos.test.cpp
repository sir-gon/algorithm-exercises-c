// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#include "tools/json_to_string.hpp"
#include <exercises/hackerrank/interview_preparation_kit/arrays/new_year_chaos.h>

// std libs
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("minimumBribes JSON Test Cases",
          "[hackerrank] [jsontestcase] [arrays]") {
  std::filesystem::path path = std::filesystem::path(__FILE__).parent_path() /
                               "new_year_chaos.testcases.json";

  INFO("minimumBribes JSON test cases FILE: " << path.string());

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    INFO("minimumBribes JSON test case: " << testcase["title"]);
    auto quantity = static_cast<size_t>(testcase["input"].size());
    std::vector<int> input_vector = testcase["input"];
    int *input_array = input_vector.data();

    std::string result = minimumBribesText(quantity, input_array);
    std::string expected = json_to_string(testcase["expected"]);
    minimumBribes(quantity, input_array); // call print function

    CHECK(result == expected);
  }
}
