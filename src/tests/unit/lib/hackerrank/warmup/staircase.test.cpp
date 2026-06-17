// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#if defined(__linux__)
#include "../../../../tools/memory_injector.hpp"
#endif
#include <exercises/hackerrank/warmup/staircase.h>

// std libs
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("staircase JSON Test Cases", "[hackerrank] [jsontestcase] [warmup]") {
#if defined(__linux__)
  SECTION("staircase: Failure handling during Out of Memory (OOM)") {
    int input = 4;

    MemoryInjector::enable_oom_fault();
    REQUIRE(HACKERRANK_WARMUP_staircaseCalculate(input) == nullptr);
    MemoryInjector::disable_fault();

    MemoryInjector::fail_on_allocation_number(2);
    REQUIRE(HACKERRANK_WARMUP_staircaseCalculate(input) == nullptr);
    MemoryInjector::disable_fault();

    MemoryInjector::enable_oom_fault();
    REQUIRE_NOTHROW(HACKERRANK_WARMUP_staircase(input));
    MemoryInjector::disable_fault();
  }
#endif

  SECTION("plusMinus: Normal memory allocation succeeds") {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string path =
        cwd.string() + "/unit/lib/hackerrank/warmup/staircase.testcases.json";

    INFO("staircase JSON test cases FILE: " << path);

    std::ifstream f(path);
    json data = json::parse(f);

    for (auto testcase : data) {
      auto input = static_cast<int>(testcase["input"]);

      char **result = HACKERRANK_WARMUP_staircaseCalculate(input);

      std::vector<std::string> result_as_vector;

      for (int i = 0; i < input; i++) {
        result_as_vector.emplace_back(result[i]);
      }

      HACKERRANK_WARMUP_freeStaircase(result, input);

      CHECK(result_as_vector == testcase["expected"]);

      // Just call void function, to collect coverage
      HACKERRANK_WARMUP_staircase(input);
    }
  }
}
