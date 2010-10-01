#include "tree.h"

Tree::Tree ()
{}

Tree::Tree (
	const Tree* orig
	)
{
  //copy listOfNodes and mapNodes
  int numN = orig->listOfNodes.size ();
  for (int cnt =0; cnt < numN; cnt++)
  {
	Node* n1 = orig->listOfNodes[cnt];
	Node* n2 = createNode (n1);
	mapNodes[n2->nodeLabel] = n2;
  }

  //add children to each Node* 
  //object in listOfNodes
  for (int cnt=0; cnt < numN; cnt++)
  {
	Node* n1 = orig->listOfNodes[cnt];
	Node* n2 = listOfNodes[cnt];
	int numCh = n1->children.size ();
	for (int cnt2 =0; cnt2 < numCh; cnt2++)
	{
	  Node* n3 = n1->children[cnt2];
	  string label = n3->nodeLabel;
	  Node* n4 = getNode (label);
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
		const string& nCL,
		const string& nPL
		)
{
	Node* newNode = new Node;

	//	set data members
	newNode->nodeLabel = nCL;
	newNode->parentNodeLabel = nPL;

	//	push it back into nodes list
	listOfNodes.push_back (newNode);
	return newNode;
}

void Tree::addNodeMap (
	Node* node
	)
{
  if (!mapNodes.count (node->nodeLabel))
	mapNodes[node->nodeLabel] = node;
}

void Tree::addNodeChildren ()
{
  int msize = listOfNodes.size ();
  for (int cnt =0; cnt < msize; cnt++)
  {
	string childNodeLabel = 
	  listOfNodes[cnt]->nodeLabel;
	string parentNodeLabel = 
	  listOfNodes[cnt]->parentNodeLabel;

	if (childNodeLabel == "ROOT") continue;
	else mapNodes[parentNodeLabel]->
	  addChild (mapNodes[childNodeLabel]);
  }
}

Node* Tree::getNode (
	const string& label
	)
{
  if (mapNodes.count (label)) 
	return mapNodes[label];
  else return 0;
}

Node* Tree::getNode (
	const int& num
	)
{
  if (num >= listOfNodes.size ()
	  || num < 0)
	return 0;
  else return listOfNodes[num];
}

const Node* Tree::getNode (
	const string& label
	) const
{
  if (mapNodes.count (label)) 
	return mapNodes.find (label)->second;
  else return 0;
}

const Node* Tree::getNode (
	const int& num
	) const
{
  if (num >= listOfNodes.size ()
	  || num < 0)
	return 0;
  else return listOfNodes[num];
}

pair<int,int> Tree::genWeight (
	const string& label
	)
{
  // leaf node case
  Node* n = mapNodes[label];	  
  if (n->children.empty ()) return n->weight;

  // otherwise  
  // assign minW with value of its first child
  pair<int,int> minW (0,0);
  int numCh = n->children.size ();

  for (int cnt =0; cnt < numCh; cnt++)
  {
	pair<int,int> tempW (0,0);
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

void Tree::genHuffman (
	const string& label
	)
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

void Tree::Output (
	ostream& os
	) const 
{
  Output (os, "ROOT");
}

void Tree::Output (
	ostream& os, 
	const string& label
	) const
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

  //return
}

bool Tree::equal (
	const Tree* rhs
	) const 
{
  Node* root = mapNodes.find("ROOT")->second;
  Node* root1 = rhs->mapNodes.find("ROOT")->second;
  return root->equal (root1);
}

