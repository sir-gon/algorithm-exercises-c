// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#ifdef __linux__
#include "../../../../../tools/memory_injector.hpp"
#endif
#include <exercises/hackerrank/interview_preparation_kit/arrays/ctci_array_left_rotation.h>

// std libs
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("rotLeft JSON Test Cases", "[jsontestcase] [hackerrank] [arrays]") {
  SECTION("rotLeft: Normal workflow") {
    std::filesystem::path path = std::filesystem::path(__FILE__).parent_path() /
                                 "ctci_array_left_rotation.testcases.json";

    INFO("rotLeft JSON test cases FILE: " << path.string());

    std::ifstream f(path);
    json data = json::parse(f);

    int result_size = 0;

    for (const auto &testcase : data) {
      const auto testcase_size = static_cast<int>(testcase["input"].size());
      const std::vector<int> a_input_vector = testcase["input"];
      const int *a_input_array = a_input_vector.data();

      const int *result =
          rotLeft(testcase_size, const_cast<int *>(a_input_array),
                  testcase["d_rotations"].get<int>(), &result_size);

      const std::vector<int> result_vector(result, result + testcase_size);
      CHECK(result_vector == testcase["expected"].get<std::vector<int>>());
    }
  }

  SECTION("rotLeft: Empty array") {
    int testcase_size = 5;
    int *a_input_array = nullptr;
    int d_rotations = 1;
    int result_size = 0;

    const int *result = rotLeft(testcase_size, const_cast<int *>(a_input_array),
                                d_rotations, &result_size);

    CHECK(result == nullptr);
  }

  SECTION("rotLeft: Empty size") {
    int testcase_size = 0;
    int a_input_array[1] = {1};
    int d_rotations = 1;
    int result_size = 0;

    const int *result = rotLeft(testcase_size, const_cast<int *>(a_input_array),
                                d_rotations, &result_size);

    CHECK(result == nullptr);
  }

  SECTION("rotLeft: Result size null") {
    int testcase_size = 1;
    int a_input_array[1] = {1};
    int d_rotations = 1;
    int *result_size = nullptr;

    const int *result = rotLeft(testcase_size, const_cast<int *>(a_input_array),
                                d_rotations, result_size);

    CHECK(result == nullptr);
  }
}
