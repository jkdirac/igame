// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/model/CDotOutput.h,v $
//   $Revision: 1.2 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2009/02/18 20:54:04 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CDotOutput
#define COPASI_CDotOutput

#include <iostream>
#include <map>
#include <set>

class CCopasiObject;
class CModel;
class Refresh;

class CDotOutput
  {

  public:

    CDotOutput();

    void writeDependencies(std::ostream & os, const CModel* pModel, const CCopasiObject * rootNode = NULL);

    void setSkipDependenciesOnCompartments(bool b) {mSkipCompartments = b;};
    void setOnlyAlgebraicDependencies(bool b) {mOnlyAlgebraicDependencies = b;};
    void simpleCall(const CModel* pModel);

  protected:

    class ObjectData
      {
      public:
        bool mInUpToDateList;
        int mSimulatedRefreshesIndex;
        int mNonSimulatedRefreshesIndex;
        int mConstantRefreshesIndex;

        ObjectData()
            : mInUpToDateList(false),
            mSimulatedRefreshesIndex(-1),
            mNonSimulatedRefreshesIndex(-1),
            mConstantRefreshesIndex(-1)
        {};
      };

    void writeDotRecursively(const CCopasiObject * obj, std::ostream & os);

    void writeObjectNode(std::ostream & os, const CCopasiObject * ptr, const ObjectData & od) const;

    void writeEdge(std::ostream & os, const CCopasiObject * ptr1, const CCopasiObject * ptr2, bool indirect = false);

    void updateObjectNodesFromModel(const CModel* model);

    ObjectData * getObjectDataFromRefresh(const Refresh* ref);

    void findObjectsWithUpdateMethod(const CCopasiObject * obj, std::set<const CCopasiObject*> & objectSet, unsigned int recursion = 0) const;

    // member variables

    bool mSkipCompartments;
    bool mOnlyAlgebraicDependencies;

    std::map <const CCopasiObject*, ObjectData> mObjects;
  };

#endif
