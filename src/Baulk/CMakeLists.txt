###| CMAKE Baulk |###

#| Project
project( baulk )
cmake_minimum_required( VERSION 2.6 )
subdirs(
	#Control
	Server
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

#| Baulk Common Libraries
include_directories(
	${PROJECT_BINARY_DIR}/../Common
	${PROJECT_SOURCE_DIR}/../Common
)
set( CMAKE_LIBRARY_PATH
	${PROJECT_BINARY_DIR}/../Common
)
find_library( LIBRARY_LOADER
	LibraryLoader
)


#| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )
include( ${CMAKE_BINARY_DIR} )

#| Create the Executable
add_executable( ${EXEC} ${SRCS} ${MOC_SRCS} )
set( EXECUTABLE_OUTPUT_PATH
	${PROJECT_BINARY_DIR}/../../bin
)

#| Link Needed Libraries
target_link_libraries( ${EXEC} 
	${QT_LIBRARIES} 
	${LIBRARY_LOADER} 
)

