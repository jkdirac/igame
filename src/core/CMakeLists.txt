SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

INCLUDE_DIRECTORIES( AFTER
	${IGAME_SOURCE_DIR}/core/strcacu
	)

#source file
FILE( GLOB PRO_CORE_HDRS *.h )
FILE( GLOB PRO_INT_HDRS strcacu/*.h)
FILE( GLOB PRO_CORE_SRC *.cpp )
FILE( GLOB PRO_TEST_SRC strcacu/*.cpp )

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
  sbml
  bdinterface
  utility
  str_cacu
  )
