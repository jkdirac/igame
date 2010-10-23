#include "node.h"

Node::Node ()
	:
		weight (make_pair(-1, -1))
{}

//
//	children will not be initialized
//
Node::Node (const Node* orig)
	:
		nodeLabel (orig->nodeLabel),
		parentNodeLabel (orig->parentNodeLabel),
		weight (orig->weight),
		huffman (orig->huffman)
{}

Node::~Node ()
{}

void Node::setNodeLabel (const string& label) {
	nodeLabel = label;
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

markType Node::getNodeWeight () const
{
	return weight;
}

void Node::addChild (
		Node* childNodePtr
		)
{
	assert (childNodePtr != NULL);
	children.push_back (childNodePtr);
}

bool Node::isLeaf () const
{
	return children.size () == 0;
}
