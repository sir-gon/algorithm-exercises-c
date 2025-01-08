#include <exercises/hackerrank/warmup/mini_max_sum.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/mini_max_sum.md]]
 */

#include <exercises/basic/common.h>
#include <stdio.h>  // malloc
#include <stdlib.h> // snprintf

char *HACKERRANK_WARMUP_miniMaxSumCalculate(int arr_count, const int *arr) {
  if (arr_count < 2) {
    char *result = NULL;
    return result;
  }

  long long tsum = 0;
  long long tmin = arr[0];
  long long tmax = arr[1];

  for (int i = 0; i < arr_count; i++) {
    long long cvalue = (long long)arr[i];
    tsum += cvalue;
    tmin = MIN(tmin, cvalue);
    tmax = MAX(tmax, cvalue);
  }

  const int BUFFER_MAX_SIZE = 100;
  char *buffer = malloc(BUFFER_MAX_SIZE * sizeof(char));

  snprintf(buffer, BUFFER_MAX_SIZE, "%lld %lld", tsum - tmax, tsum - tmin);
  return buffer;
}

void HACKERRANK_WARMUP_miniMaxSum(int arr_count, const int *arr) {
  char *result = HACKERRANK_WARMUP_miniMaxSumCalculate(arr_count, arr);
  printf("%s\n", result);
  free(result);
}
