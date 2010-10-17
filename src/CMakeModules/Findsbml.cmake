include(Find_functions)

IGAME_FIND_PATH(sbml sbml/SBMLTypes.h)
IGAME_FIND_LIBRARY(sbml libsbml.so libsbml-3.4.1.so libsbml.a libsbml-3.4.1.a)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(sbml DEFAULT_MSG SBML_LIBRARY SBML_INCLUDE_DIR)
