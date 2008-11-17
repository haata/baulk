###| CMAKE BaulkTerm |###

#| Project
project( BaulkTerm )
cmake_minimum_required( VERSION 2.6 )

#| Baulk Now uses forked version of qtermwidget
#| Prepares the qtermwidget cvs code
#find_package( CVS REQUIRED )
#if( CVS_FOUND AND NOT EXISTS ${PROJECT_SOURCE_DIR}/qtermwidget/qtermwidget.h )
#	execute_process( 
#		COMMAND ${CVS_EXECUTABLE}
#			-z3	
#			-d:pserver:anonymous@qtermwidget.cvs.sourceforge.net:/cvsroot/qtermwidget
#			co 
#			-d qtermwidget 
#			qtermwidget/lib
#		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#	)
#	message(" -------------------------------- ")
#	message(" | CVS QTermWidget source ready | ")
#	message(" -------------------------------- ")
#
#endif( CVS_FOUND AND NOT EXISTS ${PROJECT_SOURCE_DIR}/qtermwidget/qtermwidget.h )

subdirs(
	qtermwidget
	wrapper
)

