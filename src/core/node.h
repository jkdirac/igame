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

	Node (
		const Node* orig 
		);

	~Node ();

	bool equal (
		const Node* rhs
		) const;

	void setNodeLabel (
		const string& label
		);

	void setParentNodeLabel (
		const string& label
		);

	string getNodeLabel () const;

	string getParentNodeLabel () const;

	void setNodeWeight (
		const int& cn,
		const int& pn
		);

	pair<int,int> getNodeWeight () const;
	
	void addChild (
		Node* childNodePtr
		);

	bool isLeaf () const;

  private:

	string nodeLabel;

	string parentNodeLabel;

	vector<Node*> children;

	pair<int,int> weight;

	string huffman;

};

#endif
