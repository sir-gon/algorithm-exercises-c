#include <exercises/hackerrank/warmup/time_conversion.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/time_conversion.md]]
 */

#include <stdio.h>  // snprintf
#include <stdlib.h> // malloc, free, strtol
#include <string.h> // strcmp, strnlen

#define HACKERRANK_WARMUP_LONG_TIME_FORMAT_SIZE 10
#define HACKERRANK_WARMUP_SHORT_TIME_FORMAT_SIZE 8
#define HACKERRANK_WARMUP_HOUR_FORMAT_SIZE 2

char *HACKERRANK_WARMUP_timeConversion(const char *s) {
  if (s == NULL) {
    return NULL;
  }

  size_t s_len = strnlen(s, HACKERRANK_WARMUP_LONG_TIME_FORMAT_SIZE);

  if (s_len != HACKERRANK_WARMUP_LONG_TIME_FORMAT_SIZE) {
    return NULL;
  }

  char hour_str[HACKERRANK_WARMUP_HOUR_FORMAT_SIZE + 1];

  hour_str[0] = s[0];
  hour_str[1] = s[1];
  hour_str[2] = '\0';

  char meridian[3];
  meridian[0] = s[s_len - 2];
  meridian[1] = s[s_len - 1];
  meridian[2] = '\0';

  char *endptr;
  long hour = strtol(hour_str, &endptr, 10);

  if (*endptr != '\0') {
    printf("Conversion error, non-convertible part: %s\n", endptr);

    return NULL;
  } else {
    printf("The integer value is: %ld\n", hour);
  }

  hour = hour % 12;

  if (strcmp(meridian, "PM") == 0) {
    hour += 12;
  }

  char *conversion =
      malloc((HACKERRANK_WARMUP_SHORT_TIME_FORMAT_SIZE + 1) * sizeof(char));

  for (int i = 0; i < HACKERRANK_WARMUP_SHORT_TIME_FORMAT_SIZE; i++) {
    conversion[i] = s[i];
  }
  conversion[HACKERRANK_WARMUP_SHORT_TIME_FORMAT_SIZE] = '\0';

  snprintf(hour_str, HACKERRANK_WARMUP_HOUR_FORMAT_SIZE + 1, "%02ld", hour);

  conversion[0] = hour_str[0];
  conversion[1] = hour_str[1];

  return conversion;
}
