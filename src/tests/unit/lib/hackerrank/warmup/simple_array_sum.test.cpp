#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/warmup/simple_array_sum.h>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

TEST_CASE("simpleArraySum JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path =
      cwd.string() +
      "/unit/lib/hackerrank/warmup/simple_array_sum.testcases.json";

  INFO("simpleArraySum JSON test cases FILE: " << path);

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    auto size = static_cast<int>(testcase["input"].size());
    std::vector<int> input_vector = testcase["input"];
    const int *input_array = input_vector.data();

    int result = HACKERRANK_WARMUP_simpleArraySum(size, input_array);
    CHECK(result == testcase["expected"]);
  }
}
