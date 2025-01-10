#include <exercises/hackerrank/warmup/time_conversion.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/time_conversion.md]]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *HACKERRANK_WARMUP_firstN(const char *s, unsigned long n) {
  unsigned long len = strlen(s);
  if (n > len) {
    return NULL;
  }
  if (n == 0) {
    return NULL;
  }

  char *result = (char *)malloc((n + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;
  }

  strncpy(result, s, n);

  result[n] = '\0';

  return result;
}

char *HACKERRANK_WARMUP_lastN(const char *s, unsigned long n) {
  unsigned long len = strlen(s);
  if (n > len) {
    return NULL;
  }
  if (n == 0) {
    return NULL;
  }

  char *result = (char *)malloc((n + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;
  }

  strncpy(result, s + len - n, n);

  result[n] = '\0';

  return result;
}

char *HACKERRANK_WARMUP_timeConversion(const char *s) {
  char *conversion;
  char *meridian = HACKERRANK_WARMUP_lastN(s, 2);

  char *hour_str = HACKERRANK_WARMUP_firstN(s, 2);
  char *time_str = (char *)malloc((strlen(s) + 1) * sizeof(char));
  if (time_str == NULL) {
    free(hour_str);
    free(meridian);
    return NULL;
  }
  strcpy(time_str, s);
  time_str = HACKERRANK_WARMUP_lastN(time_str, strlen(time_str) - 2);
  time_str = HACKERRANK_WARMUP_firstN(time_str, strlen(time_str) - 2);

  char *endptr;
  long hour = strtol(hour_str, &endptr, 10);

  if (*endptr != '\0') {
    printf("Conversion error, non-convertible part: %s\n", endptr);

    free(hour_str);
    free(meridian);
    free(time_str);
    free(endptr);
    return NULL;
  } else {
    printf("The integer value is: %ld\n", hour);
  }

  hour = hour % 12;

  if (strcmp(meridian, "PM") == 0) {
    hour += 12;
  }

  const int BUFFER_MAX_SIZE = 9;

  conversion = malloc(BUFFER_MAX_SIZE * sizeof(char));

  snprintf(conversion, BUFFER_MAX_SIZE, "%02ld%s", hour, time_str);
  free(hour_str);
  free(meridian);
  free(time_str);

  return conversion;
}
