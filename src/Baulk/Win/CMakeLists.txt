###| CMAKE Baulk Win |###

#| Project
project( BaulkWin )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../../.. )

#| Sources
set( SRCS
	./win_windowmanipulation.cpp
	./win_windowscanner.cpp
)

#| Headers
set( HDRS
	./win_windowmanipulation.h
	./win_windowscanner.h
)

#| Library
set( LIB
	BaulkWin
)

#if ( BuildBaulkControl )
	#| Misc Qt4
	add_definitions( 
		-Wall 
	)
	find_package( Qt4 REQUIRED )
	include( ${QT_USE_FILE} )
	QT4_WRAP_CPP( aMOC_SRCS ${HDRS} )
	
	#| Create the Library
	add_library( ${LIB} STATIC ${SRCS} ${aMOC_SRCS} )

	#| Link Needed Libraries
	target_link_libraries( ${LIB} 
		${QT_LIBRARIES}
	)
	
	#| Installation
	install( TARGETS ${LIB} DESTINATION lib )
#endif ( BuildBaulkControl )

