// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/tss/CODEExporterC.h,v $
//   $Revision: 1.5 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2008/03/12 01:34:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CODEExpoterC_H__
#define CODEExpoterC_H__

#include "CODEExporter.h"

class CODEExporterC: public CODEExporter
  {
  protected:

  public:

    /**
     ** Constructor for the exporter.
     */
    CODEExporterC();

    virtual bool preprocess(const CModel* copasiModel);

    virtual bool exportTitleData(const CModel* copasiModel, std::ofstream & outFile);

    virtual void setReservedNames();

    virtual std::string translateTimeVariableName();

    std::string setExportName(const CModelEntity::Status & status, unsigned C_INT32 n[], unsigned C_INT32 dependent);

    std::string setConcentrationName(const CModelEntity::Status & status, unsigned C_INT32 n[], unsigned C_INT32 dependent);

    std::string setODEName(const std::string & objName);

    void setExportNameOfFunction(const CEvaluationNode* pNode, std::set<std::string> & tmpset);

    virtual std::string translateObjectName(const std::string & realName);

    std::string testName(const std::string & name);

    virtual bool exportSingleObject(std::ostringstream & which, std::string & name, std::string & expression, std::string & comments);

    virtual bool exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments);

    virtual bool exportSingleCompartment(const CCompartment* comp, std::string & expression, std::string & comments);

    virtual bool exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments);

    virtual bool exportSingleModelEntity(const CModelEntity* tmp, std::string & expression, std::string & comments);

    virtual bool exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments);

    virtual bool exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments);

    bool exportSingleFunction(const CFunction *func, std::set<std::string>& isExported);

    void findFunctionsCalls(const CEvaluationNode* pNode, std::set<std::string>& isExported);

    virtual bool exportKineticFunctionGroup (const CModel* copasiModel);

    virtual std::string KineticFunction2ODEmember(const CReaction *reac);

    virtual std::string exportTitleString(const unsigned C_INT32 tmp);

    virtual std::string exportClosingString(const unsigned C_INT32 tmp);

    virtual bool exportKineticFunction (CReaction* reac);

    virtual std::string getDisplayExpressionString(CExpression * tmp);

    std::map< std::string, unsigned C_INT32 > Frequancy;
    std::set<std::string> NameSet;
  };
#endif
