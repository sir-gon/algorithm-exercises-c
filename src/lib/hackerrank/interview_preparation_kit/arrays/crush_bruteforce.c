#include <exercises/hackerrank/interview_preparation_kit/arrays/crush.h>
#include <stdlib.h>
#include <tools/memory_allocator.h>

/**
 * @link Problem definition
 * [[docs/hackerrank/interview_preparation_kit/arrays/crush.md]]
 */

static inline long exercise_max_long(long a, long b) { return a > b ? a : b; }

long arrayManipulation(int n, int queries_rows, int queries_columns,
                       int **queries) {
  // why adding 2?
  //   first slot to adjust 1-based index and
  //   last slot for storing accum_sum result
  int *result = memory_allocator_malloc((size_t)(n + 1) * sizeof(int));
  if (result == NULL) {
    return 0L;
  }

  long maximum = 0;

  for (int i = 0; i <= n; i++) {
    result[i] = 0;
  }

  for (int j = 0; j < queries_rows; j++) {
    int a = queries[j][0];
    int b = queries[j][1];
    int k = queries[j][2];

    for (int l = a; l <= b; l++) {
      result[l] += k;
    }
  }

  for (int i = 1; i < n + 1; i++) {
    int value = result[i];
    maximum = exercise_max_long(maximum, value);
  }

  free(result);
  return maximum;
}
