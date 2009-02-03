###| CMAKE Common |###

###| Project
project( Common )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../.. )


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


##| Baulk Window

#| Sources
set( SRCS_BWN
	./baulkwindow.cpp
)

#| Headers
set( HDRS_BWN
	./baulkwindow.h
)

#| Library
set( LIB_BWN
	BaulkWindow
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


###| Build Information
execute_process ( 	
	# This will fail if you don't have git in your path; however,
	#  if you don't have git in your path, you fail at life.
	#  I also don't feel like writing a detection module.
	COMMAND git log --pretty=format:%h -n 1
	OUTPUT_VARIABLE git_hash
)

if ( WIN32 )
	execute_process (
		COMMAND date /t
		OUTPUT_VARIABLE BUILD_DATE_TMP
	)
	set ( BUILD_DATE ${BUILD_DATE_TMP}\" )
else ( WIN32 )
	execute_process (
		COMMAND date +%c\"
		OUTPUT_VARIABLE BUILD_DATE
	)
endif ( WIN32 )

set ( BUILD_VERSION "${git_hash}" )
set ( CONFIG_FILE builddefines )
configure_file ( ${PROJECT_SOURCE_DIR}/${CONFIG_FILE}.cmake ${PROJECT_SOURCE_DIR}/${CONFIG_FILE}.h )


###| Misc Qt4
add_definitions( 
	-Wall 
)
find_package( Qt4 REQUIRED )
set( QT_USE_QTXML 1 )
include( ${QT_USE_FILE} )


##| Baulk Widget
if ( BuildBaulkWidget )
	QT4_WRAP_CPP( MOC_SRCS_BW ${HDRS_BW} )
	
	if ( WIN32 )
		add_library( ${LIB_BW} STATIC ${SRCS_BW} ${MOC_SRCS_BW} )
	else ( WIN32 )
		add_library( ${LIB_BW} SHARED ${SRCS_BW} ${MOC_SRCS_BW} )
	endif( WIN32 )
	
	target_link_libraries( ${LIB_BW} ${QT_LIBRARIES} )
	install( TARGETS ${LIB_BW} DESTINATION lib )
endif ( BuildBaulkWidget )


##| Baulk Window
if ( BuildBaulkWindow )
	QT4_WRAP_CPP( MOC_SRCS_BWN ${HDRS_BWN} )
	
	if ( WIN32 )
		add_library( ${LIB_BWN} STATIC ${SRCS_BWN} ${MOC_SRCS_BWN} )
	else ( WIN32 )
		add_library( ${LIB_BWN} SHARED ${SRCS_BWN} ${MOC_SRCS_BWN} )
	endif( WIN32 )

	target_link_libraries( ${LIB_BWN} ${QT_LIBRARIES} )
	install( TARGETS ${LIB_BWN} DESTINATION lib )
endif ( BuildBaulkWindow )


##| Baulk Dialog
if ( BuildBaulkDialog )
	QT4_WRAP_CPP( MOC_SRCS_BD ${HDRS_BD} )
	
	if ( WIN32 )
		add_library( ${LIB_BD} STATIC ${SRCS_BD} ${MOC_SRCS_BD} )
	else ( WIN32 )
		add_library( ${LIB_BD} SHARED ${SRCS_BD} ${MOC_SRCS_BD} )
	endif( WIN32 )
	
	target_link_libraries( ${LIB_BD} ${QT_LIBRARIES} )
	install( TARGETS ${LIB_BD} DESTINATION lib )
endif ( BuildBaulkDialog )


##| BaulkXML
if ( BuildBaulkXML )
	QT4_WRAP_CPP( MOC_SRCS_BXML ${HDRS_BXML} )
	
	if ( WIN32 )
		add_library( ${LIB_BXML} STATIC ${SRCS_BXML} ${MOC_SRCS_BXML} )
	else ( WIN32 )
		add_library( ${LIB_BXML} SHARED ${SRCS_BXML} ${MOC_SRCS_BXML} )
	endif( WIN32 )
	
	target_link_libraries( ${LIB_BXML} ${QT_LIBRARIES} )
	install( TARGETS ${LIB_BXML} DESTINATION lib )
endif ( BuildBaulkXML )


##| Library Loader
if ( BuildLibLoader )
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
	install( TARGETS ${LIB_LL} DESTINATION lib )
endif ( BuildLibLoader )

