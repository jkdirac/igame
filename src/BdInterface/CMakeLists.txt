SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

#source file
FILE( GLOB PRO_CORE_HDRS *.h )
FILE( GLOB PRO_CORE_SRC *.cpp )
FILE( GLOB PRO_TEST_HDRS test/*.h )
FILE( GLOB PRO_TEST_SRC test/*.cpp )


ADD_EXECUTABLE( test_bdbinterface 
	${PRO_TEST_MOC}
	${PRO_TEST_SRC}
	) 

TARGET_LINK_LIBRARIES( test_bdbinterface
	${QT_LIBRARIES}
	dbxml
	utility
	bdinterface
	)

ADD_LIBRARY( bdinterface
	STATIC
	${PRO_CORE_MOC}
	${PRO_CORE_SRC}
	)

TARGET_LINK_LIBRARIES( bdinterface
	bdinterface
	utility
  )
