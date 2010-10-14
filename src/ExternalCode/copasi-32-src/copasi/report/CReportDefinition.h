// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/report/CReportDefinition.h,v $
//   $Revision: 1.40 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2007/02/23 18:51:39 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 *
 * Created: Tue Aug 11 2003
 *      by: Liang Xu
 *
 *  Created for Copasi by Liang Xu
 ****************************************************************************/

#ifndef COPASI_CReport_Definition
#define COPASI_CReport_Definition

#include <string>
#include <vector>

#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiStaticString.h"
#include "utilities/CCopasiTask.h"

class CReportDefinition;
class CComment;
class CHeaderFooter;
class CReportBody;
class CReportObject;
class CReport;
class CReportTable;

class CReportDefinition : public CCopasiObject
  {
    // Operations
  private:
    std::string mKey;
    std::string mComment;
    CCopasiTask::Type mTaskType;

    std::vector<CRegisteredObjectName> mHeaderVector;
    std::vector<CRegisteredObjectName> mBodyVector;
    std::vector<CRegisteredObjectName> mFooterVector;
    std::vector<CRegisteredObjectName> mTableVector;

    CCopasiReportSeparator mSeparator;
    bool mTable;
    bool mbTitle;
    unsigned C_INT32 mPrecision;

  public:
    /**
     *  Default constructor.
     */
    CReportDefinition(const std::string & name = "NoName",
                      const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor.
     */
    CReportDefinition(const CReportDefinition & src,
                      const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CReportDefinition();

    /**
     *cleanup
     */
    void cleanup();

    /**
     * Convert the table list into a header and body list.
     * @param const std::vector< CCopasiContainer * > & listOfContainer
     * (default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    bool preCompileTable(const std::vector< CCopasiContainer * > & listOfContainer = CCopasiContainer::EmptyList);

    /**
     *Returns the comments in the report tag
     */
    const std::string & getComment() const
      {
        return mComment;
      }

    /**
     *sets the comments in the report tag
     */
    void setComment(const std::string & comment)
    {
      mComment = comment;
    }

    /**
     *gets the body in the report tag
     */
    std::vector<CRegisteredObjectName>* getBodyAddr();

    /**
     *gets the header in the report tag
     */
    std::vector<CRegisteredObjectName>* getHeaderAddr();

    /**
     *gets the footer in the report tag
     */
    std::vector<CRegisteredObjectName>* getFooterAddr();

    /**
     *gets the footer in the report tag
     */
    std::vector<CRegisteredObjectName>* getTableAddr();

    /**
     *
     */
    bool setTaskType(const CCopasiTask::Type & taskType);

    /**
     *
     */
    const CCopasiTask::Type & getTaskType() const;

    /**
     *
     */
    void setSeparator(const CCopasiReportSeparator & Separator);

    /**
     *
     */
    const CCopasiReportSeparator & getSeparator() const;

    /**
     *
     */
    bool getTitle() const;

    /**
     *
     */
    void setTitle(bool title);

    /**
     *
     */
    bool isTable() const;

    /**
     *
     */
    void setIsTable(bool table);

    /**
     * Set the precsion for floating point numbers;
     * @param const unsigned C_INT32 & precision
     */
    void setPrecision(const unsigned C_INT32 & precision);

    /**
     * Retrieve the precsion for floating point numbers;
     * @return const unsigned C_INT32 & precision
     */
    const unsigned C_INT32 & getPrecision() const;

    /**
     *
     */
    virtual const std::string & getKey() const;

  private:
    /**
     * This adds header and body entries for one table element
     * (including separator if necessary)
     * @param const CCopasiObject * pObject
     */
    void addTableElement(const CCopasiObject * pObject);
  };

#endif
