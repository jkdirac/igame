/* Begin CVS Header
  $Source: /fs/turing/cvs/copasi_dev/copasi/function/CEvaluationNodeLogical.h,v $
  $Revision: 1.13 $
  $Name: Build-31 $
  $Author: shoops $
  $Date: 2009/07/30 21:08:33 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeLogical
#define COPASI_CEvaluationNodeLogical

#include "mathematics.h"

#include "utilities/CCopasiMessage.h"

class ASTNode;
class CCopasiDataModel;

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeLogical : public CEvaluationNode
{
public:
  /**
   * Enumeration of possible node types.
   */
  enum SubType
  {
    INVALID = 0x00FFFFFF,
    //      NOT = 0x00000001,
    OR = 0x00000001,
    XOR = 0x00000002,
    AND = 0x00000003,
    EQ = 0x00000004,
    NE = 0x00000005,
    GT = 0x00000006,
    GE = 0x00000007,
    LT = 0x00000008,
    LE = 0x00000009
  };

  // Operations
private:
  /**
   * Default constructor
   */
  CEvaluationNodeLogical();

public:
  /**
   * Default constructor
   * @param const SubType & subType
   * @param const Data & data
   */
  CEvaluationNodeLogical(const SubType & subType,
                         const Data & data);

  /**
   * Copy constructor
   * @param const CEvaluationNodeLogical & src
   */
  CEvaluationNodeLogical(const CEvaluationNodeLogical & src);

  /**
   * Destructor
   */
  virtual ~CEvaluationNodeLogical();

  /**
   * Retrieve the value of the node
   * @return const C_FLOAT64 & value
   */
  virtual inline const C_FLOAT64 & value() const
  {
    C_FLOAT64 &Value = *const_cast<C_FLOAT64 *>(&mValue);

    switch (mType & 0x00FFFFFF)
      {
        case OR:
          Value = (mpLeft->value() != 0.0 ||
                   mpRight->value() != 0.0) ? 1.0 : 0.0;
          break;

        case XOR:
          Value = ((mpLeft->value() != 0.0 && mpRight->value() == 0.0) ||
                   (mpLeft->value() == 0.0 && mpRight->value() != 0.0)) ? 1.0 : 0.0;
          break;

        case AND:
          Value = (mpLeft->value() != 0.0 &&
                   mpRight->value() != 0.0) ? 1.0 : 0.0;
          break;

        case EQ:
          Value = (mpLeft->value() == mpRight->value()) ? 1.0 : 0.0;
          break;

        case NE:
          Value = (mpLeft->value() != mpRight->value()) ? 1.0 : 0.0;
          break;

        case GT:
          Value = (mpLeft->value() > mpRight->value()) ? 1.0 : 0.0;
          break;

        case GE:
          Value = (mpLeft->value() >= mpRight->value()) ? 1.0 : 0.0;
          break;

        case LT:
          Value = (mpLeft->value() < mpRight->value()) ? 1.0 : 0.0;
          break;

        case LE:
          Value = (mpLeft->value() <= mpRight->value()) ? 1.0 : 0.0;
          break;
      }

    return Value;
  }

  /**
   * Compile a node;
   * @param const CEvaluationTree * pTree
   * @return bool success;
   */
  virtual bool compile(const CEvaluationTree * pTree);

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
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getDisplay_MMD_String(const CEvaluationTree * pTree) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in XPPAUT format.
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
   * Check whether the result is Boolean
   * @return bool isBoolean
   */
  virtual bool isBoolean() const;

  /**
   * Create a new ASTNode corresponding to this OperatorNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * generate display MathML recursively
   */
  virtual void writeMathML(std::ostream & out,
                           const std::vector<std::vector<std::string> > & env,
                           bool expand = true,
                           unsigned C_INT32 l = 0) const;

  // Attributes
private:
  CEvaluationNode * mpLeft;

  CEvaluationNode * mpRight;
};

#endif // COPASI_CEvaluationNodeLogical
