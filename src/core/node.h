/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-09-25 16:15
*
*            Filename:		node.h
*
*            Description: .
*
************************************************************************************/
#ifndef NODE_H
#define NODE_H

#include "g_i.h"

class Node
{
  friend class Tree;
  friend class IsLess_n;

  public:

	Node ();
	Node (const Node*);
	~Node ();

	string getNodeLabel () const;
	string getParentNodeLabel () const;

	void setNodeLabel (const string&);
	void setNodeWeight (const int&, const int&);
	markType getNodeWeight () const;
	
	void addChild (Node*);
	bool isLeaf () const;

  private:

	string nodeLabel;
	string parentNodeLabel;

	//	children pointers
	vector<Node*> children;

  private: 

	markType weight;
	string huffman;

};

#endif
