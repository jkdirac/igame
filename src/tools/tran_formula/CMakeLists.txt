SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

#source file
FILE( GLOB PRO_CORE_CPP_SRC *.cpp )

ADD_EXECUTABLE( tran_fromula
	${PRO_CORE_CPP_SRC}
	)

TARGET_LINK_LIBRARIES( tran_fromula
	xml2
	sbml
	)

