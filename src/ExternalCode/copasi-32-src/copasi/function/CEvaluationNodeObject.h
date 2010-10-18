/* Begin CVS Header
  $Source: /fs/turing/cvs/copasi_dev/copasi/function/CEvaluationNodeObject.h,v $
  $Revision: 1.18 $
  $Name: Build-31 $
  $Author: shoops $
  $Date: 2009/08/14 13:42:47 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeObject
#define COPASI_CEvaluationNodeObject

#include "report/CCopasiObjectName.h"

class CRegisteredObjectName;
class CCopasiDataModel;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeObject : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   * The typing of variables must be handled by the tree.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    CN = 0x00000000,
    POINTER = 0x00000001
  };

  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeObject();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeObject(const SubType & subType,
                        const Data & data);

  /**
   * Specific constructor
   * @param const Data & data
   */
  CEvaluationNodeObject(const C_FLOAT64 * pValue);

  /**
   * Copy constructor
   * @param const CEvaluationNodeObject & src
   */
  CEvaluationNodeObject(const CEvaluationNodeObject & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeObject();

  /**
   * Compile a node;
   * @param const CEvaluationTree * pTree
   * @return bool success;
   */
  virtual bool compile(const CEvaluationTree * pTree);

  /**
   * Retrieve the value of the node
   * @return const C_FLOAT64 & value
   */
  virtual inline const C_FLOAT64 & value() const
  {return *const_cast<C_FLOAT64 *>(&mValue) = *mpValue;}

  /**
   * Retrieve the value of the node. This method is superseded
   * by value() which will perform faster.
   * @return const Data & value
   */
  virtual const Data & getData() const;

  /**
   * Set the data of the Node.
   * @param const Data & data
   * @return bool success
   */
  virtual bool setData(const Data & data);

  /**
   * Retrieve the infix value of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getInfix() const;

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getDisplayString(const CEvaluationTree * pTree) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return const Data & value
   */
  virtual std::string getDisplay_C_String(const CEvaluationTree * pTree) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes in
   * Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getDisplay_MMD_String(const CEvaluationTree * pTree) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes in
   * XPPAUT format.
   * @return const Data & value
   */
  virtual std::string getDisplay_XPP_String(const CEvaluationTree * pTree) const;

  /**
   * Create a new operator node from an ASTNode tree.
   * @param const ASTNode* node
   * @return CEvaluationNode* return a pointer to the newly created node;
   */
  static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

  /**
   * Converts this node to an ASTNode.
   * @return ASTNode the resulting ASTNode.
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * Retrieve the CN of the referred object.
   * @return const CRegisteredObjectName & objectCN
   */
  const CRegisteredObjectName & getObjectCN() const;

  /**
   * generate display MathML recursively
   */
  virtual void writeMathML(std::ostream & out,
                           const std::vector<std::vector<std::string> > & env,
                           bool expand = true,
                           unsigned C_INT32 l = 0) const;

  //Attributes
private:
  /**
   * Pointer to the value of the object.
   */
  const C_FLOAT64 * mpValue;

  /**
   * Pointer to the object
   */
  const CCopasiObject * mpObject;

  /**
   * The registered object name to track eventual renaming.
   */
  CRegisteredObjectName mRegisteredObjectCN;
};

#endif // COPASI_CEvaluationNodeObject
