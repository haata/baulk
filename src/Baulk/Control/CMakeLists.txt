###| CMAKE Baulk Control |###

#| Project
project( BaulkControl )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../../.. )

#| Sources
set( SRCS
	./control.cpp
	./interfacedialog.cpp
        ./wrapper_control.cpp
)

#| Headers
set( HDRS
	./control.h
	./interfacedialog.h
)

#| Library
set( LIB
	BaulkControl
)

#| Baulk Common and Server Libraries
include_directories(
	${HEAD_DIR}/src/Common
	${HEAD_DIR}/src/Server
)

if ( BuildBaulkControl )
	#| Misc Qt4
	add_definitions( 
		-Wall 
	)
	find_package( Qt4 REQUIRED )
	set( QT_USE_QTXML 1 )
	include( ${QT_USE_FILE} )
	QT4_WRAP_CPP( aMOC_SRCS ${HDRS} )
	
	###| Library Versioning
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
	
	#| Create the Library
	add_library( ${LIB} SHARED ${SRCS} ${aMOC_SRCS} )
	set( LIBRARY_OUTPUT_PATH
	        ${HEAD_DIR}/bin/BaulkLibs
	)
	set_target_properties( ${LIB} PROPERTIES VERSION ${LIBRARY_VERSION} )
	
	#| Link Needed Libraries
	if( WIN32 )
	target_link_libraries( ${LIB} 
		${QT_LIBRARIES}
		BaulkDialog	# From Common
		BaulkWidget	# From Common
		BaulkXML	# From Common
		LibraryLoader	# From Common
		BaulkClient	# From Server
		BaulkLib	# From Baulk
	)
	else( WIN32 )
	target_link_libraries( ${LIB} 
		${QT_LIBRARIES}
		BaulkDialog	# From Common
		BaulkWidget	# From Common
		BaulkXML	# From Common
		LibraryLoader	# From Common
		BaulkClient	# From Server
	)
	endif( WIN32 )
	
	#| Installation
	install( TARGETS ${LIB}
		DESTINATION lib/BaulkLibs
	)
endif ( BuildBaulkControl )

