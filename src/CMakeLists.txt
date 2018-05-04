# src
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(fpv VERSION 0.1 LANGUAGES CXX)

cmake_policy(SET CMP0057 NEW)

add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(FPV_VERSION 1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Must use GNUInstallDirs to install libraries into correct locations on all platforms:
include(GNUInstallDirs)

# To allow 'make test' command.
# Put this before 'add_subdirectory'
enable_testing()

# Targets that we develop here
add_subdirectory(lib)
add_subdirectory(app)

