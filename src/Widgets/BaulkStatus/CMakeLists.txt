###| CMAKE BaulkStatus |###

#| Project
project( BaulkStatus )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../../.. )


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
	${HEAD_DIR}/src/Common
)


#| Misc Qt4
add_definitions( 
	-Wall 
)
find_package( Qt4 REQUIRED )
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

if ( BuildBaulkStatus )
	QT4_WRAP_CPP( MOC_SRCS ${HDRS} )

	#| Create the Library
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
endif ( BuildBaulkStatus )

