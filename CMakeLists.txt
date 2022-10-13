cmake_minimum_required (VERSION 3.24 FATAL_ERROR)
project (string VERSION 0.1 LANGUAGES C CXX)

# Make including this file idempotent
#
if(TARGET string OR TARGET string::string)
  return()
endif()

# If this is the current project.
#
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Laod the cmake recipes and utilities.
  #
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/load_cmake_helpers.cmake)

  # Options for generating tests and documentation.
  #
  option(STRING_TEST "Generate the tests." ON)
  option(STRING_DOCS "Generate the docs." OFF)

  # compile_commands.json
  #
  symlink_compile_commands()

  # Convenience targets for git operations
  #
  make_submodule_pull_target()

else()
  option(STRING_TEST "Generate the tests." OFF)
  option(STRING_DOCS "Generate the docs." OFF)
endif()

# Put executables in the top-level binary directory
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Output configuration
#
message("-- string: Configuration: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- string: Included from: ${CMAKE_SOURCE_DIR}")
message("-- string: Install prefix ${CMAKE_INSTALL_PREFIX}")
message("-- string: test ${STRING_TEST}")
message("-- string: docs ${STRING_DOCS}")

# Setup the compilation before adding dependencies
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall)
add_compile_options(-stdlib=libc++)
add_compile_options(-O)
add_link_options(-stdlib=libc++)

# Add our dependencies
#
add_fp()
add_tuple()

# Build the library
#
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

set(FILES)
foreach(NAME ${SOURCES})
  list(APPEND FILES "src/core/${NAME}.cpp")
endforeach()

add_library(string ${FILES})
add_library(string::string ALIAS string)

# Define the header files for this library.
#
file(GLOB_RECURSE PUBLIC_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.h)
target_sources(string PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${PUBLIC_INCLUDE_FILES})

target_link_libraries(string PUBLIC fp::fp tuple::tuple)

# Optionally configure the tests
#
if(STRING_TEST)
  add_gtest()
  add_subdirectory(test)
endif()

# Optionally configure the documentation
#
# if(STRING_DOCS)
#   add_subdirectory(docs)
# endif()

# Installation
#
install_config(string)
