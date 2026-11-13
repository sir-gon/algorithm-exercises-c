#include "memory_injector.hpp"
#include <cstdlib>
#include <tools/memory_allocator.h>

// Hidden state variables local to this translation unit
static bool force_immediate_error = false;
static int allocation_counter = 0;
static int target_fault_allocation = -1;

static void *faulting_malloc(size_t size) {
  if (force_immediate_error) {
    return nullptr;
  }

  if (target_fault_allocation != -1) {
    allocation_counter++;
    if (allocation_counter == target_fault_allocation) {
      return nullptr;
    }
  }

  return malloc(size);
}

namespace MemoryInjector {
void enable_oom_fault() {
  force_immediate_error = true;
  target_fault_allocation = -1;
  memory_allocator_set_malloc(faulting_malloc);
}

void disable_fault() {
  force_immediate_error = false;
  allocation_counter = 0;
  target_fault_allocation = -1;
  memory_allocator_reset();
}

void fail_on_allocation_number(int n) {
  force_immediate_error = false;
  allocation_counter = 0;
  target_fault_allocation = n;
  memory_allocator_set_malloc(faulting_malloc);
}
} // namespace MemoryInjector
