/* Begin CVS Header
  $Source: /fs/turing/cvs/copasi_dev/copasi/function/CEvaluationNodeNumber.h,v $
  $Revision: 1.13 $
  $Name: Build-31 $
  $Author: gauges $
  $Date: 2009/02/19 15:37:57 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeNumber
#define COPASI_CEvaluationNodeNumber

class CCopasiDataModel;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeNumber : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      DOUBLE = 0x00000000,
      INTEGER = 0x00000001,
      ENOTATION = 0x00000002,
      RATIONALE = 0x00000003
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeNumber();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeNumber(const SubType & subType,
                          const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeNumber & src
     */
    CEvaluationNodeNumber(const CEvaluationNodeNumber & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeNumber();

    /**
     * Creates a new CEvaluationNodeNumber from an ASTNode.
     * @param const ASTNode* node
     * @return CEvaluationNode* return a pointer to the newly created node;
     */
    static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

    /**
     * Create a new ASTNode corresponding to this NumberNode.
     * @return ASTNode* return a pointer to the newly created node;
     */
    ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

    /**
     * generate display MathML recursively
     */
    virtual void writeMathML(std::ostream & out,
                             const std::vector<std::vector<std::string> > & env,
                             bool expand = true,
                             unsigned C_INT32 l = 0) const;
  };

#endif // COPASI_CEvaluationNodeNumber
