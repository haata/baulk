###| CMAKE WebBaulk |###

#| Project
project( WebBaulk )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../../.. )


#| Sources
set( SRCS
	./common.cpp
        ./webbaulk.cpp
	./wrapper_webbaulk.cpp
)

#| Headers
set( HDRS
	./common.h
	./webbaulk.h
)

#| Library
set( LIB
	WebBaulk
)


#| Baulk Common Libraries
include_directories(
	${HEAD_DIR}/src/Common
)


#| Misc Qt4
add_definitions( 
	-Wall 
)
find_package( Qt4 REQUIRED )
set( QT_USE_QTWEBKIT 1 )
include( ${QT_USE_FILE} )


#| Library Versioning
set( cat_prog cat )
if( WIN32 )
	set( cat_prog type )
endif( WIN32 )

exec_program( ${cat_prog} 
	ARGS ${HEAD_DIR}/src/Common/VERSION 
	OUTPUT_VARIABLE VERSION 
)
set( LIBRARY_VERSION
	"${VERSION}"
)


if ( BuildWebBaulk )
	QT4_WRAP_CPP( MOC_SRCS ${HDRS} )
	
	#| Create the Executable
	add_library( ${LIB} SHARED ${SRCS} ${MOC_SRCS} )
	set( LIBRARY_OUTPUT_PATH
	        ${HEAD_DIR}/bin/BaulkLibs
	)
	set_target_properties( ${LIB} PROPERTIES VERSION ${LIBRARY_VERSION} )
	
	
	#| Link Needed Libraries
	target_link_libraries( ${LIB} 
		${QT_LIBRARIES} 
		BaulkWidget	# From Common
	)
	
	#| Installation
	install( TARGETS ${LIB}
		DESTINATION lib/BaulkLibs
	)
endif ( BuildWebBaulk )

