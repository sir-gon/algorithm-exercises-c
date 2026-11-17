#include <stdbool.h>

/**
 * @link Problem definition
 * [[docs/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/two-strings.md]]
 */

const char *__TWO_STRINGS_YES__ = "YES";
const char *__TWO_STRINGS_NO__ = "NO";

char *twoStrings(char *s1, char *s2) {
  bool char_set[26] = {false};

  for (int i = 0; s1[i] != '\0'; i++) {
    char_set[s1[i] - 'a'] = true;
  }

  for (int i = 0; s2[i] != '\0'; i++) {
    if (char_set[s2[i] - 'a']) {
      return __TWO_STRINGS_YES__;
    }
  }

  return __TWO_STRINGS_NO__;
}
