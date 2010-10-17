# Copyright (C) 2009 by Wang Rui <wangray84 at gmail dot com>
# You Dont Know OSG: Chapter 1

# Macro for set include directories for projects
MACRO( INCLUDE_FOR_PROJECT PROJNAME )
    FOREACH( varname ${ARGN} )
        IF( ${varname}_INCLUDE_DIR )
            INCLUDE_DIRECTORIES(BEFORE "${${varname}_INCLUDE_DIR}" )
        ELSE( ${varname}_INCLUDE_DIR )
            INCLUDE_DIRECTORIES(BEFORE "${varname}" )
        ENDIF( ${varname}_INCLUDE_DIR )
    ENDFOREACH( varname )
ENDMACRO( INCLUDE_FOR_PROJECT PROJNAME )

# Macro for linking libraries to projects
MACRO( LINK_PROJECT PROJNAME )
    FOREACH( varname ${ARGN} )
        IF( ${varname}_LIBRARY )
		    IF( ${varname}_LIBRARY_DEBUG )
                TARGET_LINK_LIBRARIES( ${PROJNAME}
                    debug "${${varname}_LIBRARY_DEBUG}"
                    optimized "${${varname}_LIBRARY}"
                )
            ELSE( ${varname}_LIBRARY_DEBUG )
                TARGET_LINK_LIBRARIES( ${PROJNAME} "${${varname}_LIBRARY}" )
            ENDIF( ${varname}_LIBRARY_DEBUG )
        ELSE( ${varname}_LIBRARY )
            TARGET_LINK_LIBRARIES( ${PROJNAME} "${varname}" )
        ENDIF( ${varname}_LIBRARY )
    ENDFOREACH( varname )
ENDMACRO( LINK_PROJECT PROJNAME )

# Macro for installing projects binaries and files
MACRO( INSTALL_PROJECT PROJNAME )
    SET( INSTALL_INCDIR igame/include )
    SET( INSTALL_BINDIR igame/bin )
    IF( WIN32 )
        SET( INSTALL_LIBDIR igame/bin )
        SET( INSTALL_ARCHIVEDIR igame/lib )
    ELSE( WIN32 )
        SET( INSTALL_LIBDIR igame/lib )
        SET( INSTALL_ARCHIVEDIR igame/lib )
    ENDIF( WIN32 )
    
    IF( ${PROJNAME}_HEADERS )
        SET( HEADERS_GROUP "Header Files" )
        SOURCE_GROUP( ${HEADERS_GROUP}
            FILES ${${PROJNAME}_HEADERS}
        )
        
	set_property(TARGET *binary* PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
        INSTALL( FILES ${${PROJNAME}_HEADERS}
            DESTINATION ${INSTALL_INCDIR}/${PROJNAME}
        )
    ENDIF( ${PROJNAME}_HEADERS )
    
    INSTALL( TARGETS ${PROJNAME}
        RUNTIME DESTINATION ${INSTALL_BINDIR}
        LIBRARY DESTINATION ${INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVEDIR}
    )
ENDMACRO( INSTALL_PROJECT PROJNAME )
