#include "myspecies.h"

MySpecies::MySpecies () :
	Species (2,4)
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
	equiv (orig->equiv)
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
	trim (&dbreader);

	cout << "\n!!!	--	--	--	--	!!!\n";
	cout << "\nspecies after trim	=	 "  << endl;
	Output ();

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

	for (int i=0; i<pieces.size (); i++) pieces[i]->rearrange ();
}

const Node* MySpecies::findBindedNode (
		const string& label
		) const 
{
	for (int i= 0; i<listOfTrees.size(); i++)
	{
		Node* n = listOfTrees[i]->getNode (label);
		if (n) return n;
	}
	return 0;
}

Node* MySpecies::findBindedNode (
		const string& label
		) 
{
	for (int i= 0; i<listOfTrees.size(); i++)
	{
		Node* n = listOfTrees[i]->getNode (label);
		if (n) return n;
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
	if (n >=0 && n < listOfChains.size ()) 
		return listOfChains[n];
	else return NULL;
}

const Chain* MySpecies::getChain (
		const int& n
		) const
{
	if (n >=0 && n < listOfChains.size ()) 
		return listOfChains[n];
	else return NULL;
}

Tree* MySpecies::getTree (
		const int& n
		)
{
	if (n >=0 && n < listOfTrees.size ())
		return listOfTrees[n];
	else return NULL;
}

const Tree* MySpecies::getTree (
		const int& n
		) const
{ 
	if (n >=0 && n < listOfTrees.size ())
		return listOfTrees[n];
	else return NULL;
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
	//	sort chains
	for (int i =0; i < listOfChains.size (); i++)
		listOfChains[i]->genUnicode ();

	stable_sort (
			listOfChains.begin(), 
			listOfChains.end (),
			IsLess_c ()
			);

	for (int i=0; i < listOfChains.size (); i++)
		listOfChains[i]->chainNum = i;


	//	find equal chains
	vector<markType> psEquiv; 
	findEquiv (psEquiv);

	// (1) calculate and generate all permutations
	// (important! initialize permAll)
	int numPerm = 1;
	permType permAll (psEquiv.size());
	for (int i =0; i < psEquiv.size (); i++)
	{
		vector<int> perm;
		const markType& eqv = psEquiv[i];
		for (int j = eqv.first; j <= eqv.second; j++) perm.push_back (j);

		//calculate full-array of numbers in perm
		Math::ordered_FullArray (perm, permAll[i]);
		numPerm *= (eqv.second-eqv.first+1);
	}

	/**
	 * iterate all permutations, and 
	 * find those with minimum tree unicode
	 */

	vector< vector<int> > minWperm;
	for (int i = 0; i < numPerm; i++)
	{
		//	permute equivalent chains
		vector<int> order;
		perm (i, psEquiv, permAll, order);

		//	generate weight for leaf nodes
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

		//	generate weight for all nodes
		for (int i=0; i<listOfTrees.size (); i++) 
		{
			Tree* t = listOfTrees[i];
			t->genWeight ("ROOT");
			stable_sort (
					t->listOfNodes.begin (), 
					t->listOfNodes.end (),
					IsLess_n ()
					);
		}

		//	sort trees
		stable_sort (
				listOfTrees.begin(), 
				listOfTrees.end (), 
				IsLess_t ()
				);

		//	generate huffman code for all nodes
		//	create a unique tree code 
		
		string tryuni;
		for (int i=0; i < listOfTrees.size (); i++)
		{
			Tree* t = listOfTrees[i];
			t->genHuffman ("ROOT");
			t->genUnicode ();
			tryuni += t->unicode;
		}

		if (minW.empty ()) 
		{
			minW = tryuni;
			minWperm.push_back (order);
		}
		else if (minW > tryuni)
		{
			minW = tryuni;
			minWperm.clear ();
			minWperm.push_back (order);
		}
		else if (minW == tryuni)
		{
			minWperm.push_back (order);
		}

		//	recover to orginal order
		stable_sort (
				listOfChains.begin(), 
				listOfChains.end (),
				IsLess_no ()
				);
	}

	//	find equivalent chains
	for (int i=0; i < minWperm.size (); i++)
	{
		const vector<int>& elem_i = minWperm[i]; 
		for (int j=i+1; j < minWperm.size (); j++)
		{
			const vector<int>& elem_j = minWperm[j];
			
			//	for each (i,j) pair, find equivalent chains
			int found_i = -1;
			int found_j = -1;
			for (int k=0; k < equiv.size (); k++)
			{
				if (equiv[k].count (i)) {found_i = k;}
				if (equiv[k].count (j)) {found_i = j;}
				if (found_i != -1 && found_j != -1) break;
			}

			if (found_i == -1 && found_j == -1)
			{
				set<int> newequiv;
				newequiv.insert (i);
				newequiv.insert (j);
				equiv.push_back (newequiv);
			}
			
			if (found_i != -1 && found_j == -1) equiv[found_i].insert (j);
			if (found_i == -1 && found_j != -1) equiv[found_j].insert (i);

			if (found_i != -1 && found_j != -1 && found_i != found_j)
			{
				//	merge set found_i and found_j
				set<int>::iterator iterf = equiv[found_j].begin ();
				while (iterf != equiv[found_j].end ()) equiv[found_i].insert (*iterf++);
				equiv.erase (equiv.begin () + found_j);
			}
		}
	}
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

	//	compare chains
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

	//	compare minimum forest weight 
	return minW == rhs->minW;
}

void MySpecies::findEquiv (vector<markType>& psEquiv) const 
{
	int i =0;
	while (i+1 < listOfChains.size ())
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
					i = listOfChains.size ();
					psEquiv.push_back (make_pair(i, listOfChains.size ()-1));
					break;
				}
			}
			else
			{
				if (offset > 1)
					psEquiv.push_back (make_pair(i, curp-1));
				i += offset;
				break;
			}
		} while (1);
	}
}

void MySpecies::perm (
		const int& i, 
		const vector<markType>& psEquiv,
		const permType& permAll,
		vector<int>& order
		) 
{
	//	ith permutation
	// 	swap chains and modify chain node/weight relation
	int divide = i;
	for (int j = 0; j < psEquiv.size (); j++)
	{
		const markType& eqv = psEquiv[j];
		const vector<int>& permutedArray = 
			permAll[j][divide % permAll[j].size ()];

		//	start permutation
		//	elements in [first, last] have been copied into vector splice
		vector<Chain*>::iterator 
			first = listOfChains.begin () + eqv.first, 
				  last = listOfChains.begin () + eqv.second + 1;
		vector<Chain*> splice (first, last);

		//	permute
		for (int perm = eqv.first; perm <= eqv.second; perm++) 
		{
			int pos = permutedArray[perm-eqv.first] - eqv.first;
			listOfChains[perm] = splice.at (pos);
		}

		//	record the order
		for (int k=0; k < permutedArray.size (); k++)
			order.push_back (permutedArray[k]);

		divide /= permAll[j].size ();
	}
}

void MySpecies::addPrefix (const string& prefix)
{
	for (int i=0; i<listOfChains.size (); i++) 
		listOfChains[i]->__add_chain_prefix (prefix);
	for (int i=0; i<listOfTrees.size (); i++)
		listOfTrees[i]->__add_tree_prefix (prefix);
}

bool MySpecies::match (
		const MySpecies* s,
		vector<cMatchsType2>& trym
		) const
{
	cout << "\n------------------------------------------------";
	cout << "\n#############	   CHECK SPECIES MATCH		^_!";
	cout << "\n------------------------------------------------\n"; 


	int numc_t = s->listOfChains.size (); //template chain length
	int numc_m = listOfChains.size (); //length of this chain
	if (numc_m < numc_t) return false;

	//  temporary variables
	int permuteAll = 1;
	cMatchsArray records;

	//
	// for each chain in template species, we find all matchings
	// in this species, and records them
	//
	
	//	for chains with same unicode, we only need to find
	//	matchings for one of them
	map<string, int> uniMap;

	for (int i =0; i < numc_t; i++)
	{
		cout << "\n\ntry template pattern	"
			 << "--	..	--	" << i << endl;
		
		Chain* c1 = s->listOfChains[i];
		if (!uniMap.count (c1->unicode))
		{
			cMatchsType2 record;
			for (int j = 0; j < numc_m; j++)
			{
				cout << "\nchain number in current species"
					<< "	--	..	--	" << j << endl;

				cMatchsType record2;
				listOfChains[j]->match (c1, record2);

				for (int k =0; k < record2.size (); k++)
					record.push_back (make_pair(record2[k], j));
			}

			if (record.size () == 0) return false; 
			else 
			{
				records.push_back (record);		
				uniMap.insert (make_pair(c1->unicode, i));
			}
		}
		else records.push_back (records[uniMap[c1->unicode]]);
		permuteAll *= records.back ().size ();
	}

	//
	//	Permutation
	//
	set< vector< set<int> > > repeatRemove;
	for (int i = 0; i < permuteAll; i++)
	{
		int divide = i;
		bool ok = true;

		//	same chains in this species could not be allowed 
		//            to match one chain in species s

		//	cMatchType2 only records details of one chain match
		//	and vector<cMatchType2> have a complete set of chain match
		
		set <int> chainUsed;
		cMatchsType2 tryAssemble;

		for (int j =0; j < numc_t; j++)
		{
			int indexperm = divide % records[j].size ();
			int chainnum = records[j][indexperm].second;

			if (chainUsed.count (chainnum)) {ok = false;break;}
			else 
			{
				chainUsed.insert (chainnum); 
				tryAssemble.push_back (records[j][indexperm]);
			}
			divide /= records[j].size ();
		}
		if (!ok) continue;

		vector< set<int> > equivck;
		for (int j=0; j < s->equiv.size (); j++)
		{
			const set<int>& equivset = equiv[j];

			set<int> tmp;
			set<int>::const_iterator iter = equivset.begin ();
			while (iter != equivset.end ())
				tmp.insert (tryAssemble[*iter++].second);
			equivck.push_back (tmp);
		}

		/**
		 * check if this permutation has been added
		 */
		if (repeatRemove.count (equivck)) continue;
		else repeatRemove.insert (equivck);

		//
		//	if no trees, a successful match has been found
		//
		if (s->getNumOfTrees () > 0) 
		{
			//	============
			//	generate lhs
			//	============
			MySpecies* lhs = new MySpecies;
			
			//	copy chains that are matched
			for (int j=0; j<numc_t; j++) lhs->createChain (listOfChains[tryAssemble[j].second]);
			for (int j=0; j<listOfTrees.size (); j++) lhs->createTree (listOfTrees[j]);
			lhs->addPrefix ("__MoDeL_CXX_1::");	//	add a prefix to all partLabel and nodeLabel

			//	============
			//	generate rhs
			//	============
			MySpecies* rhs = new MySpecies (s);
			rhs->addPrefix ("__MoDeL_CXX_2::");

			//	generate new chain to replace
			for (int j=0; j<numc_t; j++)
			{
				//	replace chain with a new generated one
				Chain* __matched = lhs->getChain (j);
				Chain* __template = rhs->listOfChains[j];
				Chain* __replace = new Chain;

				const cMatchType& detail = tryAssemble[j].first;
				cMatchType::const_iterator iter_c = detail.begin ();
				assert (detail.size () == __template->listOfParts.size ());

				for (int k=0; iter_c != detail.end ();k++, iter_c++)
				{
					Part* p = __template->listOfParts[k];
					if (p->getPartCtg () == "substituent")
					{
						int start = iter_c->first;
						int end = iter_c->second;

						for (int l=start; l <= end; l++) 
							__replace->createPart (__matched->getPart (l));
					}
					else __replace->createPart (p); 
				}

				//	update
				rhs->listOfChains[j] = __replace;
				delete __template;
			}

			//	copy trees as well
			for (int j=0; j<listOfTrees.size (); j++) rhs->createTree (listOfTrees[j]);

			//	trim both species
			lhs->trim (); rhs->trim ();

			if (lhs->equal (rhs)) trym.push_back (tryAssemble);
			delete lhs;	delete rhs;
		}
		else trym.push_back (tryAssemble);
	}

	return !(trym.size () == 0);
}

void MySpecies::trim (bdbXMLInterface* dbreader)
{
	//	
	//	(1) leaf nodes that are not any site on chains,
	//		the tree will be erased and leaf nodes are 
	//		conformed to its original state
	//	(2) binded part could not find any leaf node in 
	//		trees, the part will also be conformed to 
	//		its original state

	//	search binded parts first (part with isBinded attribute: true)
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
	
	//	trim condition 1
	
	/**
	 * if label of leaf nodes in trees could not be found in all
	 * parts with isBinded attribute, then this tree will be removed
	 */

	for (int i=0; i <listOfTrees.size ();)
	{
		//	find if there are leaf nodes that are not in bindsites set
		//	if any, then remove this tree

		//	however, it all node labels could be found in the set,
		//	then all of them should be removed
		set<string> nodes;

		//	finding...	
		bool DelTree = false;
		Tree* t = listOfTrees[i];
		for (int j=0; j < t->listOfNodes.size (); j++)
		{
			Node* n = t->listOfNodes[j];
			if (n->isLeaf ())
			{
				string nodeLabel = n->getNodeLabel ();
				//	find nodeLabel in bindsites
				if (!bindsites.count (nodeLabel)) {
					DelTree = true; break;
				}
				else nodes.insert (nodeLabel);
			}
		}

		if (DelTree == false) 
		{
			set<string>::iterator iter = nodes.begin ();
			while (iter != nodes.end ()) bindsites.erase (*iter++);
			i++;
		}
		else
		{
//            cout << "\n<!!!	---	---	---	DELETE TREE	---	---	---\n";

			//
			//	delete tree
			//	if dbreader != NULL, then 
			//	restore original conformation of binded parts
			//	
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

						if (dbreader != NULL)
						{
							//	change to its original conformation
							vector<string> tmp;
							const string doc = p->getPartRef ();
							string path ("/MoDeL/part/");
							path += p->getPartCtg () + "/@originalConformation";
							dbreader->get_node_attr (PART, &doc, &path, tmp);
							if (!tmp.empty ()) p->setPartRef (tmp[0]);
						}
						p->setIsBinded (false);

						//	erase bindsites
						bindsites.erase (nodeLabel);
					}
				}
			}

			listOfTrees.erase (listOfTrees.begin ()+i);
			delete t;

		}
	}	


//     trim condition 2
//	if labels in the set could not be mapped to any node in the tree
//	it will also be replaced by its original conformation
	
	map< string, pair<int,int> >::iterator first = bindsites.begin ();
	for (int i=0; first != bindsites.end (); i++, first++)
	{
		int cn = first->second.first;
		int pn = first->second.second;

		assert (cn >= 0);
		assert (pn >= 0);

		Part* p = listOfChains[cn]->listOfParts[pn];

		if (dbreader != NULL)
		{
			//	change to its original conformation
			vector<string> tmp;
			const string doc = p->getPartRef ();
			string path ("/MoDeL/part/");
			path += p->getPartCtg () + "/@originalConformation";
			dbreader->get_node_attr (PART, &doc, &path, tmp);
			if (!tmp.empty ()) p->setPartRef (tmp[0]);
		}
		p->setIsBinded (false);
	}

	rearrange ();
}

