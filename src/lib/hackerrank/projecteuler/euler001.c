#include <exercises/hackerrank/projecteuler/euler001.h>

/**
 * @link Problem definition [[docs/hackerrank/projecteuler/euler001.md]]
 */

unsigned long HACKERRANK_PROJECTEULER_min(unsigned long a, unsigned long b) {
  if (a > b) {
    return b;
  }

  return a;
}

// Function to return gcd of a and b
unsigned long HACKERRANK_PROJECTEULER_gcd(unsigned long a, unsigned long b) {
  // Find Minimum of a and b
  unsigned long result = HACKERRANK_PROJECTEULER_min(a, b);
  while (result > 0) {
    if (a % result == 0 && b % result == 0) {
      break;
    }
    result--;
  }

  // Return gcd of a and b
  return result;
}

// Function to find sum of Arithmetic Progression series
unsigned long
HACKERRANK_PROJECTEULER_sum_of_arithmetic_progression(unsigned long n,
                                                      unsigned long d) {
  // Number of terms
  n = n / d;
  return n * (1 + n) * d / 2;
}

// Function to find the sum of all multiples of a and b below n
unsigned long HACKERRANK_PROJECTEULER_euler001(int a, int b, int n) {
  // Since, we need the sum of multiples less than N
  n = n - 1;

  unsigned long gcd = HACKERRANK_PROJECTEULER_gcd(a, b);
  if (gcd == 0) {
    return 0;
  }

  unsigned long lcm = (a * b) / gcd;

  return HACKERRANK_PROJECTEULER_sum_of_arithmetic_progression(n, a) +
         HACKERRANK_PROJECTEULER_sum_of_arithmetic_progression(n, b) -
         HACKERRANK_PROJECTEULER_sum_of_arithmetic_progression(n, lcm);
}
