###| CMAKE Baulk |###

#| Project
project( baulk )
cmake_minimum_required( VERSION 2.6 )

#| Sources
set( SRCS
        ./main.cpp
)

#| Headers
set( HDRS
)

#| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
QT4_WRAP_CPP( MOC_SRCS ${HDRS} )
include( ${CMAKE_BINARY_DIR} )

#| Create the Executable
add_executable( quillTex ${SRCS} ${MOC_SRCS} )

#| Link Needed Libraries
target_link_libraries( quillTex ${QT_LIBRARIES} )

