###| CMAKE Baulk |###

#| Project
project( baulk )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../.. )

subdirs(
	Control
)


#| Sources
set( SRCS
	./baulk.cpp
        ./main.cpp
)

#| Headers
set( HDRS
	./baulk.h
)

#| Executable
set( EXEC
	baulk
)

#| Library
set( LIB
	BaulkLib
)

#| Baulk Common Libraries
include_directories(
	${HEAD_DIR}/src/Common
)

#| Baulk Information Server Libraries
include_directories( Server )

if ( BuildBaulkBinary )
	#| Misc Qt4
	add_definitions( 
		-Wall 
	)
	find_package( Qt4 REQUIRED )
	set( QT_USE_QTNETWORK 1 )
	set( QT_USE_QTTEST 1 )
	include( ${QT_USE_FILE} )
	QT4_WRAP_CPP( MOC_SRCS ${HDRS} )
	
	#| Create the Executable
	add_executable( ${EXEC} ${SRCS} ${MOC_SRCS} )
	set( EXECUTABLE_OUTPUT_PATH
	        ${HEAD_DIR}/bin
	)
	
	#| Library for Win32
	if( WIN32 )
		add_library( ${LIB} STATIC ${SRCS} ${MOC_SRCS} )
	endif( WIN32 )
	
	#| Link Needed Libraries
	target_link_libraries( ${EXEC} 
		${QT_LIBRARIES} 
		LibraryLoader	# From Common
		BaulkWidget	# From Common
	)
	
	#| Installation
	install(
		TARGETS ${EXEC}
		RUNTIME DESTINATION bin
	)
endif ( BuildBaulkBinary )

