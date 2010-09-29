IF( WIN32 )
	FILE( GLOB PRO_EXT_LIB *.dll )
	add_subdirectory (win32)
ELSE( WIN32 )
	FILE( GLOB PRO_EXT_LIB *.so )
	add_subdirectory (linux)
ENDIF( WIN32 )

INSTALL(FILES ${PRO_EXT_LIB}
    DESTINATION ./bin)
