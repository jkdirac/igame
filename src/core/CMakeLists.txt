SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

INCLUDE_DIRECTORIES( AFTER
	${IGAME_SOURCE_DIR}/core/strcacu
	${IGAME_SOURCE_DIR}/core/
	)

if( NOT WIN32 )
add_subdirectory (copsiPlot)
endif( NOT WIN32 )

add_subdirectory (strcacu)

#source file
FILE( GLOB PRO_CORE_HDRS *.h )
FILE( GLOB PRO_CORE_SRC *.cpp )
FILE( GLOB PRO_INT_HDRS strcacu/*.h)
FILE( GLOB PRO_PLOT_TEST_SRC plotTest/*.cpp )
FILE( GLOB PRO_PLOT_TEST_H plotTest/*.h)
FILE( GLOB PRO_MAIN_CPP main/main.cpp)

ADD_LIBRARY( core
	SHARED
	${PRO_CORE_HDRS}
	${PRO_CORE_SRC}
	${PRO_INT_HDRS}
	${COPSI_INTER_CPP}
	${COPSI_INTER_H}
	)

TARGET_LINK_LIBRARIES( core
  ${QT_LIBRARIES}
  qwt5
  dbxml
  sbml-3.4.1
  bdinterface
  utility
  str_cacu
  )

#ADD_EXECUTABLE( helloplot
#	${PRO_PLOT_TEST_SRC}
#	${PRO_PLOT_TEST_H}
#	)
#
#TARGET_LINK_LIBRARIES( helloplot
#  ${QT_LIBRARIES}
#  qwt5
#  plot
#  sbml-4.0.1
#  sbml_solver
#  utility
#  )

#ADD_EXECUTABLE( igame
#	${PRO_MAIN_CPP}
#	)
#
#TARGET_LINK_LIBRARIES( igame
#	core
#	copsi_wrapper 
#	)
#
#INSTALL_PROJECT( igame )
INSTALL_PROJECT( core )
