#include <basic/memory_allocator.h>
#include <exercises/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/count_triplets_1_optimized.h>
#include <stdlib.h> // free

/**
 * @link Problem definition
 * [[docs/hackerrank/interview_preparation_kit/dictionaries_and_hashmaps/count-triplets.md]]
 */

typedef struct Counter {
  long value;
  long count;
  struct Counter *next;
} Counter;

#define HASH_SIZE 1009

static int hash(long value) {
  long normalized = value % HASH_SIZE;
  return (int)(normalized < 0 ? normalized + HASH_SIZE : normalized);
}

static Counter *find_counter(Counter *bucket, long value) {
  while (bucket != NULL) {
    if (bucket->value == value) {
      return bucket;
    }
    bucket = bucket->next;
  }

  return NULL;
}

static Counter *create_counter(long value, long how_many) {
  Counter *counter = (Counter *)memory_allocator_malloc(sizeof(Counter));
  if (counter == NULL) {
    return NULL;
  }

  counter->value = value;
  counter->count = how_many;
  counter->next = NULL;
  return counter;
}

static Counter *insert_counter(Counter **bucket, long value, long how_many) {
  int hash_sign = hash(value);
  Counter *found_counter = find_counter(bucket[hash_sign], value);
  if (found_counter != NULL) {
    found_counter->count += how_many;
    return found_counter;
  }

  Counter *new_counter = create_counter(value, how_many);
  if (new_counter == NULL) {
    return NULL;
  }

  new_counter->next = bucket[hash_sign];
  bucket[hash_sign] = new_counter;
  return new_counter;
}

static void free_counter_buckets(Counter *buckets[HASH_SIZE]) {
  for (int i = 0; i < HASH_SIZE; ++i) {
    Counter *current = buckets[i];
    while (current != NULL) {
      Counter *next = current->next;
      free(current);
      current = next;
    }
  }
}

long countTriplets(int arr_count, const long *arr, long r) {
  Counter *potential_twos[HASH_SIZE] = {NULL};
  Counter *potential_threes[HASH_SIZE] = {NULL};
  long counter = 0;

  for (int i = 0; i < arr_count; i++) {
    const Counter *found_potential_three =
        find_counter(potential_threes[hash(arr[i])], arr[i]);

    if (found_potential_three != NULL) {
      counter += found_potential_three->count;
    }

    const Counter *found_potential_two =
        find_counter(potential_twos[hash(arr[i])], arr[i]);

    if (found_potential_two != NULL) {
      const long next_key = arr[i] * r;
      insert_counter(potential_threes, next_key, found_potential_two->count);
    }

    const long next_key = arr[i] * r;
    insert_counter(potential_twos, next_key, 1);
  }

  free_counter_buckets(potential_twos);
  free_counter_buckets(potential_threes);

  return counter;
}
