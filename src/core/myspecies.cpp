#include "myspecies.h"

MySpecies::MySpecies () :
	Species (2,4), isRearranged (false)
{}

MySpecies::MySpecies (const int& speciesNum)
{
	ostringstream oss;
	oss << "sPecIes" << speciesNum;
	setId (oss.str ());
}

MySpecies::MySpecies (
		const MySpecies* orig
		): 
	reference_db (orig->reference_db),
	comp_type_id (orig->comp_type_id),
	speciesLabel_db (orig->speciesLabel_db),
	equiv (orig->equiv),
	isRearranged (orig->isRearranged)
{
	for (int i=0; i < orig->listOfChains.size (); i++)
		createChain (orig->listOfChains[i]);

	for (int i=0; i < orig->listOfTrees.size (); i++)
		createTree (orig->listOfTrees[i]);
}

MySpecies::~MySpecies ()
{
	for (int i=0; i < listOfChains.size (); i++)
		delete listOfChains[i];

	for (int i=0; i < listOfTrees.size (); i++)
		delete listOfTrees[i];
}

int MySpecies::getNumOfChains () const
{
	return listOfChains.size ();
}

int MySpecies::getNumOfTrees () const
{
	return listOfTrees.size ();
}

void MySpecies::split (
		bdbXMLInterface& dbreader,
		vector<MySpecies*>& pieces
		)
{
	//	first trim the species
	trim (dbreader);

	//	container to store chainnum of species
	//	chainUsed[species][chainnum set]
	vector< set<int> > chainUsed;

	for (int i=0; i < listOfTrees.size (); i++)
	{
		Tree* t = listOfTrees[i];

		//int not species associated, found = -1,
		//else found = species index in cU;
		int found = -1;
		bool exit = false;

		//	traverse all leaf nodes of tree t
		//	to find chains that associated with the tree
		for (int j =0; j< t->listOfNodes.size (); j++)
		{
			Node* n = t->getNode (j);
			if (n->isLeaf ())
			{
				//	if it a leaf node
				int chainnum = n->getNodeWeight ().first;

				//	search for species containing this chain
				for (int k=0; k < chainUsed.size (); k++)
				{
					if (chainUsed[k].count (chainnum)) 
					{
						found = k; 
						exit = true;
						break;
					}
				}
			}

			if (exit) break;
		}

		//	if found = -1; create new species
		//	containing this tree and associated chains

		//	if found >=0; merge this tree and associated 
		//	chains to that species

		if (found == -1)
		{
			MySpecies* s = new MySpecies ();

			//add tree
			s->createTree (t);

			set<int> newset;

			//add associated chains
			for (int j=0; j < t->listOfNodes.size (); j++)
			{
				Node* n = t->getNode (j);
				if (n->isLeaf ())
				{
					int chainnum = n->getNodeWeight ().first;
					assert (chainnum >= 0);

					s->createChain (listOfChains[chainnum]);
					newset.insert (chainnum);
				}
			}

			pieces.push_back (s);
			chainUsed.push_back (newset);
		}
		else
		{
			//merge
			MySpecies* s = pieces[found];
			set<int>& oldset = chainUsed[found];

			//add tree
			s->createTree (t);

			//add associated chains
			for (int j=0; j< t->listOfNodes.size (); j++)
			{
				Node* n = t->getNode (j);
				if (n->isLeaf ())
				{
					int chainnum = n->getNodeWeight ().first;
					if (!oldset.count (chainnum))
					{
						s->createChain (listOfChains[chainnum]);
						oldset.insert (chainnum);
					}
				}
			}
		}

		//merge over, go to next tree
	}

	//	handle chains remained
	for (int i=0; i < listOfChains.size (); i++)
	{
		bool found = false;
		for (int j=0; j < chainUsed.size (); j++)
			if (chainUsed[j].count (i)) found = true;
		if (!found)	//	not found
		{
			MySpecies* s = new MySpecies ();
			s->createChain (listOfChains[i]);
			pieces.push_back (s);

			//	chainUsed
			set<int> cU;
			cU.insert (i);
			chainUsed.push_back (cU);
		}
	}

	//	rearrange all species
	//	remain problems
	for (int i=0; i<pieces.size (); i++) pieces[i]->rearrange ();
}

bool MySpecies::countBindedNode (
		const string& label
		) const
{
	int numT = listOfTrees.size ();
	for (int cnt =0; cnt < numT; cnt++)
	{
		Node* n = listOfTrees[cnt]->getNode (label);
		if (!n) return true;
	}
	return false;
}

Node* MySpecies::findBindedNode (
		const string& label
		) 
{
	int numT = listOfTrees.size ();
	for (int cnt = 0; cnt < numT; cnt++)
	{
		Node* n = listOfTrees[cnt]->getNode (label);
		if (!n) return n;
	}
	return 0;
}

Chain* MySpecies::createChain ()
{
	Chain* c = new Chain;
	listOfChains.push_back (c);
	return c;
}

Chain* MySpecies::createChain (
		const Chain* orig
		)
{
	Chain* c = new Chain (orig);
	listOfChains.push_back (c);
	return c;
}

Chain* MySpecies::createChain (
		const string& prefix,
		const int& chainnum
		)
{
	Chain* c = new Chain;
	//    cout << "\nprefix = " << prefix << endl;

	ostringstream oss;
	oss << prefix << "[cHaIn" << chainnum << "]";
	c->chainLabel  = oss.str ();

	listOfChains.push_back (c);
	return c;
}

Tree* MySpecies::createTree ()
{
	Tree* t = new Tree;
	listOfTrees.push_back (t);

	//add root node with label ROOT
	//it has no parent node
	Node* root = t->createNode ();
	root->setNodeLabel ("ROOT");
	t->mapNodes["ROOT"] = root;

	return t;
}

Tree* MySpecies::createTree (
		const Tree* t
		)
{
	Tree* newTree = new Tree (t);
	listOfTrees.push_back (newTree);

	return newTree;
}

Chain* MySpecies::getChain (
		const int& n
		) 
{
	return listOfChains.at(n);
}

const Chain* MySpecies::getChain (
		const int& n
		) const
{
	return listOfChains.at(n);
}

Tree* MySpecies::getTree (
		const int& n
		)
{
	return listOfTrees.at(n);
}

const Tree* MySpecies::getTree (
		const int& n
		) const
{ 
	return listOfTrees.at(n);
}

Part* MySpecies::getPart (
		const string& partLabel
		)
{
	for (int i=0; i < listOfChains.size (); i++)
	{
		Chain* c = listOfChains[i];
		Part* p = c->getPart (partLabel);
		if (p != NULL) return p;
	}
	return NULL;
}

const Part* MySpecies::getPart (
		const string& partLabel
		) const
{
	for (int i=0; i < listOfChains.size (); i++)
	{
		Chain* c = listOfChains[i];
		Part* p = c->getPart (partLabel);
		if (p != NULL) return p;
	}
	return NULL;
}

void MySpecies::setDB_ref (const string& ref) {
	reference_db = ref;
}

void MySpecies::setDB_Label (const string& label) {
	speciesLabel_db = label;
}

void MySpecies::setCompTypeId (const string& sid) {
	comp_type_id = sid;
}

string MySpecies::getDB_ref () const {
	return reference_db;
}

string MySpecies::getDB_Label () const {
	return speciesLabel_db;
}

string MySpecies::getCompTypeId () const {
	return comp_type_id;
}

void MySpecies::rearrange ()
{
	//sort chains
	if (!isRearranged)
	{
		for (int i =0; i < listOfChains.size (); i++)
			listOfChains[i]->genUnicode ();

		stable_sort (
				listOfChains.begin(), 
				listOfChains.end (),
				IsLess_c ()
				);

		//find equal chains
		findEquiv ();
		isRearranged = true;
	}

	//generate weight for leaf nodes
	for (int i=0; i<listOfChains.size(); i++)
	{
		Chain* c = listOfChains[i];
		for (int j=0; j<c->listOfParts.size (); j++)
		{
			Part* p = c->listOfParts[j];
			if (p->getIsBinded ())
			{
				string label = p->getPartLabel ();
				Node* n = findBindedNode (label);
				if (n) n->setNodeWeight (i,j);
			}
		}
	}

	//generate weight for all nodes
	//generate huffman code for all nodes
	for (int i=0; i < listOfTrees.size (); i++)
	{
		Tree* t = listOfTrees[i];
		t->genWeight ("ROOT");
		t->genHuffman ("ROOT");

		//sort listOfNodes
		stable_sort (
				t->listOfNodes.begin (), 
				t->listOfNodes.end (),
				IsLess_n ()
				);
	}

	//sort trees
	stable_sort (
			listOfTrees.begin(), 
			listOfTrees.end (),
			IsLess_t ()
			);

	//return
}

void MySpecies::partialDup (
		const set<int>& chainSaved,
		const set<string>& nodeSaved
		)
{
	//
	//  copy Chain* saved in chainSaved
	//
	vector<Chain*> listOfChains_new;
	listOfChains_new.reserve (chainSaved.size ());

	set<int>::iterator iter_s = chainSaved.begin ();
	for (int i=0; iter_s != chainSaved.end (); i++, iter_s++)
	{
		int cn = *iter_s;
		listOfChains_new.push_back (listOfChains[cn]);
		vector<Chain*>::iterator iter = listOfChains.begin () + cn;
		listOfChains.erase (iter);
	}

	for (int i =0; i <listOfChains.size (); i++) delete listOfChains[i];
	listOfChains.clear ();

	listOfChains = listOfChains_new;

	//
	//  copy Tree* by nodeSaved
	//
	for (int i=0; i<listOfTrees.size(); i++)
	{
		Tree* t = listOfTrees[i];
		for (int j=0; j< t->listOfNodes.size(); j++)
		{
			Node* n = t->getNode (j);
			if (!nodeSaved.count (n->getNodeLabel ())) 
			{
				delete t;
				vector<Tree*>::iterator iter = listOfTrees.begin () + i;
				listOfTrees.erase (iter);

				break;
			}
		}
	}

	isRearranged = false;
	rearrange ();
}

void MySpecies::Output () const
{
	cout << "\n------Begin (MySpeices)------" << endl;

	cout << "\nCHAINs (" << listOfChains.size () << "):" << endl;

	for (int cnt =0; cnt < listOfChains.size (); cnt++)
	{
		Chain* c = listOfChains[cnt];
		cout << "\nchain (" << cnt << ", " << c->chainLabel <<  ") :"; 
		c->Output (cout);
	}

	int numT = listOfTrees.size ();
	cout << "\n\nTREEs (" << numT << "):" << endl;

	for (int cnt =0; cnt < numT; cnt++)
	{
		cout << "\ntree " << cnt << " ( NODES = " 
			<< listOfTrees[cnt]->listOfNodes.size () 
			<< " ) : " ;
		listOfTrees[cnt]->Output (cout);
	}

	cout << "\n\n------End (MySpeices)------" << endl;
}

//
//	return true if two species has same CN strucuture,
//	they may not in the same compartment
//

bool MySpecies::equal (
		const MySpecies* rhs
		)  
{
	MySpecies* lhs = this;

	//compare chains
	if (lhs->listOfChains.size () != rhs->listOfChains.size ()) return false;
	else
	{
		for (int i=0; i < lhs->listOfChains.size (); i++)
		{
			Chain* left = lhs->listOfChains[i];
			Chain* right = rhs->listOfChains[i];
			//            cout << "\nleft = " << left->getUnicode () << 
			//                " right = " << right->getUnicode ()<< endl;
			if (!left->equal (right)) return false;
		}
	}

	//campare trees
	if (lhs->listOfTrees.size () != rhs->listOfTrees.size ()) return false;
	else
	{
		if (lhs->listOfTrees.size () == 0) return true;
		else
		{
			// (1) calculate and generate all permutations
			// (important! initialize permAll)
			int numPerm = 1;
			permType permAll (lhs->equiv.size());
			for (int i =0; i < lhs->equiv.size (); i++)
			{
				vector<int> perm;
				const pair <int, int>& eqv = lhs->equiv[i];
				for (int j = eqv.first; j <= eqv.second; j++) perm.push_back (j);

				//calculate full-array of numbers in perm
				Math::ordered_FullArray (perm, permAll[i]);
				numPerm *= (eqv.second-eqv.first+1);
			}

			for (int i = 0; i < numPerm; i++)
			{
				//permute equivalent chains to get a new chain order
				lhs->perm (i, permAll);

				//compare tree structure
				for (int j =0; j < lhs->listOfTrees.size (); j++)
				{
					Tree* left = lhs->listOfTrees[j];
					Tree* right = rhs->listOfTrees[j];
					if (left->equal (right)) return true;
				}
			}

			return false;
		}
	}
}

void MySpecies::findEquiv () 
{
	//clear if there are element left
	if (!equiv.empty ()) equiv.clear ();

	int i =0;
	while (i < listOfChains.size ()-1)
	{
		Chain* c1 = listOfChains[i];

		int offset = 1;
		do
		{
			int curp = i + offset;
			Chain* c2 = listOfChains[curp];

			if (&c1 == &c2) 
			{
				offset++;
				if (curp+1 == listOfChains.size ()) //last element
				{
					equiv.push_back (
							make_pair(i, listOfChains.size ()-1)
							);
					i = listOfChains.size ();
					break;
				}
			}
			else
			{
				if (offset > 1)
					equiv.push_back (make_pair(i, curp-1));
				i += offset;
				break;
			}
		} while (1);
	}
}

void MySpecies::perm (
		const int& i, 
		const permType& permAll
		) 
{
	// ith permutation
	// swap chains and modify chain node/weight relation
	int divide = i;
	for (int j = 0; j < equiv.size (); j++)
	{
		const markType& eqv = equiv[j];

		const vector<int>& permutedArray = 
			permAll[j][divide % permAll[j].size ()];

		//start permutation
		//elements in [first, last] have been copied into vector splice
		vector<Chain*>::iterator 
			first = listOfChains.begin () + eqv.first, 
				  last = listOfChains.begin () + eqv.second + 1;
		vector<Chain*> splice (first, last);

		//permute
		for (int perm = eqv.first; perm <= eqv.second; perm++) 
		{
			int pos = permutedArray[perm-eqv.first] - eqv.first;
			listOfChains[perm] = splice.at (pos);
		}

		divide /= permAll[j].size ();
	}

	//    based on  chain node/weight relation, 
	//    modify order of tree nodes
	rearrange ();

	//return
}

bool MySpecies::match (
		const MySpecies* s,
		vector<cMatchsType2>& trym
		) const
{
	cout << "\nSPECIES: MATCHING ......" << endl;

	//  template chain length
	int numc_t = s->listOfChains.size ();

	//  chain length to be matched
	int numc_m = listOfChains.size ();

	if (numc_t < numc_m) return false;

	//  temporary variables
	vector<cMatchsType> records (numc_t);
	vector<vi> chainNum (numc_t);

	//
	// for each chain in template species, we find all matchings
	// in this species, and records them
	//
	int permuteAll = 1;
	for (int i =0; i < numc_t; i++)
	{
		Chain* c1 = s->listOfChains[i];

		int found_all = 0;
		for (int j = 0; j < numc_m; j++)
		{
			listOfChains[j]->match (c1, records[i]);
			for (int k =0; k < records[i].size (); k++)
				chainNum[i].push_back (j);
			found_all += records[i].size ();
		}
		if (found_all == 0) return false; 
		else permuteAll *= found_all;
	}

	cout << "\npermuteAll = " << permuteAll;

	//
	//	Permutation
	//
	for (int i = 0; i < permuteAll; i++)
	{
		int divide = i;
		bool ok = true;

		//	same chains in this species could not be allowed 
		//            to match one chain in species s
		set <int> chainUsed;
		vector<cMatchType2> tryAssemble (numc_t);

		for (int j =0; j < numc_t; j++)
		{
			int indexperm = divide % records[j].size ();
			int chainnum = chainNum[j][indexperm];	// num of chain of this species

			if (chainUsed.count (chainnum)) {ok = false;break;}
			else 
			{
				tryAssemble.push_back (
						make_pair (records[j][indexperm],
							chainNum[j][indexperm])
						);

				chainUsed.insert (chainnum); 
			}
			divide /= records[j].size ();
		}

		if (!ok) continue;

		//
		//	if no trees, a successful match has been found
		//
		if (s->getNumOfTrees () > 0) 
		{
			//
			//  generate s1
			//
			MySpecies* s1 = new MySpecies (this);

			set<string> nodeSaved;
			for (int k=0; k < numc_t; k++)
			{
				Chain* c = s->listOfChains[k];
				cMatchType& cm_T = tryAssemble[k].first;
				int cn_m = tryAssemble[k].second;
				Chain* mc = listOfChains[cn_m];

				cMatchType::const_iterator iter_c = cm_T.begin ();
				for (int l=0; iter_c != cm_T.end (); l++, iter_c++)
				{
					Part* p = c->listOfParts[l];
					string ctg = p->getPartCtg ();
					if (ctg != "substituent")
					{
						int start = iter_c->first;
						int end = iter_c->second;
						assert (start == end);

						Part* mp = mc->getPart (start);
						if (mp->getIsBinded ()) 
							nodeSaved.insert (mp->getPartLabel ());
					}
				}
			}

			//
			//  rearrange operation will be done in DeleteAndSave
			//
			s1->partialDup (chainUsed, nodeSaved);


			//
			//  generate s2
			//
			MySpecies* s2 = new MySpecies;
			for (int k=0; k < numc_t; k++)
			{
				Chain* c = s->listOfChains[k];
				Chain* nc = s2->createChain ();

				cMatchType& cm_T = tryAssemble[k].first;
				int cn_m = tryAssemble[k].second;
				Chain* mc = listOfChains[cn_m];

				cMatchType::const_iterator iter_c = cm_T.begin ();
				for (int l=0; iter_c != cm_T.end (); l++, iter_c++)
				{
					Part* p = c->listOfParts[l];
					if (p->getPartCtg () == "substituent")
					{
						int start = iter_c->first;
						int end = iter_c->second;

						for (int r = start; r <= end; r++)
							nc->createPart (mc->getPart (r));
					}
					else nc->createPart (p); 
				}
			}

			for (int k=0; k < s->listOfTrees.size (); k++)
				s2->createTree (s->listOfTrees[k]);

			s2->rearrange ();

			if (s1->equal (s2)) 
			{
				/*
				cout << "\ns1 = " << endl;
				s1->Output ();
				cout << "\ns2 = " << endl;
				s2->Output ();
				*/

				trym.push_back (tryAssemble);
			}
			else
			{
				delete s1;
				delete s2;
			}
		}
		else
		{
			trym.push_back (tryAssemble);
		}
	}

	return !(trym.size () == 0);
}

void MySpecies::trim (bdbXMLInterface& dbreader)
{
	//	
	//	(1) leaf nodes that are not any site on chains,
	//		the tree will be erased and leaf nodes are 
	//		conformed to its original state
	//	(2) binded part could not find any leaf node in 
	//		trees, the part will also be conformed to 
	//		its original state

	//	search binded parts first
	map < string, pair<int,int> > bindsites;

	for (int i=0; i<listOfChains.size(); i++)
	{
		Chain* c = listOfChains[i];
		for (int j=0; j < c->listOfParts.size (); j++)
		{
			Part* p = c->listOfParts[j];
			if (p->getIsBinded ()) 
			{
				string partLabel = p->getPartLabel ();
				if (bindsites.count (partLabel)) throw StrCacuException (
						"Part Labels must be different in one species!"
						);
				else bindsites[partLabel] = make_pair (i,j);
			}
		}
	}

	//	trim
	for (int i=0; i <listOfTrees.size (); i++)
	{
		bool DelTree = false;
		Tree* t = listOfTrees[i];
		for (int j=0; j < t->listOfNodes.size (); j++)
		{
			Node* n = t->listOfNodes[j];
			if (n->isLeaf ())
			{
				string nodeLabel = n->getNodeLabel ();
				//	find nodeLabel in bindsites
				if (!bindsites.count (nodeLabel)) 
				{
					DelTree = true;
					break;
				}
			}
		}

		if (DelTree == false) continue;

		//	delete tree
		for (int j=0; j< t->listOfNodes.size (); j++)
		{
			Node* n = t->listOfNodes[j];
			if (n->isLeaf ())
			{
				string nodeLabel = n->getNodeLabel ();
				if (bindsites.count (nodeLabel))
				{
					int cn = bindsites[nodeLabel].first;
					int pn = bindsites[nodeLabel].second;

					assert (cn >= 0);
					assert (pn >= 0);

					Part* p = listOfChains[cn]->listOfParts[pn];

					//	change to its original conformation
					vector<string> tmp;
					const string doc = p->getPartRef ();
					string path ("/MoDeL/part/");
					path += p->getPartCtg () + "/@originalConformation";
					dbreader.get_node_attr (PART, &doc, &path, tmp);
					if (!tmp.empty ()) p->setPartRef (tmp[0]);
					p->setIsBinded (false);

					//	erase bindsites
					bindsites.erase (nodeLabel);
				}
			}
		}

		delete t;
		vector<Tree*>::iterator iter_tree = listOfTrees.begin () + i;
		listOfTrees.erase (iter_tree);
	}	

	map< string, pair<int,int> >::iterator first = bindsites.begin ();
	for (int i=0; first != bindsites.end (); i++, first++)
	{
		int cn = first->second.first;
		int pn = first->second.second;

		assert (cn >= 0);
		assert (pn >= 0);

		Part* p = listOfChains[cn]->listOfParts[pn];

		//	change to its original conformation
		vector<string> tmp;
		const string doc = p->getPartRef ();
		string path ("/MoDeL/part/");
		path += p->getPartCtg () + "/@originalConformation";
		dbreader.get_node_attr (PART, &doc, &path, tmp);
		if (!tmp.empty ()) p->setPartRef (tmp[0]);
		p->setIsBinded (false);
	}

	//	rearrange
	rearrange ();
}

void MySpecies::genUniqueLabel (const int& i)
{
	ostringstream oss;

	for (int i=0; i<listOfChains.size (); i++)
	{
		oss.str ("");
		oss << speciesLabel_db << "[cHaIn" << i << "]";
		listOfChains[i]->chainLabel = oss.str ();
	} 
}

