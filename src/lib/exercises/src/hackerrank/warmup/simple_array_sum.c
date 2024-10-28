#include <exercises/hackerrank/warmup/simple_array_sum.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/simple_array_sum.md]]
 */

int HACKERRANK_WARMUP_simpleArraySum(int ar_count, const int *ar) {
  int total = 0;

  for (int i = 0; i < ar_count; i++) {
    total += ar[i];
  }

  return total;
}
