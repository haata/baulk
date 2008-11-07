###| CMAKE qtermwidget wrapper |###

#| Project
project( BaulkTermWrapper )
cmake_minimum_required( VERSION 2.6 )


#| Sources
set( SRCS
	./baulkterm.cpp
        ./wrapper_baulkterm.cpp
)

#| Headers
set( HDRS
	./baulkterm.h
)

#| Library
set( LIB
	BaulkTerm
)


#| Baulk Common and qtermwidget Libraries
include_directories(
	${PROJECT_SOURCE_DIR}/../../../Common
	${PROJECT_SOURCE_DIR}/..
	${PROJECT_SOURCE_DIR}/../qtermwidget
)


#| Misc Qt4
add_definitions( 
	-Wall 
	-ggdb
)
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )


#| Library Versioning
set( cat_prog cat )
if( WIN32 )
  if( not UNIX )
    set( cat_prog type )
  endif( not UNIX )
endif( WIN32 )

exec_program( ${cat_prog} 
	ARGS ${PROJECT_SOURCE_DIR}/../../../Common/VERSION 
	OUTPUT_VARIABLE VERSION 
)
set( LIBRARY_VERSION
	"${VERSION}"
)


#| Create the Executable
add_library( ${LIB} SHARED ${SRCS} ${MOC_SRCS} )
set( LIBRARY_OUTPUT_PATH
        ${PROJECT_BINARY_DIR}/../../../../bin/BaulkLibs
)
set_target_properties( ${LIB} PROPERTIES VERSION ${LIBRARY_VERSION} )

#| Link Needed Libraries
target_link_libraries( ${LIB} 
	${QT_LIBRARIES} 
	BaulkWidget	# From Common
	qtermwidget	# From qtermwidget CVS
)

