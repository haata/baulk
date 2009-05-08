###| CMAKE Baulk X11 |###

#| Project
project( BaulkControl )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../../.. )

#| Sources
set( SRCS
	./xcb_WindowScanner.cpp
)

#| Headers
set( HDRS
	./xcb_WindowScanner.h
)

#| Library
set( LIB
	BaulkX11
)

if ( BuildBaulkControl )
	#| Misc Qt4
	add_definitions( 
		-Wall 
	)
	find_package( Qt4 REQUIRED )
	include( ${QT_USE_FILE} )
	QT4_WRAP_CPP( aMOC_SRCS ${HDRS} )
	
	#| Create the Library
	add_library( ${LIB} SHARED ${SRCS} ${aMOC_SRCS} )
	set( LIBRARY_OUTPUT_PATH
	        ${HEAD_DIR}/bin/BaulkLibs
	)

	#| xcb
	include( FindPkgConfig )
	pkg_check_modules( XCB_COMMON REQUIRED
		xcb>=1.1
		xcb-atom>=0.3.4
		xcb-icccm>=0.3.4
	)
	
	#| Link Needed Libraries
	target_link_libraries( ${LIB} 
		${QT_LIBRARIES}
		${XCB_COMMON_LIBRARIES}
	)
	
	#| Installation
	install( TARGETS ${LIB} DESTINATION lib )
endif ( BuildBaulkControl )

