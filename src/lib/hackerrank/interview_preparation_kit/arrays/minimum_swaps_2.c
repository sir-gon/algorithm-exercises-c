#include <stdlib.h>

#include <exercises/hackerrank/interview_preparation_kit/arrays/minimum_swaps_2.h>

/**
 * @link Problem definition
 * [[docs/hackerrank/interview_preparation_kit/arrays/minimum_swaps_2.md]]
 */

// cppcheck-suppress constParameterPointer
int minimumSwaps(int arr_count, int *arr) {
  int *indexed_group = malloc(arr_count * sizeof(int));
  if (indexed_group == NULL) {
    return -1;
  }

  for (int i = 0; i < arr_count; i++) {
    indexed_group[i] = arr[i] - 1;
  }

  int swaps = 0;
  int index = 0;

  while (index < arr_count) {
    if (indexed_group[index] == index) {
      index += 1;
    } else {
      int temp = indexed_group[index];
      indexed_group[index] = indexed_group[temp];
      indexed_group[temp] = temp;
      swaps += 1;
    }
  }

  free(indexed_group);
  return swaps;
}
