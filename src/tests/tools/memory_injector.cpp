#include "memory_injector.hpp"
#include <cstdlib>

// Hidden state variables local to this translation unit
static bool force_immediate_error = false;
static int allocation_counter = 0;
static int target_fault_allocation = -1;

namespace MemoryInjector {
void enable_oom_fault() {
  force_immediate_error = true;
  target_fault_allocation = -1;
}

void disable_fault() {
  force_immediate_error = false;
  allocation_counter = 0;
  target_fault_allocation = -1;
}

void fail_on_allocation_number(int n) {
  force_immediate_error = false;
  allocation_counter = 0;
  target_fault_allocation = n;
}
} // namespace MemoryInjector

// Forward declarations with C linkage
extern "C" void *__real_malloc(size_t);

// Global wrapper intercepted by the Linker
extern "C" void *__wrap_malloc(size_t size) {
  // Case 1: Forced immediate out-of-memory error
  if (force_immediate_error) {
    return nullptr;
  }

  // Case 2: Error on the Nth allocation attempt
  if (target_fault_allocation != -1) {
    allocation_counter++;
    if (allocation_counter == target_fault_allocation) {
      return nullptr;
    }
  }

  // If it shouldn't fail, call the real system malloc
  return __real_malloc(size);
}
