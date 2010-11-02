SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

#source file
FILE( GLOB PRO_CORE_HDRS *.h MosQt/*.h demoUi/*.h iGameUi/*.h *.hxx MosQt)
FILE( GLOB PRO_CORE_CPP_SRC *.cpp )
FILE( GLOB PRO_CORE_C_SRC *.c )
FILE( GLOB PRO_DSG_FILE *.ui )
FILE( GLOB PRO_RESOURCE_SRC *.qrc )

FILE( GLOB PRO_UI_CPP_SRC iGameUi/*.cpp )

FILE( GLOB PRO_DEMO_CPP_SRC demoUi/*.cpp )

FILE( GLOB PRO_MAIN_CPP_SRC igameUiMain/*.cpp )

QT4_WRAP_UI( PRO_QDSG_HDR ${PRO_DSG_FILE})
QT4_WRAP_CPP( PRO_CORE_MOC ${PRO_CORE_HDRS} )
QT4_ADD_RESOURCES( PRO_RESOURCE ${PRO_RESOURCE_SRC} )
#QT4_WRAP_CPP( PRO_MOC_CPP ${PRO_MOC_FILE})

INCLUDE_DIRECTORIES( BEFORE
	${IGAME_BINARY_DIR}/igameUiMort
	)

ADD_LIBRARY( uicore
	SHARED
	${PRO_CORE_MOC}
	${PRO_CORE_CPP_SRC}
	${PRO_CORE_C_SRC}
	${PRO_QDSG_HDR}
	${PRO_RESOURCE}
	)

TARGET_LINK_LIBRARIES( uicore
	uicore
	dbxml
	bdinterface
	core
	utility
	)

ADD_EXECUTABLE( igameUiMort
	${PRO_UI_CPP_SRC}
	)

TARGET_LINK_LIBRARIES( igameUiMort
  ${QT_LIBRARIES}
  uicore
  )
  #copsi_wrapper 

ADD_EXECUTABLE( demoUiXml
	${PRO_DEMO_CPP_SRC}
	)

TARGET_LINK_LIBRARIES( demoUiXml
  ${QT_LIBRARIES}
  uicore
  )
  #copsi_wrapper 

ADD_EXECUTABLE( igameUiMain
	${PRO_MAIN_CPP_SRC}
	)

TARGET_LINK_LIBRARIES( igameUiMain
  ${QT_LIBRARIES}
  uicore
  )


INSTALL_PROJECT(igameUiMain)
INSTALL_PROJECT(uicore)
