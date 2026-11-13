#include <stdlib.h>

#include "tools/memory_allocator.h"

static memory_allocator_malloc_fn memory_allocator_impl = malloc;

void memory_allocator_set_malloc(memory_allocator_malloc_fn allocator) {
  memory_allocator_impl = (allocator == NULL) ? malloc : allocator;
}

// cppcheck-suppress unusedFunction --- IGNORE ---
memory_allocator_malloc_fn memory_allocator_get_malloc(void) {
  return memory_allocator_impl;
}

void *memory_allocator_malloc(size_t size) {
  return memory_allocator_impl(size);
}

// cppcheck-suppress unusedFunction --- IGNORE ---
void memory_allocator_reset(void) { memory_allocator_impl = malloc; }
