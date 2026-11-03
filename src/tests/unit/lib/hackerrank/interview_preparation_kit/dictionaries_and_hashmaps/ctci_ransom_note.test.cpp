// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#include <exercises/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/ctci_ransom_note.h>

// std libs
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

TEST_CASE("checkMagazine JSON Test Cases",
          "[hackerrank] [jsontestcase] [dictionaries_and_hashmaps]") {
  std::filesystem::path path = std::filesystem::path(__FILE__).parent_path() /
                               "ctci-ransom-note.testcases.json";

  INFO("checkMagazine JSON test cases FILE: " << path.string());

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    INFO("checkMagazine JSON test case: " << testcase["title"]);

    std::vector<std::string> magazine =
        testcase["magazine"].get<std::vector<std::string>>();
    std::vector<std::string> note =
        testcase["note"].get<std::vector<std::string>>();
    std::string expected = testcase["expected"].get<std::string>();

    std::vector<char *> magazine_ptr(magazine.size());
    std::transform(magazine.begin(), magazine.end(), magazine_ptr.begin(),
                   [](const std::string &word) {
                     return const_cast<char *>(word.c_str());
                   });

    std::vector<char *> note_ptr(note.size());
    std::transform(note.begin(), note.end(), note_ptr.begin(),
                   [](const std::string &word) {
                     return const_cast<char *>(word.c_str());
                   });

    std::string result = checkMagazineText(
        static_cast<int>(magazine_ptr.size()), magazine_ptr.data(),
        static_cast<int>(note_ptr.size()), note_ptr.data());

    CHECK(result == expected);
  }
}
