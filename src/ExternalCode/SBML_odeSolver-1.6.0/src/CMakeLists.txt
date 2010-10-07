SET(LIBRARY_OUTPUT_PATH ${EXTERNAL_LIB_OUTPUT_PATH})

FILE( GLOB SBMLSOLVER_SRC *.cpp *.c )
FILE( GLOB SBMLSOLVER_HEADER *.h )

ADD_LIBRARY( sbml_solver
#  STATIC
  SHARED
  ${SBMLSOLVER_SRC}
  ${SBMLSOLVER_HEADER}
  )

TARGET_LINK_LIBRARIES( sbml_solver
	xml2
	sbml
	sundials_cvodes
	sundials_nvecserial
	sundials_kinsol
	sundials_shared
  )
