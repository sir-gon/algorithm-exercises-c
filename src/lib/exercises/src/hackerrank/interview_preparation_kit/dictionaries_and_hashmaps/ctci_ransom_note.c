#include <exercises/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/ctci_ransom_note.h>
#include <stdbool.h> // bool
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // printf

const char *__RANSOM_NOTE_YES__ = "Yes";
const char *__RANSOM_NOTE_NO__ = "No";

/**
 * @link Problem definition
 * [[docs/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/ctci-ransom-note.md]]
 */

typedef struct WordCount {
  char word[256];
  int count;
  struct WordCount *next;
} WordCount;

static int hash_function(const char *word) {
  if (word == NULL) {
    return 0;
  }
  if (word[0] == '\0') {
    return 0;
  }
  return (int)word[0];
}

bool checkMagazineCompute(int magazine_count, char **magazine, int note_count,
                          char **note) {

  // build dictionary from magazine
  WordCount *buckets[256] = {NULL};

  for (int i = 0; i < magazine_count; i++) {
    const char *word = magazine[i];
    int hash = hash_function(word);
    WordCount *current = buckets[hash];

    while (current != NULL) {
      if (strcmp(current->word, word) == 0) {
        current->count++;
        break;
      }
      current = current->next;
    }

    if (current == NULL) {
      WordCount *new_word_count = malloc(sizeof(WordCount));
      if (new_word_count == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
      }
      snprintf(new_word_count->word, sizeof(new_word_count->word), "%s", word);
      new_word_count->count = 1;
      new_word_count->next = buckets[hash];
      buckets[hash] = new_word_count;
    }
  }

  // Search words in the note and check if they exist in the magazine dictionary
  for (int i = 0; i < note_count; i++) {
    const char *word = note[i];
    int hash = hash_function(word);
    WordCount *current = buckets[hash];

    while (current != NULL) {
      if (strcmp(current->word, word) == 0) {
        if (current->count <= 0) {
          return false;
        }
        current->count--;
        break;
      }
      current = current->next;
    }

    if (current == NULL) {
      return false;
    }
  }

  return true;
}

const char *checkMagazineText(int magazine_count, char **magazine,
                              int note_count, char **note) {
  if (!checkMagazineCompute(magazine_count, magazine, note_count, note)) {
    return __RANSOM_NOTE_NO__;
  } else {
    return __RANSOM_NOTE_YES__;
  }
}

void checkMagazine(int magazine_count, char **magazine, int note_count,
                   char **note) {
  printf("%s\n", checkMagazineText(magazine_count, magazine, note_count, note));
}
