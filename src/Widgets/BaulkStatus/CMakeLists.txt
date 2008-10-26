###| CMAKE BaulkStatus |###

#| Project
project( BaulkStatus )
cmake_minimum_required( VERSION 2.6 )


#| Sources
set( SRCS
        ./baulkstatus.cpp
	./wrapper_baulkstatus.cpp
)

#| Headers
set( HDRS
	./baulkstatus.h
)

#| Library
set( LIB
	BaulkStatus
)


#| Baulk Common Libraries
include_directories(
	${PROJECT_SOURCE_DIR}/../../Common
)


#| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )


#| Library Versioning
set( cat_prog cat )
if( WIN32 )
	set( cat_prog type )
endif( WIN32 )

exec_program( ${cat_prog} 
	ARGS ${PROJECT_SOURCE_DIR}/../../Common/VERSION 
	OUTPUT_VARIABLE VERSION 
)
set( LIBRARY_VERSION
	"${VERSION}"
)


#| Create the Library
add_library( ${LIB} SHARED ${SRCS} ${MOC_SRCS} )
set( LIBRARY_OUTPUT_PATH
        ${PROJECT_BINARY_DIR}/../../../bin/BaulkLibs
)
set_target_properties( ${LIB} PROPERTIES VERSION ${LIBRARY_VERSION} )

#| Link Needed Libraries
target_link_libraries( ${LIB} 
	${QT_LIBRARIES} 
	BaulkWidget	# From Common
)

