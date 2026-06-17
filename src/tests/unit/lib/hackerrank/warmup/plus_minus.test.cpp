// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#ifdef __linux__
#include "../../../../tools/memory_injector.hpp"
#endif
#include <exercises/hackerrank/warmup/plus_minus.h>

// std libs
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("plusMinus JSON Test Cases", "[hackerrank] [jsontestcase] [warmup]") {
#ifdef __linux__
  SECTION("Failure handling during Out of Memory (OOM)") {
    // MemoryInjector::enable_oom_fault();

    int input_size = 3;
    int input_array[] = {1, -2, 0};

    MemoryInjector::fail_on_allocation_number(1);
    REQUIRE(HACKERRANK_WARMUP_plusMinusCalculate(input_size, input_array) ==
            nullptr);

    MemoryInjector::fail_on_allocation_number(2);
    REQUIRE(HACKERRANK_WARMUP_plusMinusCalculate(input_size, input_array) ==
            nullptr);

    MemoryInjector::fail_on_allocation_number(3);
    REQUIRE(HACKERRANK_WARMUP_plusMinusCalculate(input_size, input_array) ==
            nullptr);

    MemoryInjector::disable_fault();
    MemoryInjector::enable_oom_fault();
    REQUIRE_NOTHROW(HACKERRANK_WARMUP_plusMinus(input_size, input_array));

    // Clean up the state after finishing the test section
    MemoryInjector::disable_fault();
  }
#endif

  SECTION("Normal memory allocation succeeds") {
    // Reset the injector state before every section running
    // MemoryInjector::disable_fault();

    std::filesystem::path cwd = std::filesystem::current_path();
    std::string path =
        cwd.string() + "/unit/lib/hackerrank/warmup/plus_minus.testcases.json";

    INFO("plusMinus JSON test cases FILE: " << path);

    std::ifstream f(path);
    json data = json::parse(f);

    for (auto testcase : data) {
      auto input_size = static_cast<int>(testcase["input"].size());
      std::vector<int> input_vector = testcase["input"];
      const int *input_array = input_vector.data();

      char **result =
          HACKERRANK_WARMUP_plusMinusCalculate(input_size, input_array);

      std::vector<std::string> result_as_vector;

      for (int i = 0; i < HACKERRANK_WARMUP_PLUSMINUS_LIMIT_ANSWERS; i++) {
        result_as_vector.emplace_back(result[i]);
      }
      HACKERRANK_WARMUP_freePlusMinus(
          result, HACKERRANK_WARMUP_PLUSMINUS_LIMIT_ANSWERS);

      CHECK(result_as_vector == testcase["expected"]);

      // Just call void function, to collect coverage
      HACKERRANK_WARMUP_plusMinus(input_size, input_array);
    }
  }
}
