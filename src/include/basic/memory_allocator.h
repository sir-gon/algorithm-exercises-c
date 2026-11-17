#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*memory_allocator_malloc_fn)(size_t size);

void memory_allocator_set_malloc(memory_allocator_malloc_fn allocator);
memory_allocator_malloc_fn memory_allocator_get_malloc(void);
void *memory_allocator_malloc(size_t size);
void memory_allocator_reset(void);

#ifdef __cplusplus
}
#endif

#endif // MEMORY_ALLOCATOR_H
