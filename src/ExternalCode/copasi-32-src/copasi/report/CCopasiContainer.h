/* Begin CVS Header
$Source: /fs/turing/cvs/copasi_dev/copasi/report/CCopasiContainer.h,v $
$Revision: 1.34 $
$Name: Build-31 $
$Author: shoops $
$Date: 2009/02/19 19:51:19 $
End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file CCopasiContainer.h
    \brief Header file of class CCopasiContainer
 */

/**
 * Class CCopasiContainer
 *
 * This class is the is used to group CCopasiObjects logically. It inself is
 * an object. Contained objects are still globally accessible.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CCopasiContainer
#define COPASI_CCopasiContainer

#include <map>
#include <vector>

#include "report/CCopasiObject.h"

class CCopasiContainer: public CCopasiObject
  {
    //Attributes
  public:

    static const std::vector< CCopasiContainer * > EmptyList;

    typedef std::multimap< const std::string, CCopasiObject * > objectMap;

  protected:
    objectMap mObjects;

  private:
    // Operations
    CCopasiContainer();

  public:
    CCopasiContainer(const std::string & name,
                     const CCopasiContainer * pParent = NULL,
                     const std::string & type = "CN",
                     const unsigned C_INT32 & flag = CCopasiObject::Container);

    CCopasiContainer(const CCopasiContainer & src,
                     const CCopasiContainer * pParent = NULL);

    virtual ~CCopasiContainer();

    virtual const CCopasiObject * getObject(const CCopasiObjectName & cn) const;

    virtual const CCopasiObject * getValueObject() const;

    virtual const objectMap & getObjects() const;

    virtual bool add(CCopasiObject * pObject, const bool & adopt = true);

    virtual bool remove(CCopasiObject * pObject);

    /**
     * Retrieve the units of the object.
     * @return std::string units
     */
    virtual std::string getUnits() const;

    /**
     * Retrieve the units of the child object.
     * @return std::string units
     */
    virtual std::string getChildObjectUnits(const CCopasiObject * pObject) const;

  protected:
    void initObjects();

    template <class CType> CCopasiObject * addObjectReference(const std::string & name,
        CType & reference,
        const unsigned C_INT32 & flag = 0)
    {return createReference(name, this, reference, flag);}

    template <class CType> CCopasiObject * addVectorReference(const std::string & name,
        CType & reference,
        const unsigned C_INT32 & flag = 0)
    {return createVectorReference(name, this, reference, flag);}

    template <class CType> CCopasiObject * addMatrixReference(const std::string & name,
        CType & reference,
        const unsigned C_INT32 & flag = 0)
    {return createMatrixReference(name, this, reference, flag);}
  };

#endif // COPASI_CCopasiContainer
