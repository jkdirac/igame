// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/utilities/CMatrix.h,v $
//   $Revision: 1.38 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/02/01 15:29:23 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CMatrix
#define COPASI_CMatrix

#include <iostream>
#include <assert.h>
#include <string.h>

#include "copasi.h"

#include "utilities/CVector.h"

template<typename CType> class CMatrix;

template <class CType>
std::ostream &operator<<(std::ostream &os, const CMatrix< CType > & A);

template <class Matrix> class CTransposeView;

template <class Matrix>
std::ostream &operator << (std::ostream &os, const CTransposeView< Matrix > & A);

template <class Matrix> class CLowerTriangularView;

template <class Matrix>
std::ostream &operator<<(std::ostream &os, const CLowerTriangularView< Matrix > & A);

template <class Matrix> class CUpperTriangularView;

template <class Matrix>
std::ostream &operator<<(std::ostream &os, const CUpperTriangularView< Matrix > & A);

template <class Matrix> class CUnitUpperTriangularView;

template <class Matrix>
std::ostream &operator << (std::ostream &os, const CUnitUpperTriangularView< Matrix > & A);

template <class Matrix> class CUnitLowerTriangularView;

template <class Matrix>
std::ostream &operator << (std::ostream &os, const CUnitLowerTriangularView< Matrix > & A);

/**
 * Template class CMatrix < class CType >
 * This template class is a simple matrix class  allowing standard
 * C-style and fortran style access to the elements. It also supplies
 * an ostream operator.
 */
template <class CType>
class CMatrix
{
public:
  typedef CType elementType;

  // Attributes
protected:
  /**
   * Number of rows in the matrix.
   */
  unsigned C_INT32 mRows;

  /**
   * Number of columns in the matrix
   */
  unsigned C_INT32 mCols;

  /**
   * The array storing the matrix elements
   */
  CType * mArray;

  // Operations
public:
  /**
   * Default constructor
   * @param unsigned C_INT32 rows (default = 0)
   * @param unsigned C_INT32 cols (default = 0)
   */
  CMatrix(unsigned C_INT32 rows = 0, unsigned C_INT32 cols = 0) :
      mRows(0),
      mCols(0),
      mArray(NULL)
  {
    resize(rows, cols);
  }

  /**
   * Copy constructor
   * @param const CMatrix <CType> & src
   */
  CMatrix(const CMatrix <CType> & src):
      mRows(0),
      mCols(0),
      mArray(NULL)
  {
    resize(src.mRows, src.mCols);

    if (mRows && mCols)
      memcpy(mArray, src.mArray, mRows * mCols * sizeof(CType));
  }

  /**
   * Destructor.
   */
  virtual ~CMatrix()
  {
    if (mArray)
      delete [] mArray;
  }

  /**
   * The number of elements stored in the matrix.
   * @return unsigned C_INT32 size
   */
  virtual unsigned C_INT32 size() const {return mRows * mCols;}

  /**
   * The number of rows of the matrix.
   * @return unsigned C_INT32 rows
   */
  virtual unsigned C_INT32 numRows() const {return mRows;}

  /**
   * The number of columns of the matrix
   * @return unsigned C_INT32 cols
   */
  virtual unsigned C_INT32 numCols() const {return mCols;}

  /**
   * Resize the matrix. The previous content is lost
   * @param unsigned C_INT32 rows
   * @param unsigned C_INT32 cols
   */
  virtual void resize(unsigned C_INT32 rows, unsigned C_INT32 cols)
  {
    if (rows * cols != mRows * mCols)
      {
        if (mArray)
          {
            delete [] mArray;
            mArray = NULL;
          }

        if (rows && cols)
          {
            try
              {
                mArray = new CType[rows * cols];
              }

            catch (...)
              {
                mArray = NULL;
              }

            if (mArray == NULL)
              {
                mRows = 0;
                mCols = 0;

                CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, rows * cols * sizeof(CType));
              }
          }
      }

    mRows = rows;
    mCols = cols;
  }

  /**
   * Assignement operator
   * @param const CMatrix <CType> & rhs
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator = (const CMatrix <CType> & rhs)
  {
    if (mRows != rhs.mRows || mCols != rhs.mCols)
      resize(rhs.mRows, rhs.mCols);

    memcpy(mArray, rhs.mArray, mRows * mCols * sizeof(CType));

    return *this;
  }

  /**
   * Assignement operator
   * @param const CType & value
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator = (const CType & value)
  {
    unsigned C_INT32 i, imax = mRows * mCols;
    CType * tmp = mArray;

    for (i = 0; i < imax; i++, tmp++) *tmp = value;

    return *this;
  }

#ifdef XXXX
  /**
   * Scalar multiplication operator
   * @param const CType & value
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator *(const CType & value)
  {
    unsigned C_INT32 i, imax = mRows * mCols;
    CType * tmp = mArray;

    for (i = 0; i < imax; i++, tmp++) *tmp *= value;

    return *this;
  }

  /**
   * Scalar division operator
   * @param const CType & value
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator / (const CType & value)
  {return (*this) *(1.0 / value);}

  /**
   * + operator
   * @param const CMatrix <CType> & rhs
   * @return CMatrix <CType> & lhs
   */
  virtual CMatrix <CType> & operator + (const CMatrix <CType> & rhs)
  {
    assert(mRows == rhs.mRows && mCols == rhs.mCols);

    unsigned C_INT32 i, imax = mRows * mCols;
    CType * tmp1 = mArray;
    CType * tmp2 = rhs.mArray;

    for (i = 0; i < imax; i++, tmp1++, tmp2++) *tmp1 += *tmp2;

    return *this;
  }
#endif // XXXX

  /**
   * Retrieve a row of the matrix using c-style indexing
   * @param unsigned C_INT32 row
   * @return CType * row
   */
  virtual inline CType * operator[](unsigned C_INT32 row)
  {return mArray + row * mCols;}

  /**
   * Retrieve a row of the matrix using c-style indexing
   * @param unsigned C_INT32 row
   * @return const CType * row
   */
  virtual inline const CType * operator[](unsigned C_INT32 row) const
  {return mArray + row * mCols;}

  /**
   * Retrieve a matrix element using c-style indexing.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return const elementType & element
   */
  virtual inline elementType & operator()(const unsigned C_INT32 & row,
                                          const unsigned C_INT32 & col)
  {
    assert(row < mRows && col < mCols);
    return *(mArray + row * mCols + col);
  }

  /**
   * Retrieve a matrix element using c-style indexing.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return const elementType & element
   */
  virtual inline const elementType & operator()(const unsigned C_INT32 & row,
      const unsigned C_INT32 & col) const
  {
    assert(row < mRows && col < mCols);
    return *(mArray + row * mCols + col);
  }

  /**
   * Retrieve the array of the matrix elements. This is suitable
   * for interfacing with clapack routines.
   * @return CType * array
   */
  virtual CType * array() {return mArray;}

  /**
   * Retrieve the array of the matrix elements. This is suitable
   * for interfacing with clapack routines.
   * @return const CType * array
   */
  virtual const CType * array() const {return mArray;}

  /**
   * Reorder the rows according to the provided pivots
   * @param const CVector<unsigned C_INT32> & pivot
   * @return bool success
   */
  bool applyPivot(const CVector<unsigned C_INT32> & pivot)
  {
    if (pivot.size() != mRows) return false;

    CVector< bool > Applied(mRows);
    Applied = false;
    CType *pTmp = new CType[mCols];

    unsigned C_INT32 i;
    unsigned C_INT32 to;
    unsigned C_INT32 from;

    for (i = 0; i < mRows; i++)
      if (!Applied[i])
        {
          to = i;
          from = pivot[i];

          if (to != from)
            {
              memcpy(pTmp, mArray + i * mCols, mCols * sizeof(CType));

              while (from != i)
                {
                  memcpy(mArray + to * mCols, mArray + from * mCols, mCols * sizeof(CType));
                  Applied[to] = true;

                  to = from;
                  from = pivot[to];
                }

              memcpy(mArray + to * mCols, pTmp, mCols * sizeof(CType));
            }

          Applied[to] = true;
        }

    pdeletev(pTmp);
    return true;
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CMatrix< CType > & A
   * @return ostream & os
   */
#if defined SWIG
  friend std::ostream &operator <<(std::ostream &os,
                                   const CMatrix< CType > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend std::ostream &operator <<(std::ostream &os,
                                   const CMatrix< CType > & A);
#else
  friend std::ostream &operator << <> (std::ostream &os,
                                       const CMatrix< CType > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CFortranAccess
{
public:
  typedef typename Matrix::elementType elementType;

private:
  Matrix & mA;

public:
  CFortranAccess(Matrix & A):
      mA(A)
  {}

  ~CFortranAccess() {}

  /**
   * Retrieve a row of the matrix using Fortran style indexing.
   * @param unsigned C_INT32 row
   * @return elementType * row
   */
  inline elementType * operator[](unsigned C_INT32 row)
  {return mA[row - 1] - 1;}

  /**
   * Retrieve a row of the matrix using Fortran style indexing.
   * @param unsigned C_INT32 row
   * @return const elementType * row
   */
  inline const elementType * operator[](unsigned C_INT32 row) const
  {return mA[row - 1] - 1;}

  /**
   * Retrieve a matrix element using Fortran style indexing.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return const elementType & element
   */
  inline elementType & operator()(const unsigned C_INT32 & row,
                                  const unsigned C_INT32 & col)
  {return mA(row - 1, col - 1);}

  /**
   * Retrieve a matrix element using Fortran style indexing.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return const elementType & element
   */
  inline const elementType & operator()(const unsigned C_INT32 & row,
                                        const unsigned C_INT32 & col) const
  {return mA(row - 1, col - 1);}
};

template <class Matrix>
class CUpperTriangularView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;
  elementType mZero;

public:
  CUpperTriangularView(const Matrix & A, const elementType zero):
      mA(A),
      mZero(zero)
  {}

  ~CUpperTriangularView() {}

  /**
   * The number of rows of the matrix.
   * @return unsigned C_INT32 rows
   */
  unsigned C_INT32 numRows() const {return mA.numRows();}

  /**
   * The number of columns of the matrix
   * @return unsigned C_INT32 cols
   */
  unsigned C_INT32 numCols() const {return mA.numCols();}

  /**
   * Retrieve a matrix element using the indexing style of the matrix.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return elementType element
   */
  inline elementType operator()(const unsigned C_INT32 & row,
                                const unsigned C_INT32 & col) const
  {
    if (row > col)
      return mZero;
    else
      return mA(row, col);
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CUpperTriangularView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUpperTriangularView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUpperTriangularView< Matrix > & A);
#else
  friend
  std::ostream &operator << <>(std::ostream &os,
                               const CUpperTriangularView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CLowerTriangularView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;
  elementType mZero;

public:
  CLowerTriangularView(const Matrix & A, const elementType zero):
      mA(A),
      mZero(zero)
  {}

  ~CLowerTriangularView() {}

  /**
   * The number of rows of the matrix.
   * @return unsigned C_INT32 rows
   */
  unsigned C_INT32 numRows() const {return mA.numRows();}

  /**
   * The number of columns of the matrix
   * @return unsigned C_INT32 cols
   */
  unsigned C_INT32 numCols() const {return mA.numCols();}

  /**
   * Retrieve a matrix element using the indexing style of the matrix.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return elementType element
   */
  inline elementType operator()(const unsigned C_INT32 & row,
                                const unsigned C_INT32 & col) const
  {
    if (row < col)
      return mZero;
    else
      return mA(row, col);
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CLowerTriangularView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CLowerTriangularView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CLowerTriangularView< Matrix > & A);
#else
  friend
  std::ostream &operator << <>(std::ostream &os,
                               const CLowerTriangularView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CUnitUpperTriangularView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;
  elementType mZero;
  elementType mUnit;

public:
  CUnitUpperTriangularView(const Matrix & A,
                           const elementType zero,
                           const elementType unit):
      mA(A),
      mZero(zero),
      mUnit(unit)
  {}

  ~CUnitUpperTriangularView() {}

  /**
   * The number of rows of the matrix.
   * @return unsigned C_INT32 rows
   */
  unsigned C_INT32 numRows() const {return mA.numRows();}

  /**
   * The number of columns of the matrix
   * @return unsigned C_INT32 cols
   */
  unsigned C_INT32 numCols() const {return mA.numCols();}

  /**
   * Retrieve a matrix element  using the indexing style of the matrix.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return elementType element
   */
  inline elementType operator()(const unsigned C_INT32 & row,
                                const unsigned C_INT32 & col) const
  {
    if (row < col)
      return mA(row, col);
    else if (row > col)
      return mZero;
    else
      return mUnit;
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CUnitUpperTriangularView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUnitUpperTriangularView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUnitUpperTriangularView< Matrix > & A);
#else
  friend
  std::ostream &operator << <>(std::ostream &os,
                               const CUnitUpperTriangularView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CUnitLowerTriangularView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;
  elementType mZero;
  elementType mUnit;

public:
  CUnitLowerTriangularView(const Matrix & A,
                           const elementType zero,
                           const elementType unit):
      mA(A),
      mZero(zero),
      mUnit(unit)
  {}

  ~CUnitLowerTriangularView() {}

  /**
   * The number of rows of the matrix.
   * @return unsigned C_INT32 rows
   */
  unsigned C_INT32 numRows() const {return mA.numRows();}

  /**
   * The number of columns of the matrix
   * @return unsigned C_INT32 cols
   */
  unsigned C_INT32 numCols() const {return mA.numCols();}

  /**
   * Retrieve a matrix element using the indexing style of the matrix.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return elementType element
   */
  inline elementType operator()(const unsigned C_INT32 & row,
                                const unsigned C_INT32 & col) const
  {
    if (row > col)
      return mA(row, col);
    else if (row < col)
      return mZero;
    else
      return mUnit;
  }

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CUnitLowerTriangularView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUnitLowerTriangularView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CUnitLowerTriangularView< Matrix > & A);
#else
  friend
  std::ostream &operator << <> (std::ostream &os,
                                const CUnitLowerTriangularView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class Matrix>
class CTransposeView
{
public:
  typedef typename Matrix::elementType elementType;

private:
  const Matrix & mA;

public:
  CTransposeView(const Matrix & A): mA(A) {}

  ~CTransposeView() {}

  /**
   * The number of rows of the matrix.
   * @return unsigned C_INT32 rows
   */
  unsigned C_INT32 numRows() const {return mA.numCols();}

  /**
   * The number of columns of the matrix
   * @return unsigned C_INT32 cols
   */
  unsigned C_INT32 numCols() const {return mA.numRows();}

  /**
   * Retrieve a matrix element using the indexing style of the matrix.
   * @param const unsigned C_INT32 & row
   * @param const unsigned C_INT32 & col
   * @return elementType element
   */
  inline elementType operator()(const unsigned C_INT32 & row,
                                const unsigned C_INT32 & col) const
  {return mA(col, row);}

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CTransposeView< Matrix > & A
   * @return ostream & os
   */
#ifdef SWIG
  friend
  std::ostream &operator << (std::ostream &os,
                             const CTransposeView< Matrix > & A);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend
  std::ostream &operator << (std::ostream &os,
                             const CTransposeView< Matrix > & A);
#else
  friend
  std::ostream &operator << <>(std::ostream &os,
                               const CTransposeView< Matrix > & A);
#endif // WIN32
#endif // SWIG
};

template <class CType>
std::ostream &operator<<(std::ostream &os, const CMatrix< CType > & A)
{
  os << "Matrix(" << A.mRows << "x" << A.mCols << ")" << std::endl;

  unsigned C_INT32 i, j;
  CType * tmp = A.mArray;

  for (i = 0; i < A.mRows; i++)
    {
      for (j = 0; j < A.mCols; j++)
        os << "\t" << *(tmp++);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator<<(std::ostream &os,
                         const CUpperTriangularView< Matrix > & A)
{
  unsigned C_INT32 i, imax = A.numRows();
  unsigned C_INT32 j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator<<(std::ostream &os,
                         const CLowerTriangularView< Matrix > & A)
{
  unsigned C_INT32 i, imax = A.numRows();
  unsigned C_INT32 j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator << (std::ostream &os,
                           const CUnitUpperTriangularView< Matrix > & A)
{
  unsigned C_INT32 i, imax = A.numRows();
  unsigned C_INT32 j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator << (std::ostream &os,
                           const CUnitLowerTriangularView< Matrix > & A)
{
  unsigned C_INT32 i, imax = A.numRows();
  unsigned C_INT32 j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

template <class Matrix>
std::ostream &operator << (std::ostream &os,
                           const CTransposeView< Matrix > & A)
{
  unsigned C_INT32 i, imax = A.numRows();
  unsigned C_INT32 j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}

#endif // COPASI_CMatrix
