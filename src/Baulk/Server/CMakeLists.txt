###| CMAKE Baulk Server/Client |###

###| Project
project( BaulkServerClient )
cmake_minimum_required( VERSION 2.6 )


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


###| Misc Qt4
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
set( QT_USE_QTNETWORK 1 )
include( ${QT_USE_FILE} )

###| Library Versioning
set( cat_prog cat )
if( WIN32 )
  if( not UNIX )
    set( cat_prog type )
  endif( not UNIX )
endif( WIN32 )

exec_program( ${cat_prog} 
	ARGS ${PROJECT_SOURCE_DIR}/../../Common/VERSION 
	OUTPUT_VARIABLE VERSION 
)
set( LIBRARY_VERSION
	"${VERSION}"
)


##| Packet Encoder/Decoder
QT4_WRAP_CPP( MOD_SRCS_PED ${HDRS_PED} )
add_library( ${LIB_PED} SHARED ${SRCS_PED} ${MOC_SRCS_PED} )
set_target_properties( ${LIB_PED} PROPERTIES VERSION ${LIBRARY_VERSION} )
target_link_libraries( ${LIB_PED} ${QT_LIBRARIES} )


##| Baulk Server
QT4_WRAP_CPP( MOC_SRCS_BS ${HDRS_BS} )
add_library( ${LIB_BS} SHARED ${SRCS_BS} ${MOC_SRCS_BS} )
set_target_properties( ${LIB_BS} PROPERTIES VERSION ${LIBRARY_VERSION} )
target_link_libraries( ${LIB_BS} ${QT_LIBRARIES} )


##| Library Loader
QT4_WRAP_CPP( MOC_SRCS_BC ${HDRS_BC} )
add_library( ${LIB_BC} SHARED ${SRCS_BC} ${MOC_SRCS_BC} )
set_target_properties( ${LIB_BC} PROPERTIES VERSION ${LIBRARY_VERSION} )
target_link_libraries( ${LIB_BC} ${QT_LIBRARIES} )

