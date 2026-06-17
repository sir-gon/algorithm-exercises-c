// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#ifdef __linux__
#include "../../../../tools/memory_injector.hpp"
#endif
#include <exercises/hackerrank/warmup/time_conversion.h>

// std libs
#include <filesystem>
#include <fstream>

using json = nlohmann::json;

TEST_CASE("time_conversion JSON Test Cases",
          "[hackerrank] [jsontestcase] [warmup]") {
#ifdef __linux__
  SECTION("time_conversion Failure handling during Out of Memory (OOM)") {
    MemoryInjector::enable_oom_fault();

    const char *input = "12:01:00PM";

    REQUIRE(HACKERRANK_WARMUP_timeConversion(input) == nullptr);

    // Clean up the state after finishing the test section
    MemoryInjector::disable_fault();
  }
#endif

  SECTION("Normal memory allocation succeeds") {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string path =
        cwd.string() +
        "/unit/lib/hackerrank/warmup/time_conversion.testcases.json";

    INFO("time_conversion JSON test cases FILE: " << path);

    std::ifstream f(path);
    json data = json::parse(f);

    for (auto testcase : data) {
      char *result = HACKERRANK_WARMUP_timeConversion(
          testcase["input"].get<std::string>().c_str());

      std::string result_as_string(result);

      free(result);

      CHECK(result_as_string == testcase["expected"]);
    }
  }

  SECTION("time_conversion edge cases", "[hackerrank] [helper] [warmup]") {
    CHECK(HACKERRANK_WARMUP_timeConversion(nullptr) == nullptr);

    CHECK(HACKERRANK_WARMUP_timeConversion("") == nullptr);

    CHECK(HACKERRANK_WARMUP_timeConversion("aa:bb:ccXM") == nullptr);
  }
}
