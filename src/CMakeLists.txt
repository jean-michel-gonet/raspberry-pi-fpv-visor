# src
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(fpv VERSION 0.1 LANGUAGES CXX)

set (FPV_VERSION 1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Must use GNUInstallDirs to install libraries into correct locations on all platforms:
include(GNUInstallDirs)

# We want to test:
enable_testing()

# Targets that we develop here
add_subdirectory(lib)
add_subdirectory(app)