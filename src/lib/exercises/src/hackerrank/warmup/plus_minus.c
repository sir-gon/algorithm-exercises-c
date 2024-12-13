#include <exercises/hackerrank/warmup/plus_minus.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/plus_minus.md]]
 */

#include <stdio.h>  // malloc
#include <stdlib.h> // snprintf

const int BUFFER_MAX_SIZE = 10;

char *format_result(double number) {
  char *buffer = malloc(BUFFER_MAX_SIZE * sizeof(char));

  snprintf(buffer, BUFFER_MAX_SIZE, "%0.6lf", number);
  return buffer;
}

char **HACKERRANK_WARMUP_plusMinusCalculate(int arr_count, const int *arr) {
  int positives = 0;
  int negatives = 0;
  int zeros = 0;

  int i = 0;

  while (i < arr_count) {
    int value = arr[i];

    if (value > 0) {
      positives += 1;
    }
    if (value < 0) {
      negatives += 1;
    }
    if (value == 0) {
      zeros += 1;
    }

    i += 1;
  }

  double const results[3] = {(double)positives / arr_count,
                             (double)negatives / arr_count,
                             (double)zeros / arr_count};

  int n = 3; // Número de strings (puede ser arbitrario)
  char **answer = malloc(n * sizeof(char *)); // Array de punteros

  for (i = 0; i < n; i++) {
    char *formatted = format_result(results[i]);
    answer[i] = formatted;
  }

  return answer;
}

void HACKERRANK_WARMUP_freePlusMinus(char **plusMinusAnswer, int n) {
  for (int i = 0; i < n; i++) {
    free(plusMinusAnswer[i]);
  }
  free(plusMinusAnswer);
}

void HACKERRANK_WARMUP_plusMinus(int arr_count, const int *arr) {
  char **output = HACKERRANK_WARMUP_plusMinusCalculate(arr_count, arr);

  for (int i = 0; i < HACKERRANK_WARMUP_PLUSMINUS_LIMIT_ANSWERS; i++) {
    printf("%s", output[i]);
  }

  HACKERRANK_WARMUP_freePlusMinus(output,
                                  HACKERRANK_WARMUP_PLUSMINUS_LIMIT_ANSWERS);
}
