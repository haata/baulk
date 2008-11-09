###| CMAKE Baulk (Top-Level Build) |###

#| Project
project( BaulkTOPLEVEL )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/.. )

subdirs(
	Common
	Baulk
	Widgets
)

#| Doxygen
find_package( Doxygen ) 
if( DOXYGEN_FOUND )
	execute_process( COMMAND ${DOXYGEN_EXECUTABLE} ${HEAD_DIR}/docs )
endif( DOXYGEN_FOUND )

