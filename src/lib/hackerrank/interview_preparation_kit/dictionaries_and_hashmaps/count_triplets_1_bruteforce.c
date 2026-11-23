#include <exercises/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/count_triplets_1_bruteforce.h>

/**
 * @link Problem definition
 * [[docs/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/count_triplets_1.md]]
 */

long countTripletsBruteForce(int arr_count, long *arr, long r) {
  long counter = 0;

  for (unsigned int i = 0; i != arr_count - 2; ++i) {
    for (unsigned int j = i + 1; j != arr_count - 1; ++j) {
      for (unsigned int k = j + 1; k != arr_count; ++k) {
        counter = arr[i] * r == arr[j] && arr[j] * r == arr[k] ? counter + 1
                                                               : counter;
      }
    }
  }
  return counter;
}
