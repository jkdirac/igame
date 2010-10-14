/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/report/CRenameHandler.h,v $
   $Revision: 1.3 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2006/04/27 01:31:10 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CRenameHandler
#define COPASI_CRenameHandler

//just the abstract class to handle things that need to be done after every rename

class CRenameHandler
  {
  public:
    virtual ~CRenameHandler(){};

    virtual bool handle(const std::string & oldCN, const std::string & newCN) const = 0;
  };

#endif
