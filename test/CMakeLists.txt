cmake_minimum_required (VERSION 3.22 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

find_package(stream REQUIRED)
find_package(GTest REQUIRED)
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
  pp::pp
  mp::mp
  tuple::tuple
  stream::stream
  GTest::gtest
  Threads::Threads)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/configure_tests.cmake)
configure_tests("core" "${LIBRARIES}" ${TESTS})
