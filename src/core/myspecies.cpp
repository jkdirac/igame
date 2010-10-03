#include "myspecies.h"

	MySpecies::MySpecies () 
:Species (2,4), isRearranged (false)
{}

MySpecies::MySpecies (
		const MySpecies* orig
		): 
	dbId (orig->dbId),
	isRearranged (orig->isRearranged),
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
		vector<MySpecies*>& pieces
		)
{
	//rearrange species
	rearrange ();

	//container to store chainnum of species
	vector< set<int> > cU;

	int numT = listOfTrees.size ();
	for (int cnt =0; cnt < numT; cnt++)
	{
		Tree* t = listOfTrees[cnt];

		//int not species associated, found = -1,
		//else found = species index in cU;
		int found = -1;
		bool exit = false;

		//search leaf nodes
		int numN = t->listOfNodes.size ();
		for (int cnt2 =0; cnt2 < numN; cnt2++)
		{
			Node* n = t->getNode (cnt2);
			if (n->isLeaf ())
			{
				int chainnum = n->getNodeWeight ().first;

				//search for species added if this chainnum
				//has been added yet
				int numV = cU.size ();
				for (int cnt3 =0; cnt3 < numV; cnt3++)
				{
					if (cU[cnt3].count (chainnum)) 
					{
						found = cnt3;
						exit = true;
						break;
					}
				}
			}

			if (exit) break;
		}

		//if found = -1; create new species
		//containing this tree and associated chains
		//if found >=0; merge this tree and associated 
		//chains to that species
		if (found == -1)
		{
			MySpecies* s = new MySpecies ();

			bool GENok = true;
			set <int> cU1;

			//add tree
			s->createTree (t);

			//add associated chains
			int numN = t->listOfNodes.size ();
			for (int cnt2 =0; cnt2 < numN; cnt2++)
			{
				Node* n = t->getNode (cnt2);
				if (n->isLeaf ())
				{
					int chainnum = n->getNodeWeight ().first;
					if (chainnum == -1)
					{
						GENok = false;
						break;
					}
					else
					{
						s->createChain (listOfChains[chainnum]);
						cU1.insert (chainnum);
					}
				}
			}

			if (!GENok) delete s;
			else
			{
				pieces.push_back (s);
				cU.push_back (cU1);
			}
		}
		else
		{
			//merge
			MySpecies* s = pieces[found];

			bool GENok = true;
			set<int> cU1;

			//add tree
			s->createTree (t);

			//add associated chains
			int numN = t->listOfNodes.size ();
			for (int cnt2 =0; cnt2 < numN; cnt2++)
			{
				Node* n = t->getNode (cnt2);
				if (n->isLeaf ())
				{
					int chainnum = n->getNodeWeight ().first;
					if (chainnum == -1)
					{
						GENok = false;
						break;
					}
					else
					{
						s->createChain (listOfChains[chainnum]);
						cU1.insert (chainnum);
					}
				}
			}

			if (GENok)
			{
				s->createTree (t);

				set<int>::const_iterator itset =  cU1.begin ();
				while (itset != cU1.end ()) cU[found].insert (*itset++);
			}
		}

		//merge over, go to next tree
	}

	//rearrange all species
	for (int cnt =0; cnt < pieces.size (); cnt++)
		pieces[cnt]->rearrange ();
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
	Chain* newChain = new Chain;
	listOfChains.push_back (newChain);
	return newChain;
}

Chain* MySpecies::createChain (
		const Chain* c
		)
{
	Chain* newChain = new Chain (c);
	listOfChains.push_back (newChain);
	return newChain;
}

Tree* MySpecies::createTree ()
{
	Tree* newTree = new Tree;
	listOfTrees.push_back (newTree);

	//add root node with label ROOT
	//it has no parent node
	Node* root = newTree->createNode ();
	root->setNodeLabel ("ROOT");

	//add node map
	newTree->addNodeMap (root);

	return newTree;
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

void MySpecies::setDbId (
		const string& dbid
		)
{
	dbId = dbid;
}

void MySpecies::setLabel (
		const string& _label
		)
{
	label = _label;
}

void MySpecies::setCCid (
		const string& _ccid
		)
{
	ccid = _ccid;
}

string MySpecies::getDbId () const
{
	return dbId;
}

string MySpecies::getLabel () const
{
	return label;
}

string MySpecies::getCCid () const
{
	return ccid;
}

void MySpecies::rearrange ()
{
	//sort chains
	if (!isRearranged)
	{
		for (int i =0; i < listOfChains.size (); i++)
		{
			Chain* c = listOfChains[i];
			c->genUnicode ();
			c->genChainLabel (getId (), i);
		}

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
	int numC = listOfChains.size ();
	for (int cnt1 =0; cnt1 < numC; cnt1++)
	{
		Chain* c = listOfChains[cnt1];
		int numP = c->listOfParts.size ();
		for (int cnt2 =0; cnt2 < numP; cnt2++)
		{
			Part* p = c->listOfParts[cnt2];
			if (p->getIsBinded ())
			{
				Node* n = findBindedNode (p->getPartLabel());
				if (n) n->setNodeWeight (cnt1, cnt2);
			}
		}
	}

	//generate weight for all nodes
	//generate huffman code for all nodes
	int numT = listOfTrees.size ();
	for (int cnt =0; cnt < numT; cnt++)
	{
		Tree* t = listOfTrees[cnt];
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

void MySpecies::DeleteAndSave (
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

	int numC = listOfChains.size ();
	cout << "\nCHAINs (" << numC << "):" << endl;

	for (int cnt =0; cnt < numC; cnt++)
	{
		cout << "\nchain " << cnt << " :"; 
		listOfChains[cnt]->Output (cout);
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
			MySpecies::permType permAll (lhs->equiv.size());
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

	int numC = listOfChains.size ();
	for (int cnt =0; cnt < numC-1; )
	{
		Chain* c1 = listOfChains[cnt];

		int offset = 1;
		do
		{
			int curp = cnt + offset;
			Chain* c2 = listOfChains[curp];

			if (&c1 == &c2) 
			{
				offset++;
				if (curp+1 == numC) //last element
				{
					equiv.push_back (
							make_pair(cnt, numC-1)
							);
					cnt = numC;
				}
			}
			else
			{
				if (offset > 1)
					equiv.push_back (
							make_pair(cnt, curp-1)
							);
				cnt += offset;
				break;
			}
		} while (1);
	}

	//return
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

			int numM = records[i].size ();
			for (int k =0; k < numM; k++) 
				chainNum[i].push_back (j);

			found_all += numM;
		}
		if (found_all == 0) return false; 
		else permuteAll *= found_all;
	}

	//
	//	Permutation
	//
	for (int i = 0; i < permuteAll; i++)
	{
		int divide = i;

		//	same chains in this species could not be allowed 
		//            to match one chain in species s
		set <int> chainUsed;
		vector<cMatchType2> tryAssemble (numc_t);

		for (int j =0; j < numc_t; j++)
		{
			int indexperm = divide % records[j].size ();
			int chainnum = chainNum[j][indexperm];

			if (chainUsed.count (chainnum)) return false;
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

		//
		//	if no trees, a successful match has been found
		//
		if (s->getNumOfTrees ()) 
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
					string ctg = p->getPartCategory ();
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
			s1->DeleteAndSave (chainUsed, nodeSaved);


			//
			//  generate s2
			//
			set<string> subs_t;
			subs_t.insert ("X");
			subs_t.insert ("Y");
			subs_t.insert ("Z");
			subs_t.insert ("T");

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
					string partLabel = p->getPartLabel ();

					if (subs_t.count (partLabel))
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

			if (s1->equal (s2)) trym.push_back (tryAssemble);
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
}
