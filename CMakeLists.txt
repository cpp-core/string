cmake_minimum_required (VERSION 3.22 FATAL_ERROR)
project (string VERSION 0.1 LANGUAGES C CXX)

# Make including this file idempotent
#
if(TARGET string OR TARGET string::string)
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
  
  # Have cmake output the compilation commands and create a link to it
  # from the project root directory so the language server can find
  # it.
  #
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json)
endif()

# Options for generating tests and documentation.
#
option(STRING_TEST "Generate the tests." OFF)
option(STRING_DOCS "Generate the docs." OFF)

# Output configuration
#
message("-- string: Configuration: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- string: Included from: ${CMAKE_SOURCE_DIR}")
message("-- string: STRING_TEST ${STRING_TEST}")
message("-- string: STRING_DOCS ${STRING_DOCS}")
message("-- string: CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

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
include(cmake/cpp_core_find_package.cmake)
cpp_core_find_package(fp)
cpp_core_find_package(tuple)

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

# Define the header files for this library.
#
file(GLOB_RECURSE PUBLIC_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.h)
target_sources(string PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${PUBLIC_INCLUDE_FILES})

target_link_libraries(string PUBLIC fp::fp tuple::tuple)

# Optionally configure the tests
#
if(STRING_TEST)
  enable_testing()
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
