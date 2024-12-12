#include <exercises/hackerrank/warmup/staircase.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/staircase.md]]
 */

#include <stdio.h>  // malloc
#include <stdlib.h> // snprintf

char **HACKERRANK_WARMUP_staircaseCalculate(int n) {

  char **answer = malloc(n * sizeof(char *)); // Array of char pointers

  for (int i = 0; i < n; i++) {
    char *line = malloc((n + 1) * sizeof(char)); // Array of char values

    for (int j = 0; j < n; j++) {
      if (j < n - i - 1) {
        line[j] = ' ';
      } else {
        line[j] = '#';
      }
    }
    line[n] = '\0';

    answer[i] = line;
  }

  return answer;
}

void HACKERRANK_WARMUP_staircase(int n) {
  char **output = HACKERRANK_WARMUP_staircaseCalculate(n);

  for (int i = 0; i < n; i++) {
    printf("%s\n", output[i]);
    free(output[i]);
  }

  free(output);
}
