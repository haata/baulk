###| CMAKE Common |###

#| Project
project( Common )
cmake_minimum_required( VERSION 2.6 )

#| Sources - Library Loader
set( SRCS_LL
        libraryloader.cpp
)

#| Headers - Library Loader
set( HDRS_LL
	libraryloader.h
)

#| Library - Library Loader
set( LIB_LL
	LibraryLoader
)

#| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
include( ${CMAKE_BINARY_DIR} )
QT4_WRAP_CPP( MOC_SRCS_LL ${HDRS_LL} )

#| Create the Library Loader Library
add_library( ${LIB_LL} ${SRCS_LL} ${MOC_SRCS_LL} )

#| Link Needed Libraries
target_link_libraries( ${LIB_LL} ${QT_LIBRARIES} )

