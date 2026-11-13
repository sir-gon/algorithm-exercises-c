#include <catch2/catch_test_macros.hpp>

#include <cstdlib>
#include <tools/memory_allocator.h>

static size_t custom_allocator_last_size = 0;
static int custom_allocator_calls = 0;
static int custom_allocator_value = 42;

static void *custom_malloc(size_t size) {
  custom_allocator_last_size = size;
  custom_allocator_calls += 1;
  return &custom_allocator_value;
}

static void *null_malloc(size_t size) {
  (void)size;
  return nullptr;
}

TEST_CASE("memory_allocator defaults to malloc and can be overridden",
          "[tools] [memory_allocator]") {
  memory_allocator_reset();

  SECTION("default allocator is malloc") {
    memory_allocator_reset();
    REQUIRE(memory_allocator_get_malloc() == malloc);
    const void *ptr = memory_allocator_malloc(64);
    REQUIRE(ptr != nullptr);
    free(const_cast<void *>(ptr));
  }

  SECTION("custom allocator can replace malloc") {
    memory_allocator_reset();
    custom_allocator_last_size = 0;
    custom_allocator_calls = 0;

    memory_allocator_set_malloc(custom_malloc);
    REQUIRE(memory_allocator_get_malloc() == custom_malloc);

    const void *ptr = memory_allocator_malloc(128);
    REQUIRE(ptr == &custom_allocator_value);
    REQUIRE(custom_allocator_last_size == 128);
    REQUIRE(custom_allocator_calls == 1);

    memory_allocator_reset();
    REQUIRE(memory_allocator_get_malloc() == malloc);
  }

  SECTION("null setter restores the default allocator") {
    memory_allocator_reset();
    memory_allocator_set_malloc(nullptr);
    REQUIRE(memory_allocator_get_malloc() == malloc);

    const void *ptr = memory_allocator_malloc(32);
    REQUIRE(ptr != nullptr);
    free(const_cast<void *>(ptr));
  }

  SECTION("custom allocator returning null propagates NULL") {
    memory_allocator_set_malloc(null_malloc);
    REQUIRE(memory_allocator_get_malloc() == null_malloc);
    REQUIRE(memory_allocator_malloc(256) == nullptr);

    memory_allocator_reset();
    REQUIRE(memory_allocator_get_malloc() == malloc);
  }
}
