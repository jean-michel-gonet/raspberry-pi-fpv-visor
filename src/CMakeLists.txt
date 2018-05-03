# src
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(fpv VERSION 0.1 LANGUAGES CXX)

cmake_policy(SET CMP0057 NEW)

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
message(STATUS "include: ${$ENV{GMOCK_HOME}/include}")

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include $ENV{BOOST_ROOT}/ ${CMAKE_SOURCE_DIR}/library/include)
#link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild )
add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set (FPV_VERSION 1)
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

