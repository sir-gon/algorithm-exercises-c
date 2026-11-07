// 3rd party libs
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

// local libs
#include "tools/memory_injector.hpp"
#include <exercises/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/ctci_ransom_note.h>

// std libs
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

using json = nlohmann::json;

void transform_magazine_note_input(std::vector<std::string> &magazine,
                                   std::vector<std::string> &note,
                                   std::vector<char *> &magazine_ptr,
                                   std::vector<char *> &note_ptr) {
  magazine_ptr.resize(magazine.size());
  std::transform(
      magazine.begin(), magazine.end(), magazine_ptr.begin(),
      [](const std::string &word) { return const_cast<char *>(word.c_str()); });

  note_ptr.resize(note.size());
  std::transform(
      note.begin(), note.end(), note_ptr.begin(),
      [](const std::string &word) { return const_cast<char *>(word.c_str()); });
}

TEST_CASE("checkMagazine JSON Test Cases",
          "[hackerrank] [jsontestcase] [dictionaries_and_hashmaps]") {
  std::filesystem::path path = std::filesystem::path(__FILE__).parent_path() /
                               "ctci-ransom-note.testcases.json";

  INFO("checkMagazine JSON test cases FILE: " << path.string());

  std::ifstream f(path);
  json data = json::parse(f);

  for (auto testcase : data) {
    INFO("checkMagazine JSON test case: " << testcase["title"]);

    std::string expected = testcase["expected"].get<std::string>();
    std::vector<std::string> magazine =
        testcase["magazine"].get<std::vector<std::string>>();
    std::vector<std::string> note =
        testcase["note"].get<std::vector<std::string>>();
    std::vector<char *> magazine_ptr;
    std::vector<char *> note_ptr;

    transform_magazine_note_input(magazine, note, magazine_ptr, note_ptr);

    std::string result = checkMagazineText(
        static_cast<int>(magazine_ptr.size()), magazine_ptr.data(),
        static_cast<int>(note_ptr.size()), note_ptr.data());

    // print result to get high coverage
    checkMagazine(static_cast<int>(magazine_ptr.size()), magazine_ptr.data(),
                  static_cast<int>(note_ptr.size()), note_ptr.data());

    CHECK(result == expected);
  }
}

TEST_CASE("checkMagazine unhappy path cases",
          "[hackerrank] [dictionaries_and_hashmaps] [unhappy]") {
  SECTION("arrayManipulation: magazine has null word") {
    std::vector<std::string> magazine = {"hello", "world"};
    std::vector<std::string> note = {"hello", "world"};
    std::vector<char *> magazine_ptr;
    std::vector<char *> note_ptr;

    transform_magazine_note_input(magazine, note, magazine_ptr, note_ptr);
    magazine_ptr.push_back(
        nullptr); // add a null pointer to simulate a failure case

    std::string result = checkMagazineText(
        static_cast<int>(magazine_ptr.size()), magazine_ptr.data(),
        static_cast<int>(note_ptr.size()), note_ptr.data());

    CHECK(result == __RANSOM_NOTE_YES__);
  }

  SECTION("arrayManipulation: magazine has empty word") {
    std::vector<std::string> magazine = {"hello", "world", ""};
    std::vector<std::string> note = {"hello", "world"};
    std::vector<char *> magazine_ptr;
    std::vector<char *> note_ptr;

    transform_magazine_note_input(magazine, note, magazine_ptr, note_ptr);

    std::string result = checkMagazineText(
        static_cast<int>(magazine_ptr.size()), magazine_ptr.data(),
        static_cast<int>(note_ptr.size()), note_ptr.data());

    CHECK(result == __RANSOM_NOTE_YES__);
  }

  SECTION(
      "arrayManipulation: note contains a word not present in the magazine") {
    std::vector<std::string> magazine = {"hello", "world"};
    std::vector<std::string> note = {"hello", "missing"};
    std::vector<char *> magazine_ptr;
    std::vector<char *> note_ptr;

    transform_magazine_note_input(magazine, note, magazine_ptr, note_ptr);

    std::string result = checkMagazineText(
        static_cast<int>(magazine_ptr.size()), magazine_ptr.data(),
        static_cast<int>(note_ptr.size()), note_ptr.data());

    CHECK(result == __RANSOM_NOTE_NO__);
  }

  SECTION("arrayManipulation: note has many repeated words") {
    std::vector<std::string> magazine = {"hello", "world"};
    std::vector<std::string> note = {"hello", "world", "world", "world"};
    std::vector<char *> magazine_ptr;
    std::vector<char *> note_ptr;

    transform_magazine_note_input(magazine, note, magazine_ptr, note_ptr);

    std::string result = checkMagazineText(
        static_cast<int>(magazine_ptr.size()), magazine_ptr.data(),
        static_cast<int>(note_ptr.size()), note_ptr.data());

    CHECK(result == __RANSOM_NOTE_NO__);
  }

#if defined(__linux__)
  SECTION("arrayManipulation: Failure handling during Out of Memory (OOM)") {
    MemoryInjector::enable_oom_fault();

    std::vector<std::string> magazine = {"hello", "world"};
    std::vector<std::string> note = {"out", "of", "world"};
    std::vector<char *> magazine_ptr;
    std::vector<char *> note_ptr;

    transform_magazine_note_input(magazine, note, magazine_ptr, note_ptr);

    std::string result = checkMagazineText(
        static_cast<int>(magazine_ptr.size()), magazine_ptr.data(),
        static_cast<int>(note_ptr.size()), note_ptr.data());

    CHECK(result == __RANSOM_NOTE_NO__);

    // Clean up the state after finishing the test section
    MemoryInjector::disable_fault();
  }
#endif
}
