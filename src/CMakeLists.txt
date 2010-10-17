PROJECT(IGAME)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_DEBUG")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --export-all-symbols")
cmake_minimum_required(VERSION 2.6)

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
 ${IGAME_BINARY_DIR}/bin/libs/
 CACHE PATH "Single output directory for building all cpp libraries."
)
SET(C_LIBRARY_OUTPUT_PATH
 ${IGAME_BINARY_DIR}/bin/libs/
 CACHE PATH "Single output directory for building all c libraries."
)

SET(CMAKE_INSTALL_PREFIX
 ${IGAME_SOURCE_DIR}/Build/
 CACHE INTERNAL "Single output directory for building all c libraries."
)

#QT4
FIND_PACKAGE( Qt4 )
SET( QT_USE_QTCORE TRUE )
SET( QT_USE_QTGUI TRUE )
SET( QT_USE_QTXML TRUE )
SET( QT_USE_QTOPENGL TRUE )
SET( QT_USE_QTSVG TRUE )
SET( QT_USE_QT3SUPPORT FALSE )
#SET( QT_USE_QTSVG TRUE )
INCLUDE( ${QT_USE_FILE} )

#build
LINK_DIRECTORIES(
	${CPP_LIBRARY_OUTPUT_PATH}
	${C_LIBRARY_OUTPUT_PATH}
	${IGAME_BINARY_DIR}
	${EXECUTABLE_OUTPUT_PATH}
	${EXTERNAL_LIB_OUTPUT_PATH}
	)

INCLUDE_DIRECTORIES( BEFORE
	${CPP_LIBRARY_OUTPUT_PATH}
	${C_LIBRARY_OUTPUT_PATH}
	${IGAME_BINARY_DIR}
	${QT_INCLUDES}
	${IGAME_SOURCE_DIR}/
	${IGAME_SOURCE_DIR}/utility
	${IGAME_SOURCE_DIR}/ExternalCode/qwt/include
	${IGAME_SOURCE_DIR}/ExternalCode/bdbxml
	${IGAME_SOURCE_DIR}/ExternalCode/bdbxml/include/
	${IGAME_SOURCE_DIR}/ExternalCode/bdbxml/include/dbxml
	${IGAME_SOURCE_DIR}/BdInterface
	${IGAME_SOURCE_DIR}/QwtPlot
	${IGAME_SOURCE_DIR}/core
	${IGAME_SOURCE_DIR}/ExternalCode/SBML_odeSolver-1.6.0/src
	${IGAME_SOURCE_DIR}/ExternalCode/SBML_odeSolver-1.6.0/src/sbmlsolver
	${IGAME_SOURCE_DIR}/ExternalCode/sundials-2.1.1/include
	${IGAME_SOURCE_DIR}/ExternalCode/
	${IGAME_SOURCE_DIR}/ExternalCode/sbml/
	${IGAME_SOURCE_DIR}/ExternalCode/sbml/xml
	)

add_subdirectory (ExternalCode)
add_subdirectory (BdInterface)
add_subdirectory (utility)
add_subdirectory (QwtPlot)
add_subdirectory (core)
#add_subdirectory (tools)
#add_subdirectory (ExternalLib)
#add_subdirectory (SimTool)

