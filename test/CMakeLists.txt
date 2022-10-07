cmake_minimum_required (VERSION 3.24 FATAL_ERROR)

add_stream()
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

configure_tests("core" "${LIBRARIES}" ${TESTS})
