#include "tree.h"

Tree::Tree ()
{}

Tree::Tree (const Tree* orig)
{
	//copy listOfNodes and mapNodes
	for (int i=0; i < orig->listOfNodes.size (); i++)
	{
		Node* n1 = orig->listOfNodes[i];
		Node* n2 = createNode (n1);
		mapNodes[n2->nodeLabel] = n2;
	}

	//add children to each Node* 
	//object in listOfNodes
	for (int i=0; i < orig->listOfNodes.size (); i++)
	{
		Node* n1 = orig->listOfNodes[i];
		Node* n2 = listOfNodes[i];
		for (int j=0; j < n1->children.size (); j++)
		{
			Node* n3 = n1->children[j];
			Node* n4 = getNode (n3->nodeLabel);
			n2->children.push_back (n4);
		}
	}
}

Tree::~Tree ()
{
	//delete Node objects allocated in createNode
	for (int i=0; i < listOfNodes.size (); i++)
		delete listOfNodes[i];
}

int Tree::getNumOfNodes () const {
	return listOfNodes.size ();
}

void Tree::checkIntegrated () const
{
	set<int> __index_root;

	for (int i=0; i < listOfNodes.size (); i++)
	{
		Node* n = listOfNodes[i];
		if (n->parentNodeLabel == "ROOT") __index_root.insert (i);
	}

	if (__index_root.size () == 0) throw StrCacuException (
			"No tree ROOT is found!"
			);
	if (__index_root.size () > 1) throw StrCacuException (
			"More than one tree ROOT is found!"
			);

	set<string> collection;
	Node* n = listOfNodes[*__index_root.begin ()];
	__label_collection (collection, n);

	if (collection.size () < listOfNodes.size ())
		throw StrCacuException (
				"Incompleted Tree: unrelated nodes are found!"
				);
}

Node* Tree::__label_collection (
		set<string>& collection,
		const Node* n
		) const
{
	for (int i=0; i < n->children.size (); i++)
	{
		Node* __child = n->children[i];
		collection.insert (__child->nodeLabel);
		__label_collection (collection, n->children[i]); 
	}
}

void Tree::__add_tree_prefix (const string& prefix)
{
	if (!mapNodes.empty ()) mapNodes.clear ();

	for (int i=0; i<listOfNodes.size (); i++)
	{
		Node* n = listOfNodes[i];

		n->nodeLabel = prefix + n->nodeLabel;
		if (n->parentNodeLabel != "ROOT")
			n->parentNodeLabel = prefix + n->parentNodeLabel;

		mapNodes.insert (make_pair(n->nodeLabel, n));
	}
}

Node* Tree::createNode ()
{
	Node* newNode = new Node;
	listOfNodes.push_back (newNode);
	return newNode;
}

Node* Tree::createNode (
		const Node* n
		)
{
	Node* newNode = new Node (n);
	listOfNodes.push_back (newNode);
	return newNode;
}

Node* Tree::createNode (
		const string& child,
		const string& parent
		)
{
	Node* n = new Node;

	//	set data members
	n->nodeLabel = child;
	n->parentNodeLabel = parent;

	//	push it back into nodes list
	listOfNodes.push_back (n);

	if (!mapNodes.count (child)) 
		mapNodes[n->nodeLabel] = n;
	else throw StrCacuException (
			"Two nodes with same label is not permitted!"
			);

	return n;
}

void Tree::addNodeChildren ()
{
	for (int i=0; i < listOfNodes.size(); i++)
	{
		string childNodeLabel = listOfNodes[i]->nodeLabel;
		string parentNodeLabel = listOfNodes[i]->parentNodeLabel;

		if (childNodeLabel == "ROOT") continue;
		else 
		{
			Node* parent = mapNodes[parentNodeLabel];
			Node* child = mapNodes[childNodeLabel];
			parent->addChild (child);
		}
	}
}

Node* Tree::getNode (const string& label)
{
	if (mapNodes.count (label)) return mapNodes[label];
	else return 0;
}

const Node* Tree::getNode (const string& label) const
{
	if (mapNodes.count (label)) return mapNodes.find (label)->second;
	else return 0;
}

Node* Tree::getNode (const int& n) {
	return listOfNodes.at(n);
}

const Node* Tree::getNode (const int& n) const {
	return listOfNodes.at(n);
}

markType Tree::genWeight (const string& label)
{
	// leaf node case
	Node* n = mapNodes[label];	  
	if (n->children.empty ()) return n->weight;

	// otherwise  
	// assign minW with value of its first child
	markType minW (0,0);
	int numCh = n->children.size ();

	for (int cnt =0; cnt < numCh; cnt++)
	{
		markType tempW (0,0);
		string label = n->children[cnt]->nodeLabel;
		tempW = genWeight (label);

		if (cnt == 0) minW = tempW;
		else if (tempW < minW) minW = tempW;
	}

	n->weight = minW;

	// sort children nodes by their weight
	std::stable_sort (
			n->children.begin (),
			n->children.end (),
			IsLess_n ()
			);

	return minW;
}

void Tree::genHuffman (const string& label)
{
	// make sure that children nodes has been sorted
	// no need to generate huffman code for leaf nodes
	Node* n = mapNodes[label];	  
	if (n->children.empty ()) return;

	// huffman code of children are generated only
	// by adding 0 (firstchild) or 1 (ith time for i-1 child)
	// to their parent one
	Node* nn = 0;
	string huff = n->huffman;
	int numCh = n->children.size ();

	// firstchild
	string firstchild = huff + "0";
	nn = n->children.at (0);
	nn->huffman = firstchild;
	genHuffman (nn->nodeLabel);

	//nextsiblings
	string nextsibling = huff;
	for (int cnt =1; cnt < numCh; cnt++)
	{
		nextsibling += "1";
		nn = n->children.at (cnt);
		nn->huffman = nextsibling;
		genHuffman (nn->nodeLabel);
	}

	//return
}

void Tree::Output (ostream& os) const {
	Output (os, "ROOT");
}

void Tree::Output (ostream& os, const string& label) const
{
	if (!mapNodes.count (label)) return;

	//find children
	Node* n = mapNodes.find (label)->second;
	int numCh = n->children.size ();
	if (numCh == 0) return;
	else
	{
		os << "\n" << std::setw (5) << label << " --> ";
		for (int cnt =0; cnt < numCh; cnt++)
		{
			Node* nn = n->children[cnt];
			os << std::setw(5) 
				<< nn->nodeLabel << " ( " 
				<< nn->weight.first << " " 
				<< nn->weight.second << " ,"
				<< nn->huffman << ")" << "	";
		}

		for (int cnt =0; cnt < numCh; cnt++)
		{
			Node* nn = n->children[cnt];
			Output (os, nn->nodeLabel);
		}
	}
}

bool Tree::equal (
		const Tree* rhs
		) const 
{
	Node* rootLHS = mapNodes.find("ROOT")->second;
	Node* rootRHS = rhs->mapNodes.find("ROOT")->second;
	return rootLHS->equal (rootRHS);
}

