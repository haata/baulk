###| CMAKE WebBaulk |###

#| Project
project( WebBaulk )
cmake_minimum_required( VERSION 2.6 )


#| Sources
set( SRCS
        ./webbaulk.cpp
	./wrapper_webbaulk.cpp
)

#| Headers
set( HDRS
	./webbaulk.h
)

#| Library
set( LIB
	WebBaulk
)


#| Baulk Common Libraries
include_directories(
	${PROJECT_SOURCE_DIR}/../../Common
)


#| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
set( QT_USE_QTWEBKIT 1 )
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


#| Create the Executable
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

