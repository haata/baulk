###| CMAKE BaulkTerm |###

#| Project
project( BaulkTerm )
cmake_minimum_required( VERSION 2.6 )

#| Prepares the qtermwidget cvs code
find_package( CVS REQUIRED )
if( NOT EXISTS ${PROJECT_SOURCE_DIR}/qtermwidget/qtermwidget.h )
	execute_process( 
		COMMAND cvs 
			-z3	
			-d:pserver:anonymous@qtermwidget.cvs.sourceforge.net:/cvsroot/qtermwidget
			co 
			-d qtermwidget 
			qtermwidget/lib
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	)
	message(" -------------------------------- ")
	message(" | CVS qtermwidget source ready | ")
	message(" -------------------------------- ")

endif( NOT EXISTS ${PROJECT_SOURCE_DIR}/qtermwidget/qtermwidget.h )

subdirs(
	qtermwidget
	wrapper
)

