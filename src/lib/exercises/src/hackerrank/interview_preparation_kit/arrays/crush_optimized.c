#include <exercises/hackerrank/interview_preparation_kit/arrays/crush.h>
#include <stdlib.h>

/**
 * @link Problem definition
 * [[docs/hackerrank/interview_preparation_kit/arrays/crush.md]]
 */

static inline long exercise_max_long(long a, long b) { return a > b ? a : b; }

static inline long exercise_min_long(long a, long b) { return a < b ? a : b; }

long arrayManipulationOptimized(int n, int queries_rows, int queries_columns,
                                int **queries) {
  // why adding 2?
  //   first slot to adjust 1-based index and
  //   last slot for storing accum_sum result
  int *result = malloc((size_t)(n + 2) * sizeof(int));
  if (result == NULL) {
    return 0L;
  }

  long maximum = 0;

  for (int i = 0; i < n + 2; i++) {
    result[i] = 0;
  }

  for (int j = 0; j < queries_rows; j++) {
    int a_start = queries[j][0];
    int b_end = queries[j][1];
    int k_value = queries[j][2];

    result[a_start] += k_value;
    result[b_end + 1] -= k_value;
  }

  long accum_sum = 0L;
  for (int i = 1; i < n + 2; i++) {
    accum_sum += result[i];
    maximum = exercise_max_long(maximum, accum_sum);
  }

  free(result);
  return maximum;
}
