###| CMAKE Common |###

###| Project
project( Common )
cmake_minimum_required( VERSION 2.6 )


##| Library Loader

#| Sources
set( SRCS_LL
        libraryloader.cpp
)

#| Headers
set( HDRS_LL
	libraryloader.h
)

#| Library
set( LIB_LL
	LibraryLoader
)


##| BaulkXML

#| Sources
set( SRCS_BXML
        baulkxml.cpp
)

#| Headers
set( HDRS_BXML
	baulkxml.h
)

#| Library
set( LIB_BXML
	BaulkXML
)


###| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
set( QT_USE_QTXML 1 )
include( ${QT_USE_FILE} )
include( ${CMAKE_BINARY_DIR} )


##| BaulkXML
QT4_WRAP_CPP( MOC_SRCS_BXML ${HDRS_BXML} )
add_library( ${LIB_BXML} SHARED ${SRCS_BXML} ${MOC_SRCS_BXML} )
target_link_libraries( ${LIB_BXML} ${QT_LIBRARIES} )


##| Library Loader
QT4_WRAP_CPP( MOC_SRCS_LL ${HDRS_LL} )
add_library( ${LIB_LL} SHARED ${SRCS_LL} ${MOC_SRCS_LL} )
target_link_libraries( ${LIB_LL} 
	${QT_LIBRARIES} 
	${LIB_BXML}
)

