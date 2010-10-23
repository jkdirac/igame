include(Find_functions)

IGAME_FIND_PATH (dbxml db.h)
IGAME_FIND_LIBRARY(dbxml libdb-4.so libdb-4.8.so libdb_cxx-4.so libdb-2.5.so libxerces-c.so libxqilla.so)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(dbxml DEFAULT_MSG DBXML_LIBRARY DBXML_INCLUDE_DIR)
