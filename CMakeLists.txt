cmake_minimum_required (VERSION 3.1)
project (raspberry-pi-fpv-visor)

# Does the I2C device exist?
execute_process(COMMAND ls /dev/i2c-1 RESULT_VARIABLE HAVE_I2C OUTPUT_QUIET ERROR_QUIET)

# Version number:
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

# configure a header file to pass the CMake settings to the source code:
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

# add the binary tree to the search path for include files
# so that we will find config.h
include_directories("${PROJECT_BINARY_DIR}")

# Add the executable:
add_executable(raspberry-pi-fpv-visor tutorial.cxx)

# add the install targets
install (TARGETS raspberry-pi-fpv-visor DESTINATION bin)


include(CTest)

# does the application run
add_test (Test1 raspberry-pi-fpv-visor 25)
set_tests_properties (Test1 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")
