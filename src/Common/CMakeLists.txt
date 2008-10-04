###| CMAKE Common |###

###| Project
project( Common )
cmake_minimum_required( VERSION 2.6 )


##| Library Loader

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


##| BaulkXML

#| Sources - BaulkXML
set( SRCS_BXML
        baulkxml.cpp
)

#| Headers - BaulkXML
set( HDRS_BXML
	baulkxml.h
)

#| Library - BaulkXML
set( LIB_BXML
	BaulkXML
)


###| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
set( QT_USE_QTXML 1 )
include( ${QT_USE_FILE} )
include( ${CMAKE_BINARY_DIR} )


##| Library Loader
QT4_WRAP_CPP( MOC_SRCS_LL ${HDRS_LL} )
add_library( ${LIB_LL} SHARED ${SRCS_LL} ${MOC_SRCS_LL} )
target_link_libraries( ${LIB_LL} ${QT_LIBRARIES} )


##| BaulkXML
QT4_WRAP_CPP( MOC_SRCS_BXML ${HDRS_BXML} )
add_library( ${LIB_BXML} SHARED ${SRCS_BXML} ${MOC_SRCS_BXML} )
target_link_libraries( ${LIB_BXML} ${QT_LIBRARIES} )

