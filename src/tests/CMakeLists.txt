find_package(Catch2 3 REQUIRED)
find_path(CATCH_INCLUDE_DIR NAMES catch.hpp PATH_SUFFIXES catch2)

# # Create a static library for the memory injector utility
file(GLOB_RECURSE TOOLS_SOURCES "tools/*.cpp")
add_library(memory_injector STATIC ${TOOLS_SOURCES})

file(GLOB_RECURSE SOURCES "unit/lib/*.cpp")
add_executable(unit-tests_combined ${SOURCES})

set_property(TARGET unit-tests_combined PROPERTY CXX_STANDARD 17)

# Test framework dependencies.
target_link_libraries(unit-tests_combined PRIVATE Catch2::Catch2WithMain)

# Functionality to test.
target_link_libraries(unit-tests_combined PRIVATE exercises)

target_link_libraries(unit-tests_combined PRIVATE memory_injector)

# GNU ld (Linux) needs --wrap=malloc to redirect calls to __wrap_malloc.
# macOS uses dyld interposition instead, which requires no linker flag.
if(NOT APPLE)
  target_link_options(memory_injector INTERFACE "-Wl,--wrap=malloc")
endif()

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

catch_discover_tests(unit-tests_combined WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DISCOVERY_MODE "PRE_TEST")
