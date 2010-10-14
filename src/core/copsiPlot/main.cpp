// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/CopasiUI/main.cpp,v $
//   $Revision: 1.41.2.1 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/05/26 15:57:40 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <stdexcept>

#include <qapplication.h>

#define COPASI_MAIN

#include "copasi.h"
#include "copasilicense.h"
#include "copasiversion.h"

#include "UI/copasiui3window.h"
#include "UI/objectdebug.h"
#include "UI/DataModelGUI.h"
#include "UI/CQMessageBox.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h"
#include "commandline/COptionParser.h"
#include "commandline/COptions.h"

#ifdef COPASI_SBW_INTEGRATION
// SBW includes
#include "SBW/SBW.h"
#include <sstream>
#endif // COPASI_SBW_INTEGRATION

#ifdef Darwin
# include <QDir>
# include "UI/qtUtilities.h"
#endif // Darwin

#include "string.h"
#include "StrCacuException.h"

int copsi_main(int argc, char **argv)
{
  QApplication a(argc, argv);

  // Parse the commandline options
  try
    {
      // Create the root container.
      CCopasiRootContainer::init(argc, argv, true);
    }
  catch (copasi::option_error & msg)
    {
      CQMessageBox::critical(NULL, "Initialization Error",
                             msg.what(),
                             QMessageBox::Ok , QMessageBox::Ok);

      return 1;
    }

#ifdef Darwin
  std::string PluginDir;

  COptions::getValue("CopasiDir", PluginDir);
  PluginDir += "/Contents/plugins";

  QApplication::setLibraryPaths(QStringList(FROM_UTF8(PluginDir)));
#endif // Darwin

  // Create the global data model.
  CCopasiRootContainer::addDatamodel();

  // Create the main application window.
  CopasiUI3Window *pWindow = CopasiUI3Window::create();

#ifdef COPASI_SBW_INTEGRATION

  if (COptions::compareValue("SBWRegister", true))
    goto finish;

#endif // COPASI_SBW_INTEGRATION

  if (pWindow != NULL)
    {
      a.setMainWidget(pWindow);
      pWindow->getDataModel()->setQApp(&a);
      a.exec();
    }

finish:

  try // To suppress any access violations during destruction works only under Windows
    {
      CCopasiRootContainer::destroy();
    }
  catch (...)
    {}

  return 0;
}

#ifdef BUILD_EXE
int main(int argc, char **argv)
{
	char *file_name = "network.xml";
	int opt_num = 3;
	char **options = new char*[opt_num];

//    options[0] ;
	options[1] = new char[3];
	strcpy(options[1], "-i"); options[1][2] = 0;	

	options[2] = new char[strlen(file_name)+1];
	memset(options[2], 0, strlen(file_name)+1);
	strcpy(options[2], file_name);
	copsi_main(opt_num, options);
}
#endif

int copsi_entry(char *file_name_1)
{
	char* file_name = "network.xml";
	int opt_num = 3;
	char **options = new char*[opt_num];

#ifndef BUILD_EXE
	if (file_name == NULL)
	{
		throw StrCacuException("copsi_entry NULL input pointer");
	}
#endif


//    options[0] ;
	options[1] = new char[3];
	strcpy(options[1], "-i"); options[1][2] = 0;	

	options[2] = new char[strlen(file_name)+1];
	memset(options[2], 0, strlen(file_name)+1);
	strcpy(options[2], file_name);
	copsi_main(opt_num, options);

	for (int i=1; i<3; i++)
	{
		if (options[i] != NULL)
			delete options[i];
	}

	if (options != NULL)
	{
		delete []options;
	}

	return 0;
}
