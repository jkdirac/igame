SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

#source file
FILE( GLOB PRO_CORE_HDRS *.h )
FILE( GLOB PRO_CORE_SRC *.cpp )
FILE( GLOB PRO_TEST_SRC *.cpp )

find_package(BISON)
find_package(FLEX)

BISON_TARGET(STRParser cacu.y ${IGAME_BINARY_DIR}/cacuyac.c)
FLEX_TARGET(STRScanner cacu.l  ${IGAME_BINARY_DIR}/caculex.c)
ADD_FLEX_BISON_DEPENDENCY(STRScanner STRParser)

include_directories(${IGAME_BINARY_DIR})

FIND_PACKAGE( BISON )
FIND_PACKAGE( FLEX )

ADD_LIBRARY( str_cacu
	STATIC
	${PRO_CORE_MOC}
	${PRO_CORE_SRC}
	${BISON_STRParser_OUTPUTS}
	${FLEX_STRScanner_OUTPUTS}
	)

ADD_EXECUTABLE( test_strcacu
	${PRO_TEST_SRC}
	)
TARGET_LINK_LIBRARIES( test_strcacu
	str_cacu
	utility
	)
INSTALL_PROJECT( test_strcacu )
