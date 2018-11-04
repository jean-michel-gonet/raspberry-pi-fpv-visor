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
    main.cpp
	
    main-window.cpp
    main-window.hpp

    auto-viseur.cpp
    auto-viseur.hpp
 )

# Link files:
target_link_libraries(fpv
   fpv-lib
   ${GTKMM_LIBRARIES}  
   ${OpenCV_LIBS} )

# Lets bundle it:
if (APPLE)
	set_target_properties(fpv PROPERTIES
	  MACOSX_BUNDLE TRUE
	  MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
	)
endif()