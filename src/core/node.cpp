#include "node.h"

Node::Node ()
  :weight (make_pair(-1, -1))
{}

//
//	children will not be initialized
//
Node::Node (
	const Node* orig
	):
  nodeLabel (orig->nodeLabel),
  parentNodeLabel (orig->parentNodeLabel),
  weight (orig->weight),
  huffman (orig->huffman)
{}

Node::~Node ()
{}

void Node::setNodeLabel (
	const string& label
	)
{
  nodeLabel = label;
}

void Node::setParentNodeLabel (
	const string& label
	)
{
  parentNodeLabel = label;
}

void Node::setNodeWeight (
	const int& cn,
	const int& pn
	)
{
  weight = make_pair (cn, pn);
}

string Node::getNodeLabel () const
{
  return nodeLabel; 
}

string Node::getParentNodeLabel () const
{
  return parentNodeLabel;
}

pair<int,int> Node::getNodeWeight () const
{
  return weight;
}

void Node::addChild (
	Node* childNodePtr
	)
{
  children.push_back (childNodePtr);
}

bool Node::isLeaf () const
{
  return children.size () == 0;
}

bool Node::equal (
	const Node* rhs
	) const
{
  //compare current node
  bool isequal = (weight == rhs->weight 
	  && huffman == rhs->huffman);
  if (!isequal) return false;

  //compare children nodes
  int numCh = children.size ();
  if (rhs->children.size () != numCh) 
	return false;

  for (int cnt =0; cnt < numCh; cnt++)
  {
	Node* n1 = children[cnt];
	Node* n2 = rhs->children[cnt];
	if (!n1->equal(n2)) return false;
  }
  return true;
}
