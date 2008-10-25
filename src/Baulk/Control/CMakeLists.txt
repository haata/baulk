###| CMAKE Baulk Control |###

#| Project
project( BaulkControl )
cmake_minimum_required( VERSION 2.6 )

#| Sources
set( SRCS
	./control.cpp
        ./wrapper_control.cpp
)

#| Headers
set( HDRS
	./control.h
)

#| Executable
set( LIB
	BaulkControl
)

#| Baulk Common and Server Libraries
include_directories(
	${PROJECT_SOURCE_DIR}/../../Common
	${PROJECT_SOURCE_DIR}/../Server
)

#| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )

###| Library Versioning
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
if( WIN32 )
target_link_libraries( ${LIB} 
	${QT_LIBRARIES}
	BaulkWidget	# From Common
	LibraryLoader	# From Common
	BaulkClient	# From Server
	BaulkLib	# From Baulk
)
else( WIN32 )
target_link_libraries( ${LIB} 
	${QT_LIBRARIES}
	BaulkWidget	# From Common
	LibraryLoader	# From Common
	BaulkClient	# From Server
)
endif( WIN32 )

