#include <exercises/hackerrank/projecteuler/euler002.h>

/**
 * @link Problem definition [[docs/hackerrank/projecteuler/euler002.md]]
 */

int HACKERRANK_PROJECTEULER_fibo_even_sum(int n) {
  int fibo1 = 1;
  int fibo2 = 1;
  int total = 0;

  while (fibo1 + fibo2 < n) {
    int fibo = fibo1 + fibo2;
    fibo1 = fibo2;
    fibo2 = fibo;

    if (fibo % 2 == 0) {
      total += fibo;
    }
  }

  return total;
}

int HACKERRANK_PROJECTEULER_euler002(int n) {
  return HACKERRANK_PROJECTEULER_fibo_even_sum(n);
}
