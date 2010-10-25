PROJECT(IGAME)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_DEBUG")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --export-all-symbols")
cmake_minimum_required(VERSION 2.6)

set(CMAKE-INSTALL-RPATH-USE-LINK-PATH TRUE)

#load MACROS
INCLUDE( CMakeModules/CustomModules.cmake )

#---------------------------------------------------------------------------
# Define EXECUTABLE_OUTPUT_PATH and LIBRARY_OUTPUT_PATH
#---------------------------------------------------------------------------
SET(CMAKE_BUILD_TYPE "Debug"
	CACHE INTERNAL "debug")

IF( WIN32 )
SET(EXTERNAL_LIB_OUTPUT_PATH
	${IGAME_SOURCE_DIR}/../ExternalLib/win32
	CACHE PATH "Single output directory for building all executables.")
ELSE( WIN32 )
SET(EXTERNAL_LIB_OUTPUT_PATH
	${IGAME_SOURCE_DIR}/../ExternalLib/linux
	CACHE PATH "Single output directory for building all executables.")
ENDIF( WIN32 )

SET(EXECUTABLE_OUTPUT_PATH
 ${IGAME_BINARY_DIR}/bin
 CACHE PATH "Single output directory for building all executables.")
SET(CPP_LIBRARY_OUTPUT_PATH
 ${IGAME_BINARY_DIR}/bin/
 CACHE PATH "Single output directory for building all cpp libraries."
)
SET(C_LIBRARY_OUTPUT_PATH
 ${IGAME_BINARY_DIR}/bin/
 CACHE PATH "Single output directory for building all c libraries."
)

SET( CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/CMakeModules/;${CMAKE_MODULE_PATH}" )

#FIND PACKAGES
FIND_PACKAGE( sbml )
FIND_PACKAGE( dbxml )
FIND_PACKAGE( copasi )
FIND_PACKAGE( qwt )
#FIND_PACKAGE( qwtplot3d )
#FIND_PACKAGE( odesolver )
#FIND_PACKAGE( sundials )

#INSTALL

#QT4
FIND_PACKAGE( Qt4 )
SET( QT_USE_QTCORE TRUE )
SET( QT_USE_QTGUI TRUE )
SET( QT_USE_QTXML TRUE )
SET( QT_USE_QTOPENGL TRUE )
SET( QT_USE_QT3SUPPORT TRUE)
SET( QT_USE_QTSVG TRUE )
#SET( QT_USE_QTSVG TRUE )
INCLUDE( ${QT_USE_FILE} )

#build
LINK_DIRECTORIES(
	${CPP_LIBRARY_OUTPUT_PATH}
	${C_LIBRARY_OUTPUT_PATH}
	${IGAME_BINARY_DIR}
	${EXECUTABLE_OUTPUT_PATH}
	)
#${EXTERNAL_LIB_OUTPUT_PATH}

IF (SBML_LIBRARY)
	LINK_DIRECTORIES(
		${SBML_LIBRARY})
ENDIF (SBML_LIBRARY)

IF (DBXML_LIBRARY)
	LINK_DIRECTORIES(
		${DBXML_LIBRARY} )
ENDIF (DBXML_LIBRARY)

IF (COPASI_LIBRARY)
	LINK_DIRECTORIES(
		${COPASI_LIBRARY} )
ENDIF (COPASI_LIBRARY)

IF (NOT SBML_INCLUDE_DIR)
	INCLUDE_DIRECTORIES( BEFORE
		${IGAME_SOURCE_DIR}/ExternalCode/sbml-3.4.1/
		${IGAME_SOURCE_DIR}/ExternalCode/sbml-3.4.1/sbml
		)		
ELSE(NOT SBML_INCLUDE_DIR)
	INCLUDE_DIRECTORIES( BEFORE
		${SBML_INCLUDE_DIR} )
ENDIF(NOT SBML_INCLUDE_DIR)

IF (NOT QWT_INCLUDE_DIR)
	INCLUDE_DIRECTORIES( BEFORE
		${IGAME_SOURCE_DIR}/ExternalCode/qwt/include
		)		
ELSE(NOT QWT_INCLUDE_DIR)
	INCLUDE_DIRECTORIES( BEFORE
		${QWT_INCLUDE_DIR} )
ENDIF(NOT QWT_INCLUDE_DIR)

IF (NOT DBXML_INCLUDE_DIR)
	INCLUDE_DIRECTORIES( BEFORE
		${IGAME_SOURCE_DIR}/ExternalCode/bdbxml/include/
		${IGAME_SOURCE_DIR}/ExternalCode/bdbxml/include/dbxml
		)		
ELSE(NOT DBXML_INCLUDE_DIR)
	INCLUDE_DIRECTORIES( BEFORE
		${DBXML_INCLUDE_DIR} )
ENDIF(NOT DBXML_INCLUDE_DIR)

IF (NOT COPASI_INCLUDE_DIR)
	INCLUDE_DIRECTORIES( BEFORE
		${IGAME_SOURCE_DIR}/ExternalCode/copasi-32-src/copasi
		${IGAME_SOURCE_DIR}/ExternalCode/copasi-32-src
		)		
ELSE(NOT COPASI_INCLUDE_DIR)
	INCLUDE_DIRECTORIES( BEFORE
		${COPASI_INCLUDE_DIR} )
ENDIF(NOT COPASI_INCLUDE_DIR)
	

INCLUDE_DIRECTORIES( BEFORE
	${CPP_LIBRARY_OUTPUT_PATH}
	${C_LIBRARY_OUTPUT_PATH}
	${IGAME_SOURCE_DIR}/igameUi
	${IGAME_SOURCE_DIR}/igameUiMort
	${QT_INCLUDES}
	${IGAME_SOURCE_DIR}/
	${IGAME_SOURCE_DIR}/utility
	${IGAME_SOURCE_DIR}/BdInterface
	${IGAME_SOURCE_DIR}/QwtPlot
	${IGAME_SOURCE_DIR}/core
	${IGAME_SOURCE_DIR}/core/copsiPlot
	)
#	${IGAME_SOURCE_DIR}/ExternalCode/qwt/include
#	${IGAME_SOURCE_DIR}/ExternalCode/qwtplot3d/include
#	${IGAME_SOURCE_DIR}/ExternalCode/bdbxml
#	${IGAME_SOURCE_DIR}/ExternalCode/SBML_odeSolver-1.6.0/src
#	${IGAME_SOURCE_DIR}/ExternalCode/SBML_odeSolver-1.6.0/src/sbmlsolver
#	${IGAME_SOURCE_DIR}/ExternalCode/sundials-2.1.1/include
#	${IGAME_SOURCE_DIR}/ExternalCode/

#add_subdirectory (ExternalCode)
add_subdirectory (utility)
add_subdirectory (BdInterface)
#add_subdirectory (QwtPlot)
#add_subdirectory (core)
#add_subdirectory (igameUi)
add_subdirectory (igameUiMort)
#add_subdirectory (ExternalLib)


ADD_CUSTOM_TARGET(uninstall
	COMMAND rm -rvf ${CMAKE_INSTALL_PREFIX}/igame
	)
