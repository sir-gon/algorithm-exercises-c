// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#include <exercises/hackerrank/projecteuler/euler001.h>

// std libs
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("euler001 JSON Test Cases",
          "[hackerrank] [jsontestcase] [projecteuler]") {
  std::filesystem::path path =
      std::filesystem::path(__FILE__).parent_path() / "euler001.testcases.json";

  INFO("euler001 JSON test cases FILE: " << path.string());

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    int result = HACKERRANK_PROJECTEULER_euler001(testcase["a"], testcase["b"],
                                                  testcase["n"]);
    CHECK(result == testcase["expected"]);
  }
}
