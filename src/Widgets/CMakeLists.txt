###| CMAKE Baulk (Widget-Level) Build |###

#| Project
project( BaulkWIDGETLEVEL )
cmake_minimum_required( VERSION 2.6 )

if ( UNIX )
subdirs(
	BaulkTerm
)
endif ( UNIX )

