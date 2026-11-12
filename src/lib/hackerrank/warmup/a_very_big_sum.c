#include <exercises/hackerrank/warmup/a_very_big_sum.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/a_very_big_sum.md]]
 */

long long HACKERRANK_WARMUP_aVeryBigSum(int ar_count, const long *ar) {
  long long total = 0;

  for (int i = 0; i < ar_count; i++) {
    total += ar[i];
  }

  return total;
}
