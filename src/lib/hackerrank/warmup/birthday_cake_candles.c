#include <exercises/hackerrank/warmup/a_very_big_sum.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/birthday_cake_candles.md]]
 */

int HACKERRANK_WARMUP_birthdayCakeCandles(int candles_count,
                                          const int *candles) {
  int counter = 0;
  int maximum = candles[0];

  for (int i = 0; i < candles_count; i++) {
    if (candles[i] == maximum) {
      counter += 1;
    }
    if (candles[i] > maximum) {
      maximum = candles[i];
      counter = 1;
    }
  }

  return counter;
}
