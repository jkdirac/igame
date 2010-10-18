/* Begin CVS Header
  $Source: /fs/turing/cvs/copasi_dev/copasi/report/COutputAssistant.h,v $
  $Revision: 1.6 $
  $Name: Build-31 $
  $Author: gauges $
  $Date: 2009/02/18 20:54:48 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COutputAssistant
#define COPASI_COutputAssistant

#include <vector>
#include <string>
#include <map>
#include "copasi.h"

#include "utilities/CCopasiTask.h"

class CCopasiProblem;
class CPlotSpecification;
class CReportDefinition;
class CCopasiObject;
class CCopasiDataModel;

class CDefaultOutputDescription
  {
  public:

    CDefaultOutputDescription()
        : name(""), description(""), isPlot(true), mTaskType(CCopasiTask::steadyState) {}

    //C_INT32 id;
    std::string name;
    std::string description;
    bool isPlot;
    CCopasiTask::Type mTaskType;
  };

class COutputAssistant
  {
  public:

    /**
     *  get a list of indices of output definitions that are
     *  suitable for the problem.
     *  If problem=NULL (default) all indices in the map are returned.
     */
    static
    std::vector<C_INT32> getListOfDefaultOutputDescriptions(const CCopasiProblem * problem = NULL);

    /**
     *  get an index of a default output report that is
     *  recommended  for the given problem.
     *  If no such report exists, -1 is returned
     */
    static
    C_INT32 getDefaultReportIndex(const CCopasiProblem * problem);

    /**
     *  get an index of a default plot that is
     *  recommended  for the given problem.
     *  If no such plot exists, -1 is returned
     */
    static
    C_INT32 getDefaultPlotIndex(const CCopasiProblem * problem);

    /**
     *  get title of output definition with index id.
     */
    static
    const std::string & getItemName(C_INT32 id);

    /**
     *  get complete description of output definition with index id.
     */
    static
    const CDefaultOutputDescription & getItem(C_INT32 id);

    /**
     *  create a plot or report from template with index id.
     *  returns a pointer to the plot or report definition (or NULL)
     *  if activate==true and the ouput is a report the report is set as
     *  the current report for the task (possibly replacing an already set report)
     */
    static
    CCopasiObject* createDefaultOutput(C_INT32 id, CCopasiTask * task, CCopasiDataModel* pDataModel, bool activate = true);

  private:           //************************************

    typedef std::map<C_INT32, CDefaultOutputDescription> Map;

    static
    Map mMap;

    //this method creates the lists of output descriptions
    static
    bool initialize();

    static
    CPlotSpecification* createPlot(const std::string & name,
                                   const CCopasiObject* x,
                                   const std::vector<const CCopasiObject*> & y,
                                   const CCopasiTask::Type & taskType,
                                   CCopasiDataModel* pDataModel);

    static
    CReportDefinition* createTable(const std::string & name,
                                   const std::vector<const CCopasiObject*> & d,
                                   const std::string & comment,
                                   const CCopasiTask::Type & taskType,
                                   CCopasiDataModel* pDataModel);

    static const std::string emptyString;
    static const CDefaultOutputDescription emptyItem;
  };

#endif
