// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/report/CArrayElementReference.h,v $
//   $Revision: 1.5 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2009/01/07 19:04:15 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CArrayElementReference
#define COPASI_CArrayElementReference

#include "CCopasiArray.h"
#include "CCopasiObject.h"

#include "CCopasiObjectName.h"

/**
 * Class CArrayElementReference
 *
 * This class is used to make an element of an array accessible as
 * a CCopasiObject. Usually an object from this class will be a child
 * of a CArrayAnnotation and will reference a single element of the
 * array that the CArrayAnnotation points to.
 */
class CArrayElementReference: public CCopasiObject
  {

  private:
    //CCopasiAbstractArray::data_type * mpReference;

    /**
     * this contains the index in string format, e.g. "[2][7]"
     */
    CCopasiObjectName mIndex;

  private:
    /**
     * make the default constructor unaccessible
     */
    CArrayElementReference();

    /**
     * make the copy constructor unaccessible
     */
    CArrayElementReference(const CArrayElementReference & src);

    /**
     * this method does nothing at the moment!
     */
    void updateMethod(const CCopasiAbstractArray::data_type & value);

  public:
    /**
     * create an element reference with a given index. The index
     * is passed as a string, e.g. "[3][2]"
     * The object name will be the index string, the type is "ElementReference"
     * pParent may not be NULL.
     */
    CArrayElementReference(const std::string & index,
                           const CCopasiContainer * pParent);

    virtual ~CArrayElementReference() {}

    /**
     * returns a pointer to the numerical values of the array element
     * this will be a *C_FLOAT64 for this class.
     */
    virtual void * getValuePointer() const;

    virtual const CCopasiObject * getValueObject() const {return this;}

    /**
     *
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * generate a display name.
     */
    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    /**
     *
     */
    virtual CCopasiObjectName getCN() const;
  };

#endif
