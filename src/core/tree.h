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

	Tree (
			const Tree* orig
		 );

	~Tree ();

	bool equal (
			const Tree* rhs
			) const;

	Node* createNode ();
	Node* createNode (const Node* n);
	Node* createNode (
			const string& child,
			const string& parent
			);


	void addNodeMap (
			Node* node
			);

	void addNodeChildren ();

	Node* getNode (
			const string& label
			);

	Node* getNode (
			const int& num
			);

	const Node* getNode (
			const string& label
			) const;

	const Node* getNode (
			const int& num
			) const;

	pair<int,int> genWeight (
			const string& label
			);

	void genHuffman (
			const string& label
			);

	void Output (
			ostream& os
			) const; 

	private:

	void Output (
			ostream& os, 
			const string& label
			) const;

	private:

	vector<Node*> listOfNodes;
	map<string, Node*> mapNodes;
};

#endif
