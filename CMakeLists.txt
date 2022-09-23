cmake_minimum_required (VERSION 3.22 FATAL_ERROR)
project (string VERSION 0.1 LANGUAGES C CXX)

# Make including this file idempotent
#
if(TARGET string)
  return()
endif()

# Configuration variables.
#
# Build the tests and set directories if this is the master project
#
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(STRING_TEST ON CACHE BOOL "Generate the tests.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_DOCS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
  
  # Have cmake output the compilation commands
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Options for generating tests and documentation.
#
option(STRING_TEST "Generate the tests." OFF)
option(STRING_DOCS "Generate the docs." OFF)

# Add our dependencies
#
include(GNUInstallDirs)
find_package(pp REQUIRED)
find_package(mp REQUIRED)
find_package(tuple REQUIRED)
find_package(fp REQUIRED)
find_package(stream REQUIRED)
find_package(fmt REQUIRED)

# Output configuration
#
message("-- fp: Configuration: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- fp: Included from: ${CMAKE_SOURCE_DIR}")
message("-- fp: STRING_TEST ${STRING_TEST}")
message("-- fp: STRING_DOCS ${STRING_DOCS}")
message("-- fp: CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

# Compilation
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall)
add_compile_options(-stdlib=libc++)
add_compile_options(-O)
add_link_options(-stdlib=libc++)

set(SOURCES
  string/compare
  string/join
  string/lexical_cast
  string/remove_prefix
  string/replace
  string/slurp
  string/split
  string/string
  string/tolower
  string/trim)

foreach(NAME ${SOURCES})
  list(APPEND FILES "src/core/${NAME}.cpp")
endforeach()

add_library(string ${FILES})

target_link_libraries(string PUBLIC
  pp::pp
  mp::mp
  tuple::tuple
  fmt::fmt
  )

target_include_directories(string
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Optionally configure the tests
#
if(STRING_TEST)
  enable_testing()
  if (NOT TARGET check)
    add_custom_target(check ${CMAKE_CTEST_COMMAND})
    add_custom_target(check_detail ${CMAKE_CTEST_COMMAND} -V)
  endif()
  add_subdirectory(test)
endif()

# Optionally configure the documentation
#
# if(STRING_DOCS)
#   add_subdirectory(docs)
# endif()

# Installation
#
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/install_config.cmake)
install_config(string)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/core/string DESTINATION include/core/)
