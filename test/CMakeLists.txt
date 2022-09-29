cmake_minimum_required (VERSION 3.22 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

cpp_core_find_package(stream)
cpp_core_find_package(GTest
  URL https://github.com/cpp-core/googletest
  VERSION v1.12.0
  EXCLUDE_FROM_ALL)
find_package(Threads REQUIRED)

set(TESTS
  string/compare
  string/fixed
  string/join
  string/lexical_cast
  string/lexical_cast_stl
  string/remove_prefix
  string/replace
  string/split
  string/string
  string/tolower
  string/trim
  )

set(LIBRARIES
  string
  stream::stream
  GTest::gtest
  Threads::Threads)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/configure_tests.cmake)
configure_tests("core" "${LIBRARIES}" ${TESTS})
