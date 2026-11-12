#include <catch2/catch_test_macros.hpp>

#include <exercises/hackerrank/projecteuler/euler003.h>
#include <iostream>
#include <vector>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST_CASE("euler003 JSON Test Cases",
          "[hackerrank] [jsontestcase] [projecteuler]") {
  std::filesystem::path path =
      std::filesystem::path(__FILE__).parent_path() / "euler003.testcases.json";

  INFO("euler003 JSON test cases FILE: " << path.string());

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    long result = HACKERRANK_PROJECTEULER_euler003(testcase["n"]);
    CHECK(result == testcase["expected"]);
  }
}
