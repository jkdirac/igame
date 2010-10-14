// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/layout/CListOfLayouts.h,v $
//   $Revision: 1.7 $
//   $Name: Build-31 $
//   $Author: gauges $
//   $Date: 2009/02/18 20:54:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef LOLAYOUT_H
#define LOLAYOUT_H

#include "utilities/CCopasiVector.h"
#include "CLayout.h"

class ListOf;

/**
 * this class stores a list of layouts. It should also keep the maps
 * that translate from sbml IDs to copas keys
 */
class CListOfLayouts : public CCopasiVector<CLayout>
  {
  private:
    std::string mKey;

  public:
    CListOfLayouts(const std::string & name = "ListOfLayouts",
                   const CCopasiContainer* pParent = NULL);

    ~CListOfLayouts();

    const std::string& getKey();

    /**
     * Add a layout to the list.
     * At the moment the map is just ignored. Later it should be stored somewhere
     */
    void addLayout(CLayout * layout, const std::map<std::string, std::string> & m);

    /**
     * This method writes the information of the copasi layout object into the
     * corresponding sbml object.
     * copasimodelmap maps the copasi model objects to libsbml objects.
     * At the moment we don´t assume layout objects are in the copasimodelmap.
     * idSet should contain all sbml IDs that are used in the currently exported
     * model (including the layouts, but not the objects inside the layout).
     */
    void exportToSBML(ListOf * lol, std::map<CCopasiObject*, SBase*> & copasimodelmap,
                      const std::map<std::string, const SBase*>& idMap) const;
  };

#endif
