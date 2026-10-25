// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#if defined(__linux__)
#include "../../../../../tools/memory_injector.hpp"
#endif
#include <exercises/hackerrank/interview_preparation_kit/arrays/minimum_swaps_2.h>

// std libs
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("minimumSwaps JSON Test Cases",
          "[hackerrank] [jsontestcase] [arrays]") {
  std::filesystem::path path = std::filesystem::path(__FILE__).parent_path() /
                               "minimum_swaps_2.testcases.json";

  INFO("minimumSwaps JSON test cases FILE: " << path.string());

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    INFO("minimumSwaps JSON test case: " << testcase["title"]);
    auto quantity = static_cast<size_t>(testcase["input"].size());
    std::vector<int> input_vector = testcase["input"].get<std::vector<int>>();
    int *input_array = input_vector.data();

    int result = minimumSwaps(quantity, input_array);

    CHECK(result == testcase["expected"].get<int>());
  }

#if defined(__linux__)
  SECTION("minimumSwaps: Failure handling during Out of Memory (OOM)") {
    MemoryInjector::enable_oom_fault();

    int testcase_size = 4;
    int a_input_array[4] = {1, 2, 3, 4};

    auto result = minimumSwaps(testcase_size, const_cast<int *>(a_input_array));
    REQUIRE(result == -1);

    // Clean up the state after finishing the test section
    MemoryInjector::disable_fault();
  }
#endif
}
