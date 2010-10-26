#include "tree.h"

Tree::Tree () {}

Tree::Tree (const Tree* orig) : unicode (orig->unicode)
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
	for (int i=0; i < listOfNodes.size (); i++) delete listOfNodes[i];
}

int Tree::getNumOfNodes () const {return listOfNodes.size ();}

void Tree::__add_tree_prefix (const string& prefix)
{
	if (!mapNodes.empty ()) mapNodes.clear ();

	for (int i=0; i<listOfNodes.size (); i++)
	{
		Node* n = listOfNodes[i];

		if (n->nodeLabel != "ROOT") 
		{
			n->nodeLabel = prefix + n->nodeLabel;
			if (n->parentNodeLabel != "ROOT")
				n->parentNodeLabel = prefix + n->parentNodeLabel;
		}

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
	else throw CoreException (
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
	for (int cnt =0; cnt < n->children.size (); cnt++)
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

	/**
	 * huffman code of children are generated only
	 * by adding 0 (left child) or 1 (right child) 
	 * to their parent one
	 * *
	 * ROOT has empty huffman code
	 */
	
	for (int i=0; i<n->children.size (); i++)
	{
		Node* child = n->children[i];
		if (i==0) child->huffman = n->huffman + "0";
		else child->huffman = n->children[i-1]->huffman+"1";
		genHuffman (child->nodeLabel);
	}
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
		os << "\n\n" << label << " 	--> ";
		for (int cnt =0; cnt < numCh; cnt++)
		{
			Node* nn = n->children[cnt];
			os << std::setw(5) << "\n	" 
				<< " ( " << nn->weight.first << ", " 
				<< nn->weight.second
				<< " ) " << "	";
		}

		for (int cnt =0; cnt < numCh; cnt++)
		{
			Node* nn = n->children[cnt];
			Output (os, nn->nodeLabel);
		}
	}
}

void Tree::genUnicode ()
{
	if (!unicode.empty ()) unicode.clear ();
	for (int i=0; i < listOfNodes.size (); i++)
	{
		Node* n = listOfNodes[i];
		if (n->children.empty ())
		{
			//is Leaf
			ostringstream oss;
			oss << "[" << n->huffman << "("
				<< n->weight.first << ","
				<< n->weight.second << ")]";
			unicode += oss.str ();
		}
	}		
}
