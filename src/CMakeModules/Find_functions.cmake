function(IGAME_FIND_PATH module header)
   string(TOUPPER ${module} module_uc)

   # Try the user's environment request before anything else.
   find_path(${module_uc}_INCLUDE_DIR ${header}
       HINTS
            $ENV{${module_uc}_DIR}
       PATHS
            $ENV{PATH}
			${IGAME_SOURCE_DIR}/ExternalCode
			/usr/include
			/usr/local/include
   )
endfunction(IGAME_FIND_PATH module header)

IF( WIN32 )
	SET(os_dir "win32")
ELSE( WIN32 )
	SET(os_dir "linux")
ENDIF( WIN32 )


#
# OSG_FIND_LIBRARY
#
function(IGAME_FIND_LIBRARY module library)
   string(TOUPPER ${module} module_uc)

   #   find_path(${module_uc}_LIBRARY_PATH
   #       NAMES ${library}
   #       HINTS
   #	   $ENV{PATH}
   #       PATHS
   #	   ${IGAME_SOURCE_DIR}/ExternalCode
   #	   ${IGAME_SOURCE_DIR}/../ExternalLib/${os_dir}
   #	   /usr/lib
   #	   /usr/local/lib
   #   )

   FIND_PATH(${module_uc}_LIBRARY
       NAMES ${library}
       HINTS
	   $ENV{PATH}
       PATHS
	   ${IGAME_SOURCE_DIR}/ExternalCode
	   ${IGAME_SOURCE_DIR}/../ExternalLib/${os_dir}
	   /usr/lib
	   /usr/local/lib
   )

   find_library(${module_uc}_LIBRARY_DEBUG
	   NAMES ${library}d
	   HINTS
	   $ENV{PATH}
	   PATHS
	   ${IGAME_SOURCE_DIR}/ExternalCode
	   ${IGAME_SOURCE_DIR}/../ExternalLib/${os_dir}
	   /usr/lib
	   /usr/local/lib
	   )

   if(NOT ${module_uc}_LIBRARY_DEBUG)
      # They don't have a debug library
      set(${module_uc}_LIBRARY_DEBUG ${${module_uc}_LIBRARY} PARENT_SCOPE)
      set(${module_uc}_LIBRARIES ${${module_uc}_LIBRARY} PARENT_SCOPE)
   else()
      # They really have a FOO_LIBRARY_DEBUG
      set(${module_uc}_LIBRARIES 
          optimized ${${module_uc}_LIBRARY}
          debug ${${module_uc}_LIBRARY_DEBUG}
          PARENT_SCOPE
      )
   endif()
endfunction(IGAME_FIND_LIBRARY module library)

#
# OSG_MARK_AS_ADVANCED
# Just a convenience function for calling MARK_AS_ADVANCED
#
function(IGAME_MARK_AS_ADVANCED _module)
   string(TOUPPER ${_module} _module_UC)
   mark_as_advanced(${_module_UC}_INCLUDE_DIR)
   mark_as_advanced(${_module_UC}_LIBRARY)
   mark_as_advanced(${_module_UC}_LIBRARY_DEBUG)
endfunction()
