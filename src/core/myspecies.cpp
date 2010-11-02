#include "myspecies.h"
#include "DebugOut.h"

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
	equiv (orig->equiv),
	minW (orig->minW)
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

bool MySpecies::isCompartment () const
{
	return !comp_type_id.empty ();
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

//    debugOut() << "\nspecies after trim	=	 "  << endl;
//    Output ();

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
			if (chainUsed[j].count (i)) {found = true;break;}
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

	for (int i=0; i<pieces.size (); i++) pieces[i]->rearrange (false);
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

void MySpecies::rearrange (const bool& isTemplate)
{
//    debugOut() << "\n--------rearrange species structure...--------"<<endl;

	//	minW must be cleared!!!!
	minW.clear ();
	equiv.clear ();

	//	start

	int symmstate = 1;
	bool* csymm = new bool[listOfChains.size ()];
	for (int i = 0; i < listOfChains.size (); i++)
	{
		Chain* c = listOfChains[i];

		if (!isTemplate)
		{
			csymm[i] = c->isCsymm ();
			if (csymm[i]) symmstate *= 2;
		}
		else 
		{
			csymm[i] = false;
			c->unicode = c->genUnicode (
					0, c->listOfParts.size ()-1, true
					);
		}
	}

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

	//    debugOut() << "\npsEquiv = " << psEquiv.size () << endl;
	//    for (int i=0; i<psEquiv.size (); i++)
	//        debugOut() << "\n(first = " << psEquiv[i].first
	//             << ", second = " << psEquiv[i].second
	//             << ")";

	// (1) calculate and generate all permutations
	// (important! initialize permAll)
	int numPerm = 1;
	permType permAll;
	for (int i =0; i < psEquiv.size (); i++)
	{
		vector<int> perm;
		const markType& eqv = psEquiv[i];
		for (int j = eqv.first; j <= eqv.second; j++) perm.push_back (j);
		//        debugOut() << "\neqv.first = " << eqv.first << " eqv.second = " << eqv.second << endl;
		//        debugOut() << "\nperm.size = " << perm.size () << endl;

		//calculate full-array of numbers in perm
		vector< vector<int> > tmp_perm;
		Math::ordered_FullArray (perm, tmp_perm);

		/*
		   for (int j=0; j < tmp_perm.size (); j++)
		   {
		   debugOut() << "\n\n";
		   assert (tmp_perm[j].size () == perm.size ());
		   for (int k = 0; k < tmp_perm[j].size (); k++)
		   {
		   debugOut() << tmp_perm[j][k] << " ";
		   }
		   }
		   */

		permAll.push_back (tmp_perm);

		//        debugOut() << "\npermAll = " << permAll[i].size () << endl;
		numPerm *= permAll[i].size ();
	}
	assert (permAll.size () == psEquiv.size ());

	/**
	 * iterate all permutations, and 
	 * find those with minimum tree unicode
	 */

	vector< vector<int> > minWperm;
	vector< bool > turnstate;

	for (int i=0; i < symmstate; i++)
	{
		vector<bool> tmpstate;
		if (!isTemplate)
		{
			int divide = i;
			for (int j = 0; j < listOfChains.size (); j++)
			{
				if (csymm[j]) 
				{
					tmpstate.push_back (static_cast<bool> (divide % 2));
					if (tmpstate[j]) listOfChains[j]->turnover ();
					divide /= 2;
				}
				else tmpstate.push_back (false);
			}
		}
		else tmpstate = vector<bool> (listOfChains.size (), false);

		for (int j=0; j < numPerm; j++)
		{
			//	permute equal chains
			vector<int> order;

			try
			{
				perm (j, psEquiv, permAll, order);
			}
			catch (std::out_of_range &e)
			{
				cerr << e.what () << "	out_of_range in function perm!\n";
				throw;
			}

			//	generate weight for leaf nodes
			for (int k=0; k<listOfChains.size(); k++)
			{
				Chain* c = listOfChains[k];
				for (int l=0; l<c->listOfParts.size (); l++)
				{
					Part* p = c->listOfParts[l];
					if (p->getIsBinded ())
					{
						string label = p->getPartLabel ();
						Node* n = findBindedNode (label);
						if (n) n->setNodeWeight (k,l);
					}
				}
			}

			//	generate weight for all nodes
			for (int k=0; k<listOfTrees.size (); k++) 
			{
				Tree* t = listOfTrees[k];
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
			for (int k=0; k < listOfTrees.size (); k++)
			{
				Tree* t = listOfTrees[k];
				t->genHuffman ("ROOT");
				t->genUnicode ();
				tryuni += t->unicode;
			}

			if (minW.empty ()) 
			{
				minW = tryuni;
				minWperm.push_back (order);
				turnstate= tmpstate;
			}
			else if (minW > tryuni)
			{
				minW = tryuni;
				minWperm.clear ();
				minWperm.push_back (order);
				turnstate = tmpstate;
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

			//	recover to original direction
			if (!isTemplate)
			{
				for (int k=0; k < listOfChains.size (); k++)
					if (tmpstate[k]) listOfChains[k]->turnover ();
			}
		}
	}

	//	set unique turn state
	//    debugOut() << "\nistemplate = " << isTemplate 
	//         << " chainsize == " << listOfChains.size () 
	//         << " turnsize = " <<turnstate.size () 
	//         << endl;

	if (!isTemplate)
	{
		for (int i=0; i < listOfChains.size (); i++)
			if (turnstate[i]) listOfChains[i]->turnover ();
	}

	/**
	 * BE CAREFUL! TREES MUST BE CONSISTENT WITH
	 * CHAIN ORDER, SO REWEIGHTING TREE NODES ARE NECESSARY
	 */

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

	for (int i=0; i < listOfTrees.size (); i++)
	{
		Tree* t = listOfTrees[i];
		t->genHuffman ("ROOT");
		t->genUnicode ();
	}

	/**
	 * FIND EQUIVALENT CHAINS
	 */
	for (int i=0; i < minWperm.size (); i++)
	{
		const vector<int>& elem_i = minWperm[i]; 
		for (int j=i+1; j < minWperm.size (); j++)
		{
			const vector<int>& elem_j = minWperm[j];

			assert (elem_i.size () == elem_j.size ());
			//            debugOut() << "\noutput_equivalent_info:" << endl;
			//            debugOut() << "\ni = " << i << " j = " << j << endl;

			for (int m=0; m < elem_i.size (); m++)
			{
				//                debugOut() << elem_i[m] << " " << elem_j[m] << endl;	

				if (elem_i[m] == elem_j[m]) continue;

				//	for each (i,j) pair, find equivalent chains
				int found_i = -1;
				int found_j = -1;
				for (int k=0; k < equiv.size (); k++)
				{
					if (equiv[k].count (elem_i[m])) {found_i = k;}
					if (equiv[k].count (elem_j[m])) {found_j = k;}
					if (found_i != -1 && found_j != -1) break;
				}

				//                debugOut() << "\nfound_i = " << found_i << " found_j = " << found_j << endl;
				if (found_i == -1 && found_j == -1)
				{
					set<int> newequiv;
					newequiv.insert (elem_i[m]);
					newequiv.insert (elem_j[m]);
					equiv.push_back (newequiv);
				}
				else if (found_i != -1 && found_j == -1) equiv[found_i].insert (elem_j[m]);
				else if (found_i == -1 && found_j != -1) equiv[found_j].insert (elem_i[m]);
				else if (found_i != -1 && found_j != -1 && found_i != found_j)
				{
					//	merge set found_i and found_j
					set<int>::iterator iterf = equiv[found_j].begin ();
					while (iterf != equiv[found_j].end ()) equiv[found_i].insert (*iterf++);
					equiv.erase (equiv.begin () + found_j);
				}

				//                debugOut() << "\nnow equivalent group number = " << equiv.size () << endl;
			}

		}
	}

//    debugOut() << "\nnumber of equivalent chain groups = " << equiv.size () << endl;
//    for (int i=0; i < equiv.size (); i++)
//    {
//        set<int>::iterator it = equiv[i].begin ();
//        while (it != equiv[i].end ()) debugOut() << *it++;
//        debugOut() << "	";
//    }

	delete [] csymm;
}

void MySpecies::Output (ofstream& ofs) const
{
	ofs << "\n------Begin (MySpeices)------" << endl;
	ofs << "\nCHAINs (" << listOfChains.size () << "):" << endl;

	for (int cnt =0; cnt < listOfChains.size (); cnt++)
	{
		Chain* c = listOfChains[cnt];
		ofs << "\nchain (" << cnt << ", " << c->chainLabel <<  ") :"; 
		c->Output (ofs);
	}

	int numT = listOfTrees.size ();
	ofs << "\n\nTREEs (" << numT << "):" << endl;

	for (int cnt =0; cnt < numT; cnt++)
	{
		ofs << "\ntree " << cnt << " ( NODES = " 
			<< listOfTrees[cnt]->listOfNodes.size () 
			<< " ) : " ;
		listOfTrees[cnt]->Output (ofs);
	}

	ofs << "\n\n------End (MySpeices)------" << endl;
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
			//            debugOut() << "\nleft = " << left->getUnicode () << 
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

			//            if (&c1 == &c2) 
			if (c1->unicode == c2->unicode)
			{
				//                debugOut() << "\nc1 = " << c1->unicode 
				//                     << endl << " c2 = " << c2->unicode 
				//                     << endl;

				//                debugOut() << "\ncurp = " << curp << " size = " << listOfChains.size ();

				offset++;
				if (curp+1 == listOfChains.size ()) //last element
				{
					psEquiv.push_back (make_pair(i, listOfChains.size ()-1));
					i = listOfChains.size ();
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
		//        debugOut() << "\nxml = " << j << endl;

		const markType& eqv = psEquiv[j];
		const vector<int>& permutedArray = 
			permAll[j][divide % permAll[j].size ()];

		//	start permutation
		//	elements in [first, last] have been copied into vector splice
		vector<Chain*>::iterator 
			first = listOfChains.begin () + eqv.first, 
				  last = listOfChains.begin () + eqv.second + 1;
		vector<Chain*> splice (first, last);
		assert (splice.size () == eqv.second-eqv.first+1);

		//        debugOut() << "\nxml2 = " << j << endl;
		//	permute
		for (int perm = eqv.first; perm <= eqv.second; perm++) 
		{
			int pos = permutedArray.at (perm-eqv.first) - eqv.first;
			listOfChains.at (perm) = splice.at (pos);
		}

		//        debugOut() << "\nxml3 = " << j << endl;

		//	record the order
		for (int k=0; k < permutedArray.size (); k++)
			order.push_back (permutedArray.at(k));

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
	debugOut() << "\n------------------------------------------------";
	debugOut() << "\n#############	   CHECK SPECIES MATCH		^_!";
	debugOut() << "\n------------------------------------------------\n"; 


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

	//	test
	int count_as_equiv_remove = 0;

	for (int i =0; i < numc_t; i++)
	{
		debugOut() << "\n\ntry template pattern	"
			<< "--	..	--	" << i;

		Chain* c1 = s->listOfChains[i];
		if (!uniMap.count (c1->unicode))
		{
			cMatchsType2 record;
			for (int j = 0; j < numc_m; j++)
			{
				/**************************************************************
				//	important bug!
				//	for dilution reactions, one reaction may be found
				//	more than once, thus we add constraints on the matching of
				//	the species "any_species"
				//
				//	liaochen modified on 2010-10-27
				**************************************************************/
				if (s->reference_db == "any_species" && j!=0) break;

				cMatchsType record2;
				listOfChains[j]->match (c1, record2);

				for (int k =0; k < record2.size (); k++)
					record.push_back (make_pair(record2[k], j));
			}

			if (s->reference_db == "any_species")
			{
				cout << "\nany_species ? " << "yes" << endl;
				assert (record.size() == 1);
			}

			debugOut() << "found =  " << record.size ();


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

	cout << "\npermuteAll = " << permuteAll << endl;

	//
	//	Permutation
	//
//    set< vector< set<int> > > repeatRemove;
	typedef pair< 
		vector< cMatchType2 >, 
		vector< set<cMatchType2> >
			> removePair;
	typedef set<removePair> removeT; 
	
	removeT repeatRemove;

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

		/**
		 * important bug: some matchings are incorrect discarded!
		 * fixed by liaochen, 2010-10-26
		 */
		
		/*
		vector< set<int> > equivck;
		for (int j=0; j < s->equiv.size (); j++)
		{
			const set<int>& equivset = s->equiv[j];

			set<int> tmp;
			set<int>::const_iterator iter = equivset.begin ();
			while (iter != equivset.end ())
				tmp.insert (tryAssemble[*iter++].second);
			equivck.push_back (tmp);
		}
		*/
		
		set<int> chains_used;
		vector< set<cMatchType2> > equivck;
		vector<cMatchType2> usualck;

		//set equivck
		for (int j=0; j < s->equiv.size (); j++)
		{
			const set<int>& equivset = s->equiv[j];

			set<cMatchType2> tmp;
			set<int>::const_iterator iter = equivset.begin ();
			while (iter != equivset.end ())
			{
				tmp.insert (tryAssemble[*iter]);
				chains_used.insert (*iter);
				iter ++;
			}
			equivck.push_back (tmp);
		}

		//set usualck
		for (int j= 0; j < numc_t; j++)
		{
			if (!chains_used.count (j)) 
				usualck.push_back (tryAssemble[j]);
		}

		removePair _tmp_remove = make_pair (usualck, equivck);

		/**
		 * check if this permutation has been added
		 */
//        if (repeatRemove.count (equivck)) continue;
//        else {repeatRemove.insert (equivck); count_as_equiv_remove++;}
			
		if (repeatRemove.count (_tmp_remove)) continue;
		else {repeatRemove.insert (_tmp_remove); count_as_equiv_remove++;}

//        cout << "\nmatching ordering ..." << endl;
//        for (int j=0; j < numc_t; j++)
//        {
//            cout <<"(" << j << ", " << tryAssemble[j].second << ") ";
//        }
//        cout << endl;
		//
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
			//	liaochen modifies on 2010-11-26
			for (int j=0; j< lhs->listOfTrees.size (); j++) rhs->createTree (lhs->listOfTrees[j]);

			//	trim both species
			lhs->trim (); rhs->trim ();

			if (lhs->equal (rhs)) {cout << "\nyes!" << endl; trym.push_back (tryAssemble);}
			delete lhs;	delete rhs;
		}
		else {count_as_equiv_remove++; trym.push_back (tryAssemble);}
	}
	cout << "\ncount_as_equiv_remove = " << count_as_equiv_remove << endl;
	cout << "\trym_size = " << trym.size () << endl;

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
				if (bindsites.count (partLabel)) throw CoreException (
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
			//            debugOut() << "\n<!!!	---	---	---	DELETE TREE	---	---	---\n";

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

	rearrange (false);
}

void MySpecies::display_name (const int& num)
{
	ostringstream oss1;
	oss1 << num;
	string name (oss1.str ());
	name += ":";

	set<int> skip;

//    debugOut() << "\noutput_test" << endl;
//    Output ();
//    debugOut() << "\nequivalent chains groups = " << equiv.size () << endl;
//    for (int i=0; i < equiv.size (); i++)
//    {
//        set<int>::iterator it = equiv[i].begin ();
//        while (it != equiv[i].end ()) debugOut() << *it++;
//        debugOut() << endl;
//    }

	for (int i=0; i < listOfChains.size (); i++)
	{
		if (skip.count (i)) continue;

		int times = 0;
		for (int j=0; j < equiv.size (); j++)
		{
			if (equiv[j].count (i)) 
			{
				times = equiv[j].size ();
				set<int>::iterator it = equiv[j].begin ();
				while (it != equiv[j].end ()) skip.insert (*it++);
				break;
			}
		}

		Chain* c = listOfChains[i];
		ostringstream oss;

		if (times != 0) name += "(";

		//	DNA
		if (c->isDNA) 
		{
			if (times != 0)
			{
				oss.str ("");
				oss << "DNA)" << times << ";";
				name += oss.str ();
			}
			else name += "DNA;";
		}
		else if (c->isRNA) 
		{
			if (times != 0) 
			{
				oss.str ("");
				oss << "RNA)" << times << ";";
				name += oss.str ();
			}
			else name += "RNA;";
		}
		else
		{
			string name1 ("");
			for (int j=0; j < c->listOfParts.size (); j++)
			{
				name1 += c->listOfParts[j]->getPartRef ()+ "-";
			}
			name1 = name1.substr (0, name1.size ()-1);

			if (times != 0)
			{
				oss.str ("");
				oss << name1 << ")" << times << ";";
				name += oss.str ();
			}
			else name += name1 + ";";
		}
	}

	name = name.substr (0, name.size ()-1);
	setName (name);
}
