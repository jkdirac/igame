/*************************************************************************************
 *
 *            Author: liaochen- liaochen@mail.ustc.edu.cn
 *
 *            Last modified:	2010-09-25 16:05
 *
 *            Filename:		tree.h
 *
 *            Description: .
 *
 ************************************************************************************/
#ifndef TREE_H
#define TREE_H

#include "node.h"

class IsLess_n
{
	public:

		IsLess_n () {}

		inline bool operator () (
				const Node* x, 
				const Node* y
				) const
		{
			return x->weight < y->weight;
		}
};

class Tree
{
	friend class MySpecies;
	friend class IsLess_t;

	public:

	Tree ();
	Tree (const Tree*);
	~Tree ();

	bool equal (const Tree*) const;

	Node* createNode ();
	Node* createNode (const Node*);
	Node* createNode (const string&, const string&);

	void addNodeChildren ();

	Node* getNode (const string&);
	const Node* getNode (const string&) const;
	Node* getNode (const int&);
	const Node* getNode (const int&) const;

	markType genWeight (const string&);
	void genHuffman (const string&);

	void Output (ostream&) const;

	private:

	void Output (ostream&, const string&) const; 

	private:

	vector<Node*> listOfNodes;
	map<string, Node*> mapNodes;
};

#endif
