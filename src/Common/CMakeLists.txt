###| CMAKE Common |###

###| Project
project( Common )
cmake_minimum_required( VERSION 2.6 )


##| Baulk Widget

#| Sources
set( SRCS_BW
	./baulkwidget.cpp
)

#| Headers
set( HDRS_BW
	./baulkwidget.h
)

#| Library
set( LIB_BW
	BaulkWidget
)


##| Baulk Dialog

#| Sources
set( SRCS_BD
	./baulkdialog.cpp
)

#| Headers
set( HDRS_BD
	./baulkdialog.h
)

#| Library
set( LIB_BD
	BaulkDialog
)


##| Library Loader

#| Sources
set( SRCS_LL
        ./libraryloader.cpp
)

#| Headers
set( HDRS_LL
	./libraryloader.h
)

#| Library
set( LIB_LL
	LibraryLoader
)


##| BaulkXML

#| Sources
set( SRCS_BXML
        ./baulkxml.cpp
)

#| Headers
set( HDRS_BXML
	./baulkxml.h
)

#| Library
set( LIB_BXML
	BaulkXML
)


###| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
set( QT_USE_QTXML 1 )
include( ${QT_USE_FILE} )


##| Baulk Widget
QT4_WRAP_CPP( MOC_SRCS_BW ${HDRS_BW} )

if ( WIN32 )
	add_library( ${LIB_BW} STATIC ${SRCS_BW} ${MOC_SRCS_BW} )
else ( WIN32 )
	add_library( ${LIB_BW} SHARED ${SRCS_BW} ${MOC_SRCS_BW} )
endif( WIN32 )

target_link_libraries( ${LIB_BW} ${QT_LIBRARIES} )


##| Baulk Dialog
QT4_WRAP_CPP( MOC_SRCS_BD ${HDRS_BD} )

if ( WIN32 )
	add_library( ${LIB_BD} STATIC ${SRCS_BD} ${MOC_SRCS_BD} )
else ( WIN32 )
	add_library( ${LIB_BD} SHARED ${SRCS_BD} ${MOC_SRCS_BD} )
endif( WIN32 )

target_link_libraries( ${LIB_BD} ${QT_LIBRARIES} )


##| BaulkXML
QT4_WRAP_CPP( MOC_SRCS_BXML ${HDRS_BXML} )

if ( WIN32 )
	add_library( ${LIB_BXML} STATIC ${SRCS_BXML} ${MOC_SRCS_BXML} )
else ( WIN32 )
	add_library( ${LIB_BXML} SHARED ${SRCS_BXML} ${MOC_SRCS_BXML} )
endif( WIN32 )

target_link_libraries( ${LIB_BXML} ${QT_LIBRARIES} )


##| Library Loader
QT4_WRAP_CPP( MOC_SRCS_LL ${HDRS_LL} )

if ( WIN32 )
	add_library( ${LIB_LL} STATIC ${SRCS_LL} ${MOC_SRCS_LL} )
else ( WIN32 )
	add_library( ${LIB_LL} SHARED ${SRCS_LL} ${MOC_SRCS_LL} )
endif( WIN32 )

target_link_libraries( ${LIB_LL} 
	${QT_LIBRARIES} 
	${LIB_BXML}
	${LIB_BW}
)

