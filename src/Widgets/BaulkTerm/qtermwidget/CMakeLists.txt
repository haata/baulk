###| CMAKE qtermwidget/lib |###

#| Project
project ( qtermwidget )
cmake_minimum_required ( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../../../.. )

#| Sources
set ( SRCS
	TerminalCharacterDecoder.cpp
	KeyboardTranslator.cpp 
	Screen.cpp History.cpp BlockArray.cpp konsole_wcwidth.cpp 
	ScreenWindow.cpp 
	Emulation.cpp 
	Vt102Emulation.cpp TerminalDisplay.cpp Filter.cpp 
	Pty.cpp kpty.cpp k3process.cpp k3processcontroller.cpp 
	Session.cpp ShellCommand.cpp 
	qtermwidget.cpp
)

#| Headers
#| 	Only the Headers that need to be moc'd go here
set ( HDRS
	ScreenWindow.h 
	Emulation.h 
	Vt102Emulation.h TerminalDisplay.h Filter.h 
	Pty.h k3process.h k3processcontroller.h 
	Session.h 
	qtermwidget.h
)

#| Library Versioning
#|	Libraries are not versioned by default
set ( qtermwidget_VERSION_MAJOR "0" )
set ( qtermwidget_VERSION_MINOR "1" )
set ( qtermwidget_VERSION_PATCH "0" )
set ( qtermwidget_VERSION 
	"${qtermwidget_VERSION_MAJOR}.${qtermwidget_VERSION_MINOR}.${qtermwidget_VERSION_PATCH}"
)

#| Qt4 Required Options
add_definitions ( -Wall -D NDEBUG )
find_package ( Qt4 REQUIRED ) # Finds Qt4 on the system
include ( ${QT_USE_FILE} ) # Includes Qt4 headers and libraries (the above command is needed first)

if ( BuildQTermWidget )
	QT4_WRAP_CPP ( MOC_SRCS ${HDRS} ) # Moc's the headers
	
	#| qtermwidget specific
	include_directories ( ${PROJECT_SOURCE_DIR} ) 
	
	#| Defines
	add_definitions ( -DHAVE_POSIX_OPENPT )
	#add_definitions( -DHAVE_GETPT )
	
	#| Create the Library
	add_library ( qtermwidget SHARED ${SRCS} ${MOC_SRCS} )
	
	#| Link Qt4 Libraries
	target_link_libraries ( qtermwidget ${QT_LIBRARIES} )
	
	
	#|Installation
	install( TARGETS qtermwidget
		DESTINATION lib
	)
endif ( BuildQTermWidget )

