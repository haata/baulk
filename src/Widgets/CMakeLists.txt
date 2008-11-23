###| CMAKE Baulk (Widget-Level) Build |###

#| Project
project( BaulkWIDGETLEVEL )
cmake_minimum_required( VERSION 2.6 )

if ( UNIX )
	subdirs(
		BaulkStatus
		BaulkSwallow
		BaulkTerm
		#WebBaulk
	)
endif ( UNIX )

if ( WIN32 )
	subdirs(
		BaulkStatus
		WebBaulk
	)
endif ( WIN32 )

