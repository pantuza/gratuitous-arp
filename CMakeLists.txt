
cmake_minimum_required (VERSION 2.6)
project (garp)

# Sets major and minor versions
set (garp_VERSION_MAJOR 0)
set (garp_VERSION_MINOR 3)

# Sets parameter std=gnu99
SET(CMAKE_C_FLAGS "-std=gnu99" CACHE STRING "" FORCE)

# Configure a header file to pass some of the CMake settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/garp_config.h.in"
  "${PROJECT_BINARY_DIR}/garp_config.h"
  )


# add the binary tree to the search path for finding garp_config.h
include_directories("${PROJECT_BINARY_DIR}")

add_executable(garp garp.c)
