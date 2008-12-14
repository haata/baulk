###| CMAKE Baulk (Top-Level Build) |###

#| Build Target Variable Information
#
# set using "cmake -D<variable>=<true/false> ."
#
# Note: You only need to set the variable once, at that point it will be in the variable
# 	 cache. You will only need to set the variable again if you want to turn it off.
# 
# | BuildAll			- Builds everything 
# | BuildReset			- Initializes build variables to zero before determining dependencies
#				Note: This variable stays on, so you must set it to false if you want
#					to build
# 
# Folder Builds
# | BuildBaulk			- Builds Baulk (Default)
# | BuildCommon			- Build Common libraries
# | BuildWidgets		- Build Widgets
#
# Baulk Binary Builds
# | BuildBaulkBinary		- Build minimum for the Baulk Binary (No BaulkServ)
# | BuildBaulkControl		- Build BaulkControl Library
# | BuildBaulkPacket		- Build BaulkPacket Library
# | BuildBaulkServBinary	- Build minimum for the BaulkServ Binary
# | BuildBaulkServClient	- Build BaulkServ Client Library
# | BuildBaulkServServer	- Build BaulkServ Server Library
#
# Common Library Builds
# | BuildBaulkDialog		- Builds BaulkDialog Library
# | BuildBaulkWidget		- Builds BaulkWidget Library
# | BuildBaulkWindow		- Builds BaulkWindow Library
# | BuildBaulkXML		- Builds BaulkXML Library
# | BuildLibLoader		- Builds Library Loader (BaulkXML will automatically be built as well)
#
# Widget Builds
# | BuildBaulkStatus		- Builds BaulkStatus
# | BuildBaulkSwallow		- Builds BaulkSwallow
# | BuildBaulkTerm		- Builds BaulkTerm
# | BuildWebBaulk		- Builds WebBaulk
#
# BaulkTerm Special Builds
# | BuildBaulkTermBinary 	- Builds binary version of BaulkTerm
# | BuildQTermWidget		- Builds QTermWidget library
#
#|

##| Project
project( BaulkTOPLEVEL )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/.. )

subdirs(
	Common
	Baulk
	Server
	Widgets
)

##| Target Reset
if ( BuildReset )
	set( BuildAll			0 )
	set( BuildBaulk			0 )
	set( BuildBaulkBinary 		0 )
	set( BuildBaulkControl 		0 )
	set( BuildBaulkDialog		0 )
	set( BuildBaulkPacket		0 )
	set( BuildBaulkServBinary	0 )
	set( BuildBaulkServClient	0 )
	set( BuildBaulkServServer	0 )
	set( BuildBaulkStatus		0 )
	set( BuildBaulkSwallow		0 )
	set( BuildBaulkTerm		0 )
	set( BuildBaulkTermBinary	0 )
	set( BuildBaulkWidget		0 )
	set( BuildBaulkXML		0 )
	set( BuildCommon		0 )
	set( BuildLibLoader		0 )
	set( BuildQTermWidget		0 )
	set( BuildWebBaulk		0 )
	set( BuildWidgets		0 )
endif ( BuildReset )


##| Targets - Note: Options are disabled by default

#| Full Build
if ( BuildAll )
	set( BuildBaulk 		1 )
	set( BuildBaulkTermBinary	1 )
endif ( BuildAll )


#| Default
if ( BuildBaulk )
	set( BuildBaulkBinary 		1 )
	set( BuildBaulkServBinary	1 )
	set( BuildCommon		1 )
	set( BuildWidgets		1 )
endif ( BuildBaulk )


#| Common Librarys
if ( BuildCommon )
	set( BuildBaulkDialog		1 )
	set( BuildBaulkWidget		1 )
	set( BuildBaulkXML		1 )
	set( BuildLibLoader		1 )
endif ( BuildCommon )


#| Widget Libraries
if ( BuildWidgets )
	set( BuildBaulkStatus		1 )
	set( BuildBaulkSwallow		1 )
	set( BuildBaulkTerm		1 )
	set( BuildWebBaulk		1 )
endif ( BuildWidgets )


#| Baulk Binary
if ( BuildBaulkBinary )
	set( BuildBaulkControl 		1 )
	set( BuildLibLoader		1 )
	set( BuildBaulkWidget		1 )
endif ( BuildBaulkBinary )


#| BaulkControl Library
if ( BuildBaulkControl )
	set( BuildBaulkServClient	1 )
	set( BuildBaulkDialog		1 )
	set( BuildBaulkWidget		1 )
	set( BuildBaulkXML		1 )
	set( BuildLibLoader		1 )
	if ( WIN32 )
		set( BuildBaulkBinary	1 )
	endif ( WIN32 )
endif ( BuildBaulkControl )


#| BaulkServ Binary
if ( BuildBaulkServBinary )
	set( BuildBaulkServClient	1 )
	set( BuildBaulkServServer	1 )
	set( BuildBaulkPacket		1 )
endif ( BuildBaulkServBinary )


#| BaulkTerm Binary Build
if ( BuildBaulkTermBinary )
	set( BuildBaulkTerm		1 )
	set( BuildBaulkServServer	1 )
	set( BuildBaulkServClient	1 )
	set( BuildQTermWidget		1 )
endif ( BuildBaulkTermBinary )


#| BaulkServ Client
if ( BuildBaulkServClient )
	set( BuildBaulkPacket		1 )
endif ( BuildBaulkServClient )


#| BaulkTerm Library
if ( BuildBaulkTerm )
	set( BuildQTermWidget		1 )
	set( BuildBaulkWidget		1 )
	set( BuildBaulkWindow		1 )
	set( BuildBaulkXML		1 )
endif ( BuildBaulkTerm )


#| Warning if the user forgot to specify a Build Variable
if ( BuildBaulkPacket OR BuildBaulkDialog OR BuildBaulkWidget OR BuildBaulkXML OR BuildQTermWidget )
else ( BuildBaulkPacket OR BuildBaulkDialog OR BuildBaulkWidget OR BuildBaulkXML OR BuildQTermWidget )
	message("||Warning||")
	message("  You forgot to specify a build option (make will do nothing)")
	message("    For Baulk     : cmake -DBuildBaulk=true .")
	message("    For BaulkTerm : cmake -DBuildBaulkTermBinary=true .")
	message("")
	message("  See header in src/CMakeLists.txt for more options")
endif ( BuildBaulkPacket OR BuildBaulkDialog OR BuildBaulkWidget OR BuildBaulkXML OR BuildQTermWidget )


##| Doxygen
find_package( Doxygen ) 
if( DOXYGEN_FOUND )
	execute_process( COMMAND ${DOXYGEN_EXECUTABLE} WORKING_DIRECTORY ${HEAD_DIR}/docs )
endif( DOXYGEN_FOUND )

