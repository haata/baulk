###| CMAKE qtermwidget wrapper |###

#| Project
project( BaulkTermWrapper )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../../../.. )


#| Sources
set( SRCS
	./baulkterm.cpp
	./rightclickmenu.cpp
	./terminalcolour.cpp
        ./wrapper_baulkterm.cpp
)

#| Headers
set( HDRS
	./baulkterm.h
	./rightclickmenu.h
)

#| Library
set( LIB
	BaulkTerm
)


#| Baulk Common and qtermwidget Libraries
include_directories(
	${HEAD_DIR}/src/Common
	${HEAD_DIR}/src/Server
	${HEAD_DIR}/src/Widgets/BaulkTerm/qtermwidget
)


#| Misc Qt4
add_definitions( 
	-Wall 
)
find_package( Qt4 REQUIRED )
set( QT_USE_QTXML 1 )
set( QT_USE_QTNETWORK 1 )
set( QT_USE_QTTEST 1 )

include( ${QT_USE_FILE} )


#| Library Versioning
set( cat_prog cat )
if( WIN32 )
  if( not UNIX )
    set( cat_prog type )
  endif( not UNIX )
endif( WIN32 )

exec_program( ${cat_prog} 
	ARGS ${HEAD_DIR}/src/Common/VERSION 
	OUTPUT_VARIABLE VERSION 
)
set( LIBRARY_VERSION
	"${VERSION}"
)

if ( BuildBaulkTerm )
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
		BaulkWindow	# From Common
		BaulkXML	# From Common
		qtermwidget	# From qtermwidget CVS
	)

	#| Installation
	install( TARGETS ${LIB}	DESTINATION lib/BaulkLibs )
endif ( BuildBaulkTerm )

if ( BuildBaulkTermBinary )
	##| Standalone Binary
	set( EXEC baulkTerm )
	set( EXECUTABLE_OUTPUT_PATH
		${HEAD_DIR}/bin
	)
	
	add_executable( ${EXEC} main.cpp )
	target_link_libraries( ${EXEC} 
		${LIB} 
		BaulkClient	# From Server
		BaulkServer	# From Server
	)

	#| Installation
	install( TARGETS ${EXEC} DESTINATION bin )
	install( TARGETS ${LIB} DESTINATION lib	)
endif ( BuildBaulkTermBinary )

