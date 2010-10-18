include(Find_functions)

IGAME_FIND_PATH (copasi copasi.h)
IGAME_FIND_LIBRARY(copasi libCOPASIUI.a)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(copasi DEFAULT_MSG DBXML_LIBRARY DBXML_INCLUDE_DIR)
