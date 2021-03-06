###| CMAKE Baulk Server/Client |###

###| Project
project( BaulkServerClient )
cmake_minimum_required( VERSION 2.6 )
set( HEAD_DIR ${PROJECT_SOURCE_DIR}/../.. )


##| Baulk Server

#| Sources
set( SRCS_BS
        ./server.cpp
)

#| Headers
set( HDRS_BS
	./server.h
)

#| Library
set( LIB_BS
	BaulkServer
)

#| Executable
set( EXEC_BS
	baulkServ
)


##| Baulk Client

#| Sources
set( SRCS_BC
        ./client.cpp
)

#| Headers
set( HDRS_BC
	./client.h
)

#| Library
set( LIB_BC
	BaulkClient
)


##| Packet Encoder/Decoder

#| Sources
set( SRCS_PED
	./packet.cpp
)

#| Headers
set( HDRS_PED
	./packet.h
)

#| Library
set( LIB_PED
	PacketEncoderDecoder
)


###| Baulk Common Libraries
include_directories(
	${HEAD_DIR}/src/Common
)

###| Misc Qt4
add_definitions( 
	-Wall 
)
find_package( Qt4 REQUIRED )
set( QT_USE_QTNETWORK 1 )
include( ${QT_USE_FILE} )

##| Packet Encoder/Decoder
if ( BuildBaulkPacket )
	QT4_WRAP_CPP( MOC_SRCS_PED ${HDRS_PED} )
	
	if( WIN32 )
		add_library( ${LIB_PED} STATIC ${SRCS_PED} ${MOC_SRCS_PED} )
	else( WIN32 )
		add_library( ${LIB_PED} SHARED ${SRCS_PED} ${MOC_SRCS_PED} )
	endif( WIN32 )
	
	target_link_libraries( ${LIB_PED} ${QT_LIBRARIES} )

	install( TARGETS
		${LIB_PED}
		DESTINATION lib
	)
endif ( BuildBaulkPacket )

if ( BuildBaulkServServer )
	QT4_WRAP_CPP( MOC_SRCS_BS ${HDRS_BS} )
	add_library( ${LIB_BS} SHARED ${SRCS_BS} ${MOC_SRCS_BS} )
	target_link_libraries( 	${LIB_BS} 
				${QT_LIBRARIES} 
				${LIB_PED}
	)

	install( TARGETS
		${LIB_BS}
		DESTINATION lib
	)
endif ( BuildBaulkServServer )

##| Baulk Server
if ( BuildBaulkServBinary )
	set( EXECUTABLE_OUTPUT_PATH
	        ${HEAD_DIR}/bin
	)

	QT4_WRAP_CPP( MOC_SRCS_BS ${HDRS_BS} )
	add_executable( ${EXEC_BS} main.cpp )
	target_link_libraries( 	${EXEC_BS} 
				${QT_LIBRARIES} 
				${LIB_PED}
				${LIB_BS}
	)
	install( TARGETS
		${EXEC_BS}
		DESTINATION bin
	)
endif ( BuildBaulkServBinary )


##| Baulk Client
if ( BuildBaulkServClient )
	QT4_WRAP_CPP( MOC_SRCS_BC ${HDRS_BC} )
	
	if( WIN32 )
		add_library( ${LIB_BC} STATIC ${SRCS_BC} ${MOC_SRCS_BC} )
	else( WIN32 )
		add_library( ${LIB_BC} SHARED ${SRCS_BC} ${MOC_SRCS_BC} )
	endif( WIN32 )
	
	target_link_libraries( 	${LIB_BC} 
				${QT_LIBRARIES}
				${LIB_PED}
	)

	install( TARGETS
		${LIB_BC}
		DESTINATION lib
	)
endif ( BuildBaulkServClient )

