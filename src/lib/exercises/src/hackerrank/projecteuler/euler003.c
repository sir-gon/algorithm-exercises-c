#include <exercises/hackerrank/projecteuler/euler003.h>

/**
 * @link Problem definition [[docs/hackerrank/projecteuler/euler003.md]]
 */

#include <math.h>
#include <stdbool.h>

long HACKERRANK_PROJECTEULER_prime_factor(long n) {
  long divisor = n;
  long max_prime_factor;
  bool mpf_initialized = false;

  long i = 2;

  while ((double)i <= sqrt((double)divisor)) {
    if (0 == divisor % i) {
      divisor = divisor / i;
      max_prime_factor = divisor;
      mpf_initialized = true;
    } else {
      i += 1;
    }
  }

  if (!mpf_initialized) {
    return n;
  }

  return max_prime_factor;
}

long HACKERRANK_PROJECTEULER_euler003(long n) {
  return HACKERRANK_PROJECTEULER_prime_factor(n);
}
