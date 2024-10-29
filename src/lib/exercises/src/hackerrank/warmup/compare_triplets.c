#include <stdlib.h>

#include <exercises/basic/common.h>
#include <exercises/hackerrank/warmup/compare_triplets.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/compare_triplets.md]]
 */

int *HACKERRANK_WARMUP_compareTriplets(int a_count, const int *a, int b_count,
                                       const int *b, int *result_count) {

  *result_count = 2;
  int *awards = malloc(sizeof(int) * *result_count);

  awards[0] = 0;
  awards[1] = 0;

  for (int i = 0; i < MIN(a_count, b_count); i++) {
    if (a[i] > b[i]) {
      awards[0] = awards[0] + 1;
    }
    if (a[i] < b[i]) {
      awards[1] = awards[1] + 1;
    }
  }

  return awards;
}
