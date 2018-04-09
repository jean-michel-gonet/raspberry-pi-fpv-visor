# src/app
project( fpv )

# GTKMM has to be linked/included via pkg_config:
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0) # Defines variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES.
link_directories( ${GTKMM_LIBRARY_DIRS} )
include_directories( ${GTKMM_INCLUDE_DIRS} )

# OpenCV can be linked as usual:
find_package( OpenCV REQUIRED )

# Compile files:
add_executable(fpv 
    main
    main-window 
    auto-viseur )

# Link files:
target_link_libraries(fpv
   fpv-lib
   ${GTKMM_LIBRARIES}  
   ${OpenCV_LIBS} )
