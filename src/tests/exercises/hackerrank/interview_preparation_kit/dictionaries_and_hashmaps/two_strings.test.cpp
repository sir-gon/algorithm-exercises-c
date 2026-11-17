// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#include <exercises/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/two_strings.h>

// std libs
#include <fstream> // f()
#include <vector>

using json = nlohmann::json;

TEST_CASE("Two Strings JSON Test Cases",
          "[hackerrank] [jsontestcase] [dictionaries_and_hashmaps]") {
  std::filesystem::path path = std::filesystem::path(__FILE__).parent_path() /
                               "two_strings.testcases.json";

  INFO("Two Strings JSON test cases FILE: " << path.string());

  for (auto testcase : json::parse(std::ifstream(path))) {
    INFO("Two Strings JSON test case: " << testcase["title"]);

    std::string expected = testcase["expected"].get<std::string>();
    std::string s1 = testcase["s1"].get<std::string>();
    std::string s2 = testcase["s2"].get<std::string>();

    std::string result = twoStrings(s1.data(), s2.data());

    CHECK(result == expected);
  }
}
