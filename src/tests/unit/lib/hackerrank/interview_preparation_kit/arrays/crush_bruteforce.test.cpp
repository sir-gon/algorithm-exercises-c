// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#if defined(__linux__)
#include "../../../../../tools/memory_injector.hpp"
#endif
#include <exercises/hackerrank/interview_preparation_kit/arrays/crush.h>

// std libs
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("arrayManipulation JSON Test Cases",
          "[jsontestcase] [hackerrank] [arrays]") {
  SECTION("arrayManipulation: Normal workflow") {
    std::filesystem::path path =
        std::filesystem::path(__FILE__).parent_path() / "crush.testcases.json";

    INFO("arrayManipulation JSON test cases FILE: " << path.string());

    std::ifstream f(path);
    json data = json::parse(f);

    for (const auto &testcase : data) {
      const auto queries_rows = static_cast<int>(testcase["queries"].size());
      const int queries_columns = 3;

      std::vector<std::vector<int>> queries =
          testcase["queries"].get<std::vector<std::vector<int>>>();

      // Construir el int**
      std::vector<int *> queries_ptr(queries.size());

      std::transform(queries.begin(), queries.end(), queries_ptr.begin(),
                     [](auto &row) { return row.data(); });

      const int result = arrayManipulation(testcase["n"], queries_rows,
                                           queries_columns, queries_ptr.data());

      CHECK(result == testcase["expected"]);
    }
  }
}

TEST_CASE("arrayManipulation unhappy path cases",
          "[jsontestcase] [hackerrank] [arrays]") {
#if defined(__linux__)
  SECTION("arrayManipulation: Failure handling during Out of Memory (OOM)") {
    MemoryInjector::enable_oom_fault();

    int testcase_n = 10;
    int **queries_matrix = nullptr;

    auto result = arrayManipulation(testcase_n, 3, 3, queries_matrix);
    REQUIRE(result == 0);

    // Clean up the state after finishing the test section
    MemoryInjector::disable_fault();
  }
#endif
}
