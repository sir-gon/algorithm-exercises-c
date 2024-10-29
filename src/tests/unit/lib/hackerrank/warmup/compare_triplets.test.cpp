#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/warmup/compare_triplets.h>
#include <iostream>
#include <vector>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST_CASE("compareTriplets JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path =
      cwd.string() +
      "/unit/lib/hackerrank/warmup/compare_triplets.testcases.json";

  INFO("compareTriplets JSON test cases FILE: " << path);

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    auto a_size = static_cast<int>(testcase["a"].size());
    std::vector<int> a_input_vector = testcase["a"];
    const int *a_input_array = a_input_vector.data();

    auto b_size = static_cast<int>(testcase["b"].size());
    std::vector<int> b_input_vector = testcase["b"];
    const int *b_input_array = b_input_vector.data();
    int result_count;

    int *result = HACKERRANK_WARMUP_compareTriplets(
        a_size, a_input_array, b_size, b_input_array, &result_count);

    // Crear un vector a partir del array en C
    std::vector<int> result_as_vector(result, result + result_count);

    CHECK(result_as_vector == testcase["expected"]);
  }
}
