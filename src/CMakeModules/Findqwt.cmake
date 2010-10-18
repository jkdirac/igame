include(Find_functions)

IGAME_FIND_PATH (qwt qwt.h)
IGAME_FIND_LIBRARY(qwt libqwt5.so libqwt.so)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(qwt DEFAULT_MSG QWT_LIBRARY QWT_INCLUDE_DIR)
