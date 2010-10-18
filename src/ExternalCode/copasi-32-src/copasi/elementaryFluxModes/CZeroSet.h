// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/elementaryFluxModes/CZeroSet.h,v $
//   $Revision: 1.9 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/01/29 21:59:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CZeroSet
#define COPASI_CZeroSet

#include <limits.h> // needed for CHAR_BIT, <limits.h> is not the same as <limits>

#include <vector>

#include "copasi/utilities/CVector.h"

class CStepMatrixColumn;

class CZeroSet
{
public:
  class CIndex
  {
    friend class CZeroSet;

    // Operations
  public:
    CIndex(const size_t & index = 0);

    CIndex(const CIndex & src);

    ~CIndex();

    CIndex & operator ++ ();

    CIndex & operator = (const CIndex & rhs);

    CIndex & operator = (const size_t & index);

    bool operator < (const CIndex & rhs) const;

    // Attributes
  private:
    size_t mIndex;
    size_t mBit;
    size_t mNotBit;
  };

  friend std::ostream & operator << (std::ostream &, const CZeroSet &);

  CZeroSet(const size_t & index = 0);

  CZeroSet(const CZeroSet & src);

  ~CZeroSet();

  inline void setBit(const CIndex & index)
  {
    mBitSet[index.mIndex] |= index.mBit;
    mNumberSetBits++;
  }

  inline void unsetBit(const CIndex & index)
  {
    mBitSet[index.mIndex] &= index.mNotBit;
    mNumberSetBits--;
  }

  inline bool isSet(const CIndex & index) const
  {
    return (mBitSet[index.mIndex] & index.mBit) > 0;
  }

  inline const size_t & getNumberOfSetBits() const
  {
    return mNumberSetBits;
  }

  inline size_t getNumberOfUnsetBits() const
  {
    return mBitSet.size() * CHAR_BIT * sizeof(unsigned C_INT32) - mIgnoredBits - mNumberSetBits;
  }

  inline size_t getNumberOfBits() const
  {
    return mBitSet.size() * CHAR_BIT * sizeof(unsigned C_INT32) - mIgnoredBits;
  }

  inline CZeroSet & operator |= (const CZeroSet & rhs)
  {
    unsigned C_INT32 * pIt = mBitSet.array();
    unsigned C_INT32 * pEnd = pIt + mBitSet.size();
    const unsigned C_INT32 * pRhs = rhs.mBitSet.array();
    mNumberSetBits = 0;

    for (; pIt != pEnd; ++pIt, ++pRhs)
      {
        *pIt |= *pRhs;
        mNumberSetBits += countSetBits(*pIt);
      }

    mNumberSetBits -= mIgnoredBits;

    return *this;
  }

  inline CZeroSet & operator &= (const CZeroSet & rhs)
  {
    unsigned C_INT32 * pIt = mBitSet.array();
    unsigned C_INT32 * pEnd = pIt + mBitSet.size();
    const unsigned C_INT32 * pRhs = rhs.mBitSet.array();
    mNumberSetBits = 0;

    for (; pIt != pEnd; ++pIt, ++pRhs)
      {
        *pIt &= *pRhs;
        mNumberSetBits += countSetBits(*pIt);
      }

    mNumberSetBits -= mIgnoredBits;

    return *this;
  }

  static inline
  CZeroSet intersection(const CZeroSet & set1, const CZeroSet & set2)
  {
    CZeroSet Intersection(set1);
    return Intersection &= set2;
  }

  // Superset
  inline bool operator >= (const CZeroSet & rhs) const
  {
    const unsigned C_INT32 * pIt = mBitSet.array();
    const unsigned C_INT32 * pEnd = pIt + mBitSet.size();
    const unsigned C_INT32 * pRhs = rhs.mBitSet.array();

    for (; pIt != pEnd; ++pIt, ++pRhs)
      {
        if (*pIt != (*pIt | *pRhs))
          return false;
      }

    return true;
  }

  inline bool operator == (const CZeroSet & rhs) const
  {
    if (mNumberSetBits != rhs.mNumberSetBits)
      return false;

    return memcmp(mBitSet.array(), rhs.mBitSet.array(),
                  mBitSet.size() * sizeof(unsigned C_INT32)) == 0;
  }

  bool isExtremeRay(const std::vector< CStepMatrixColumn * > & columns) const;

  // Attributes
private:
  CVector<unsigned C_INT32> mBitSet;

  size_t mIgnoredBits;

  size_t mNumberSetBits;

  inline size_t countSetBits(unsigned C_INT32 bits)
  {
    size_t numberOfBits = 0;

    for (size_t i = 0; i < CHAR_BIT * sizeof(unsigned C_INT32); ++i)
      {
        if ((bits >> i) & 1)
          {
            numberOfBits++;
          }
      }

    return numberOfBits;
  }
};

#endif // COPASI_CZeroSet
