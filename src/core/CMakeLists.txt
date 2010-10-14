SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

add_subdirectory (hellocopsi)

INCLUDE_DIRECTORIES( AFTER
	${IGAME_SOURCE_DIR}/core/strcacu
	${IGAME_SOURCE_DIR}/ExternalCode/sbml-4.0.1/
	${IGAME_SOURCE_DIR}/ExternalCode/sbml-4.0.1/sbml
	)

#source file
FILE( GLOB PRO_CORE_HDRS *.h )
FILE( GLOB PRO_INT_HDRS strcacu/*.h)
FILE( GLOB PRO_CORE_SRC *.cpp )
FILE( GLOB PRO_TEST_SRC strcacu/*.cpp )
FILE( GLOB PRO_PLOT_TEST_SRC plotTest/*.cpp )
FILE( GLOB PRO_PLOT_TEST_H plotTest/*.h)

ADD_EXECUTABLE( test_strcacu
	${PRO_TEST_SRC}
	)
TARGET_LINK_LIBRARIES( test_strcacu
	str_cacu
	)

ADD_EXECUTABLE( igame
	${PRO_CORE_HDRS}
	${PRO_CORE_SRC}
	${PRO_INT_HDRS}
	)

TARGET_LINK_LIBRARIES( igame 
  ${QT_LIBRARIES}
  qwt5
  sbml_solver
  dbxml
  sbml-4.0.1
  bdinterface
  utility
  str_cacu
  )

ADD_EXECUTABLE( helloplot
	${PRO_PLOT_TEST_SRC}
	${PRO_PLOT_TEST_H}
	)

TARGET_LINK_LIBRARIES( helloplot
  ${QT_LIBRARIES}
  qwt5
  plot
  sbml-4.0.1
  sbml_solver
  utility
  )
