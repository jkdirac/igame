/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/function/CNodeK.h,v $
   $Revision: 1.21 $
   $Name: Build-31 $
   $Author: gauges $
   $Date: 2006/10/15 07:16:08 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*  CNodeK
 *
 *  CNodeK.cpp based on UDKType.cpp from
 *  (C) Pedro Mendes 1995-2000
 *
 *  Created for Copasi by Stefan Hoops
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CNodeK
#define COPASI_CNodeK

#include <string>
#include <vector>

#include "utilities/CReadConfig.h"
//#include "utilities/CWriteConfig.h"
#include "function/CCallParameters.h"

// symbols for CNodeK types and values
#define N_NOP '@'

#define N_ROOT '%'       // the root note
#define N_OPERATOR 'O'   // operator: + - * / ^ ()
#define N_IDENTIFIER 'I' // see specific subtypes
#define N_FUNCTION 'F'   // see specific subtypes
#define N_OBJECT 'o'     // an object
#define N_NUMBER 'N'     // a C_FLOAT64 constant

// subtypes for N_FUNCTION
#define N_LOG10 'L'
#define N_LOG 'l'
#define N_EXP 'e'
#define N_SIN 'S'
#define N_COS 'C'
#define N_RND 'R'
#define N_GAUSS 'G'
#define N_BOLTZ 'B'

#define N_TAN 't'
#define N_SEC 'a'
#define N_CSC 'b'
#define N_COT 'c'
#define N_SINH 'd'
#define N_COSH 'f'
#define N_TANH 'g'
#define N_SECH 'h'
#define N_CSCH 'i'
#define N_COTH 'j'
#define N_ARCSIN 'n'
#define N_ARCCOS 'q'
#define N_ARCTAN 'r'
#define N_ARCSEC 'u'
#define N_ARCCSC 'v'
#define N_ARCCOT 'w'
#define N_ARCSINH 'x'
#define N_ARCCOSH 'y'
#define N_ARCTANH 'z'
#define N_ARCSECH 'A'
#define N_ARCCSCH 'D'
#define N_ARCCOTH 'E'
#define N_ABS     'H'
#define N_SQRT    'J'

// subtypes for N_IDENTIFIER
#define N_SUBSTRATE 's'
#define N_PRODUCT 'p'
#define N_MODIFIER 'm'
#define N_KCONSTANT 'k'
#define N_VOLUME 'V'

/** @dia:pos 12.7478,42.4925 */
class CNodeK
  {
    // Attributes
  private:
    /**
     *  The type of the node. One of N_ROOT, N_OPERATOR, N_IDENTIFIER,
     *  N_FUNCTION, N_NUMBER
     */
    char mType;

    /**
     *  The subtype of a node.
     *  for type N_FUNCTION one of: N_LOG10, N_LOG, N_EXP, N_SIN, N_COS,
     *  N_RND, N_GAUSS, N_BOLTZ
     *  for type N_IDENTIFIER one of:N_SUBSTRATE, N_PRODUCT, N_MODIFIER,
     *  N_KCONSTANT
     *  for type N_OPERATOR one of: + - * / ^ () ...
     */
    char mSubtype;

    /**
     *  The left branch of the tree originating from tyhis node
     */
    CNodeK * mLeft;

    /**
     *  The right branch of the tree originating from tyhis node
     */
    CNodeK * mRight;

    /**
     *  The value of a node of type N_NUMBER
     */
    C_FLOAT64 mConstant;

    /**
     *  The name of the node for type N_IDENTIFIER
     */
    std::string mName;

    /**
     *  The index of the node for type N_IDENTIFIER
     */
    C_INT32 mIndex;

    /**
     *  The index in old Gepasi format
     */
    C_INT32 mOldIndex;

    /**
     *  WHAT IS THIS FOR??? PLEASE ADD COMMENT!
     */
    int attribute1;

    /**
     *  The explicit function string
     */
    std::string mExplicitFunction;

    // Operations
  public:
    /**
     * Default constructor
     */
    CNodeK();

    /**
     *  Copy constructor
     *  @param "const CNodeK &" src
     */
    CNodeK(const CNodeK & src);

    /**
     * Constructor for operator
     * @param "const char" type
     * @param "const char" subtype
     */
    CNodeK(char type, char subtype);

    /**
     * Constructor for identifier
     * @param "const string" &name
     */
    CNodeK(const std::string & name);

    /**
     * Constructor for a constant
     * @param "const C_FLOAT64" constant
     */
    CNodeK(C_FLOAT64 constant);

    /**
     * Destructor
     */
    ~CNodeK();

    /**
     * Delete
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  Returns a string that contains the equation defined from
    *  this node downwards. The function contains explicit names
    *  of node identifiers, rather than the abstract symbol.
    *  @param "const CCallParameters &" callParameterNames a vector of string pointers with identifier names
    *  @param "const string &" r a suffix for parameter names (usually reaction number)
     *  @return string
     */
    std::string getExplicitFunctionString(const std::vector< std::vector< std::string > > & callParameterNames,
                                          const std::string &r);

    void writeMathML(std::ostream & out, C_INT32 level) const;

    /**
     * Retrieving mType the type of a node
     * @return char
     */
    char getType() const;

    /**
     * Retrieving mSubtype the subtype of a node
     * @return char
     */
    char getSubtype() const;

    /**
     * Retrieving mLeft the left branch of a node
     * @return CNodeK
     */
    CNodeK & getLeft() const;

    /**
     * Retrieving mName the name of a node
     * @return string
     */
    CNodeK & getRight() const;

    /**
     * Retrieving mName the name of a node
     * @return string
     */
    std::string getName() const;

    /**
     * Retrieving value of a node
     * @return C_FLOAT64
     */
    C_FLOAT64 getConstant() const;

    /**
     * Retrieving index the name of a node
     * @return C_INT32
     */
    C_INT32 getIndex() const;

    /**
     * Setting mType the subtype of a node
     * @param "const char" type
     */
    void setType(const char ype);

    /**
     * Setting mSubtype the subtype of a node
     * @param "const char" subtype
     */
    void setSubtype(const char subtype);

    /**
     * Setting mLeft the pointer to the left branch
     * @param CNodeK &left
     */
    void setLeft(CNodeK & left);

    /**
     * Setting mLeft the pointer to the left branch
     * @param CNodeK *pleft
     */
    void setLeft(CNodeK * pleft);

    /**
     * Setting mRight the pointer to the right branch
     * @param CNodeK &right
     */
    void setRight(CNodeK & right);

    /**
     * Setting mRight the pointer to the right branch
     * @param CNodeK *pright
     */
    void setRight(CNodeK * pright);

    /**
     * Setting mName the name of an identifier
     * @param "const string" &name
     */
    void setName(const std::string & name);

    /**
     * Setting the value of a number
     * @param C_FLOAT64 &constant
     */
    void setConstant(C_FLOAT64 & constant);

    /**
     * Setting the index of an identifier
     * @param C_INT32 &index
     */
    void setIndex(C_INT32 index);

    /**
     * Setting the old index
    * (Gepasi format, each type is indexed separately)
     * @param C_INT32 &index
     */
    void setOldIndex(C_INT32 oldindex);

    /**
     *  This checks whether mLeft points to a valid CNodeK
     *  @return int 1 or 0
     */
    C_INT16 isLeftValid() const;

    /**
     *  This checks whether mRight points to a valid CNodeK
     *  @return int 1 or 0
     */
    C_INT16 isRightValid() const;

    /**
     *  This checks whether the node is a number (mType = N_NUMBER)
     *  @return int 1 or 0
     */
    C_INT16 isNumber() const;

    /**
     *  This checks whether the node is an identifier (mType = N_IDENTIFIER)
     *  @return int 1 or 0
     */
    C_INT16 isIdentifier() const;

    /**
     *  This checks whether the node is a operator (mType = N_OPERATOR)
     *  @return int 1 or 0
     */
    C_INT16 isOperator() const;

    /**
     *  This returns the left precedence value of a node
     *  @return int
     */
    C_INT16 leftPrecedence() const;

    /**
     *  This returns the right precedence value of a node
     *  @return int
     */
    C_INT16 rightPrecedence() const;

    /**
     *  This calculates the value of this sub-tree (ie with this node as root)
     *  @param const CCallParameters<C_FLOAT64> & callParameters
     *  @return C_FLOAT64
     */
    C_FLOAT64 value(const CCallParameters<C_FLOAT64> & callParameters) const;
  };

#endif // COPASI_CNodeK
