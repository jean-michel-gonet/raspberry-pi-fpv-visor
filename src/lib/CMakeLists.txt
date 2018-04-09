# src/lib
project( fpv-lib )

# Find needed libraries:
find_package( OpenCV REQUIRED )

# Does the I2C device exist?
execute_process( COMMAND ls /dev/i2c-1 RESULT_VARIABLE HAVE_I2C OUTPUT_QUIET ERROR_QUIET )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/lib-config.h.in"
	"${PROJECT_BINARY_DIR}/lib-config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# include all includes:
include_directories("include")

# compile the library:
add_library( fpv-lib 
	src/car-service-torment-ecx
	src/i2c-client-mock
	src/i2c-client-wiringpi
	src/image-capture-service-from-camera
	src/service-locator )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(fpv-lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# link to needed libraries
target_link_libraries( fpv-lib ${OpenCV_LIBS} )

# This makes the project importable from the build directory
export(TARGETS fpv-lib FILE fpv-lib.cmake)