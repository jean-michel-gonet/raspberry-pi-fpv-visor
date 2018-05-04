# src/lib
project( fpv-lib )

# Find needed libraries:
include(GoogleTest)
find_package( OpenCV REQUIRED )
find_package( GTest REQUIRED )

# Does the I2C device exist?
execute_process( COMMAND ls /dev/i2c-1 RESULT_VARIABLE HAVE_I2C OUTPUT_QUIET ERROR_QUIET )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/lib-config.h.in"
	"${PROJECT_BINARY_DIR}/lib-config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# compile the library:
add_library( fpv-lib ${PROJECT_BINARY_DIR}/lib-config.h

	    src/car-service-torment-ecx
	include/car-service-torment-ecx

	    src/i2c-client-mock
	include/i2c-client-mock

	    src/i2c-client-wiringpi
	include/i2c-client-wiringpi
	include/i2c-client

		src/pedestrian-detector-opencv
	include/pedestrian-detector-opencv
	include/pedestrian-detector

	    src/image-capture-service-from-camera
	include/image-capture-service-from-camera

	    src/service-locator
	include/service-locator
)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(fpv-lib 
	PUBLIC
    	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    	$<INSTALL_INTERFACE:include>
    PRIVATE 
		src
)

# link to needed libraries
target_link_libraries( fpv-lib ${OpenCV_LIBS} pthread)

# This makes the project importable from the build directory
export(TARGETS fpv-lib FILE fpv-lib.cmake)

# Builds an executable for testing:
set(PATH_TO_TEST_DATA ${PROJECT_SOURCE_DIR}/test-data)
configure_file (
	"${PROJECT_SOURCE_DIR}/test-config.h.in"
	"${PROJECT_BINARY_DIR}/test-config.h"
)

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE test/catch.hpp)

add_executable(fpv-lib-test
	test/main.cpp
	test/catch.hpp
	${PROJECT_BINARY_DIR}/test-config.h
	
	test/car-service-torment-ecx-test.cpp
	test/pedestrian-detector-opencv-test.cpp
)

target_link_libraries(fpv-lib-test 
	fpv-lib
	pthread
	catch
)
add_test(
	NAME fpv-lib-test 
	COMMAND fpv-lib-test 
	--test-data ${PROJECT_SOURCE_DIR}/test-data
)
