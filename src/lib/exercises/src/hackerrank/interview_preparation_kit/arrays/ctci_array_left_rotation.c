#include <stdlib.h>

#include <exercises/hackerrank/interview_preparation_kit/arrays/ctci_array_left_rotation.h>

/**
 * @link Problem definition
 * [[docs/hackerrank/interview_preparation_kit/arrays/ctci_array_left_rotation.md]]
 */

int *rotLeft(int a_count, const int *a, int d, int *result_count) {

  if (a == NULL || a_count <= 0) {
    *result_count = 0;
    return NULL;
  }

  int *result = malloc((size_t)a_count * sizeof(*result));
  if (result == NULL) {
    *result_count = 0;
    return NULL;
  }

  int rotations = d % a_count;

  for (int i = 0; i < a_count; ++i) {
    int new_position = (i + a_count - rotations) % a_count;
    result[new_position] = a[i];
  }

  *result_count = a_count;
  return result;
}
