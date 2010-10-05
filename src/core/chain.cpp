#include "chain.h"

Chain::Chain ()
{
	keywords["ANY"] = 0;
	keywords["ANYUB"] = 1;
	keywords["NZ"] = 2;
	keywords["NZUB"] = 3;
	keywords["ONE"] = 4;
	keywords["ONEUB"] = 5;
}

Chain::Chain (const Chain* orig) 
	:
		unicode (orig->unicode),
		chainLabel (orig->chainLabel)
{
	for (int i =0; i < listOfParts.size (); i++)
		createPart (orig->listOfParts[i]);
}

Chain::~Chain ()
{
	for (int i =0; i < listOfParts.size (); i++)
		delete listOfParts[i];
}

Part* Chain::createPart ()
{
	Part* p = new Part;
	listOfParts.push_back (p);
	return p;
}

Part* Chain::createPart (const Part* p)
{
	Part* np = new Part (p);
	listOfParts.push_back (np);
	return np;
}

Part* Chain::createPart (
		const string& __ref,
		const string& __label,
		const string& __type,
		const string& __ctg,
		const bool& __isb
		)
{
	Part* p = new Part;
	p->setPart (__ref, __label, __type, __ctg, __isb);
	listOfParts.push_back (p);
	return p;
}

int Chain::getNumOfParts () const
{
	return listOfParts.size ();
}

string Chain::genUnicode (
		const int& start,
		const int& end
		) const
{
	string _unicode ("");
	for (int i=start; i<= end; i++)
	{
		const Part* p = listOfParts[i];

		//database id
		_unicode += "[" + p->getPartRef ();

		//database type
		_unicode += ":" + p->getPartType ();

		//is binded?
		if (p->isBinded) _unicode += ":*";

		_unicode += "]";
	}
	return _unicode;
}

void Chain::genUnicode ()
{
	//clear
	if (!unicode.empty ()) unicode.clear ();

	//initialize
	unicode = string ("");

	//traverse each part
	int numP = listOfParts.size ();
	for (int cnt =0; cnt < numP; cnt ++)
	{
		Part* p = listOfParts[cnt];

		//each part contribute a [id:type:(*)]... 
		//sub code to the whole 

		//database id
		unicode += "[" + p->getPartRef ();

		//database type
		unicode += ":" + p->getPartType ();

		//is binded?
		if (p->isBinded) unicode += ":*";

		unicode += "]";
	}
}

int Chain::getPartIndex (
		const string& label
		) const
{
	for (int i=0; i < listOfParts.size (); i++)
	{
		Part* p = listOfParts[i];
		if (p->getPartLabel () == label) return i;
	}
	return -1;
}

Part* Chain::getPart (const int& n) {
	return listOfParts.at (n);
}

const Part* Chain::getPart (const int& n) const {
	return listOfParts.at (n);
}

Part* Chain::getPart (const string& label)
{
	for (int i=0; i <listOfParts.size (); i++)
	{
		Part* p = listOfParts[i];
		if (label == p->getPartLabel ()) return p;
	}
	return NULL;
}

const Part* Chain::getPart (const string& label) const
{
	for (int i=0; i <listOfParts.size (); i++)
	{
		Part* p = listOfParts[i];
		if (label == p->getPartLabel ()) return p;
	}
	return NULL;
}

string Chain::getUnicode () const
{
	return unicode;
}

string Chain::getLabel () const
{
	return chainLabel;
}

void Chain::Output (ostream& os) const 
{
	os << "5' - ";

	int numP = listOfParts.size ();
	for (int cnt =0; cnt < numP; cnt++)
	{
		Part* p = listOfParts[cnt];
		os << p->getPartRef () << "(" 
			<< p->getPartType () << ","  
			<< p->getPartLabel () << ") - " ;
	}

	os << "3'";
}

bool Chain::equal (const Chain* rhs) const
{
	return unicode == rhs->unicode;
}

bool Chain::match (const Chain* c, cMatchsType& res	) const 
{		

	//
	//	find parts of non-substituent type
	//
	vector<markType> ns_t;
	vector<cMatchType> asmb; 

	bool start = true;
	for (int i=0; i < c->listOfParts.size (); i++)
	{
		Part* p = c->listOfParts[i];
		string ctg = p->getPartCtg ();	
		if (ctg != "substituent") 
		{
			if (start) 
			{
				ns_t.push_back (make_pair (i, 0));
				start = false;
			}
		}
		else 
		{
			ns_t.back ().second = i-1;
			start = true;
		}
	}

	//	check block searching!
	cout << "\nNon-Substituent Parts Block: " << endl;
	for (int i=0; i < ns_t.size (); i++)
		cout << "(" << ns_t[i].first << "," << ns_t[i].second << ") ";

	if (ns_t.size () > 0)
	{
		vector< markType >* m_pos = 
			new vector< markType > [ns_t.size ()];

		//
		//	for each non-substituent part, find its possible
		//	matching points in this chain 
		//
		int permAll = 1;
		for (int cnt =0; cnt < ns_t.size (); cnt++) 
		{
			int start = ns_t[cnt].first;
			int end = ns_t[cnt].second;
			int diff = end-start;

			string mkey = c->genUnicode (start, end);

			cout << "\nunicode = " << unicode;
			cout << "\nmkey = " << mkey;

			for (string::size_type pos = 0;
					(pos = unicode.find (mkey, pos)) 
					!= string::npos; pos++)
			{
				int spos = count (unicode.begin (), unicode.begin ()+pos, ']');
				int epos = spos + diff;

				cout << "\nspos = " << spos << " epos = " << epos;

				m_pos[cnt].push_back (make_pair (spos, epos));
			}

			if (m_pos[cnt].size () == 0) 
			{
				delete [] m_pos;
				return false;
			}
			else permAll *= m_pos[cnt].size ();
		}

		cout << "\npermAll = " << permAll << endl;

		//
		//	find possible matching combinations
		//
		for (int i =0; i < permAll; i++)
		{
			int lastp = -1;
			cMatchType tmp;

			int divide = i;
			for (int j=0; j< ns_t.size (); j++)
			{
				markType p = m_pos[j][divide % m_pos[j].size ()];
				if (p.first <= lastp) 
				{
					tmp.clear ();
					break;
				}
				else
				{
					lastp = p.second;
					tmp.push_back (p);
				}
				divide /= m_pos[j].size ();
			}

			assert (tmp.size () == ns_t.size ());
			if (!tmp.empty ()) asmb.push_back (tmp);
		}

		delete [] m_pos;
		if (asmb.size () == 0) return false;
	}

	//	take care if only substituent-type species exits

	//	check asmb
	for (int i=0; i < asmb.size (); i++)
	{
		cout << "\nMatch " << i << " : ";

		cMatchType tmp = asmb[i];
		cMatchType::const_iterator first
			= tmp.begin ();
		while (first != tmp.end ())
		{
			cout << "(" << first->first << "," << 
				first->second << ") ";
			first ++;
		}
	}

	//
	//	insert substituent pieces into asmb
	//

	//	if there are only substituent-type parts
	if (ns_t.size () == 0)
	{
		int l1 = 0;
		int u1 = c->listOfParts.size ()-1;

		assert (u1 >= l1);

		int l2 = 0; 
		int u2 = listOfParts.size ()-1;

		assert (u2 >= l2);

		bool mok = substituent_m (l1, u1, l2, u2, c, res);
		if (mok && res.size() > 0) return true;
		else return false;
	}
	else
	{
		assert (asmb.size () > 0);

		//	if there are non-substituent-type part
		for (int i=0; i< asmb.size (); i++)
		{
			vector<cMatchType> AssembleMatch;
			bool found = true;

			//
			//	*it ==> pair<int,int>
			//
			cMatchType::const_iterator it = asmb[i].begin ();

			//
			//	find matchings of first block of substituent-type parts
			//
			if (ns_t[0].first != 0)
			{
				vector<cMatchType> tmp;
				bool mok = substituent_m (
						0, ns_t[0].first-1, 0, it->first-1, c, tmp
						);
				//                cout << "\nmok = " << boolalpha << mok << endl;
				if (mok && tmp.size () > 0)
				{
					for (int j = 0; j < tmp.size (); j++)
						AssembleMatch.push_back (tmp[j]);
				}
				else return false;
			}

			int l1, u1, l2, u2;
			l1 = u1 = l2 = u2 = 0;

			for (int j=0; j < ns_t.size (); j++)
			{
				//
				//  add non-substituent type matching	
				//
				if (j == 0 && AssembleMatch.size () == 0)
				{
					cMatchType initial;
					for (int l=it->first; l <= it->second; l++)
						initial.push_back (make_pair (l,l));
					AssembleMatch.push_back (initial);
				}
				else
				{
					for (int k =0; k < AssembleMatch.size (); k++)
						for (int l=it->first; l <= it->second; l++)
							AssembleMatch[k].push_back (
									make_pair (l,l)
								);
				}

				//
				//  add substituent type matching
				//
				vector<cMatchType> tmp;

				l1 = ns_t[j].second+1;
				if (j == ns_t.size ()-1) u1 = c->listOfParts.size ()-1;
				else u1 = ns_t[j+1].first-1;
				l2 = it->second+1;
				if (j == ns_t.size ()-1) u2 = listOfParts.size ()-1;
				else u2 = (++it)->first-1; //it add one object

				//	no substituent-type parts
				if (j == ns_t.size ()-1)
					if (u1 < l1 && u2 < l2) continue;

				cout << "\nl1 = " << l1 << " u1 = " << u1 <<
					" l2 = " << l2 << " u2 = " << u2 << endl;

				bool mok = substituent_m (l1, u1, l2, u2, c, tmp);
				if (mok && tmp.size () > 0)
				{
					for (int k =0; k < AssembleMatch.size ();k++)
					{
						for (int l=0; l< tmp.size (); l++)
						{
							cMatchType expandMatch = AssembleMatch[k];
							expandMatch.insert (
									expandMatch.end (), tmp[i].begin (), tmp[i].end ()
									);
							AssembleMatch.push_back (expandMatch);
						}
						AssembleMatch.erase (AssembleMatch.begin () + k);	//remove record
					}
				}
				else
				{
					found = false;
					break;
				}
			}

			if (!found) continue;
			else
			{
				for (int j=0; j < AssembleMatch.size (); j++)
					res.push_back (AssembleMatch[j]);
			}
		}

		cout << "\nall possibilities found: " << res.size () << endl;

		if (res.empty ()) return false;
		return true;
	}
}

bool Chain::substituent_m (
		const int& l1,	//start pos of c
		const int& u1,	//end pos of c
		const int& l2,	//start pos of this
		const int& u2,	//end pos of this
		const Chain* c,
		vector<cMatchType>& result	//result
		) const
{
	cout << "\nl1 = "<< l1 << " u1 = "<< u1 <<
		" l2 = " << l2 << " u2 = " << u2 << endl;

	if (!result.empty ()) result.clear ();

	assert (l1 <= u1 + 1);
	assert (l2 <= u2 + 1);

	//	take case! l1 = u1+1 and l2 = u2+1 has been ruled out previously

	if (l1 == u1 + 1)
	{
		if (l2 == u2 + 1) return true;
		else return false; 
	}

	if (l2 == u2 + 1)
	{
		if (l1 == u1 + 1) return true;	
		else 
		{
			cMatchType res;
			for (int i=l1; i <= u1; i++) 
			{
				string partRef = c->listOfParts[i]->getPartRef ();
				int keyValue = keywords.find (partRef)->second;
				switch (keyValue)
				{
					case 0: 
					case 1: {res.push_back (make_pair(l2,u2));break;}
					default: return false;
				}
			}
			result.push_back (res);
			return true;
		}
	}

	//
	//	only handle one part and left recuisively
	//
	int startpos, endpos;
	assert (l1 < c->listOfParts.size ());
	string partRef = c->listOfParts[l1]->getPartRef ();
	string partType = c->listOfParts[l1]->getPartType ();
	if (keywords.count (partRef))
	{
		int keyValue = keywords.find (partRef)->second;
		switch (keyValue)
		{
			case 0: {
						startpos = l2; 
						endpos = u2+1; 
						if (!partType.empty ())
						{
							for (int i=l2; i<=u2; i++)
							{
								string partType__ = 
									listOfParts[i]->partType;
							    if (partType__ != partType) {
									endpos = i; break;
								}
							}
						}
						break;
					}
			case 1: {
						startpos = l2; 
						endpos = u2+1;
						for (int i=l2; i<=u2; i++)
							if (listOfParts[i]->isBinded) {
								endpos = i; break;
							}

						if (!partType.empty ())
						{
							for (int i=l2; i<=u2; i++)
							{
								string partType__ = 
									listOfParts[i]->partType;
							    if (partType__ != partType
										&& i < endpos) {
									endpos = i; break;
								}
							}
						}
						break;
					}
			case 2: {
						startpos = l2+1; 
						endpos = u2+1; 
						
						if (!partType.empty ())
						{
							for (int i=l2; i<=u2; i++)
							{
								string partType__ = 
									listOfParts[i]->partType;
							    if (partType__ != partType) {
									endpos = i; break;
								}
							}
						}
						break;
					}
			case 3: {
						startpos = l2+1; 
						endpos = u2+1;
						for (int i=l2; i<=u2; i++)
							if (listOfParts[i]->isBinded) {
								endpos = i; break;
							}
						if (!partType.empty ())
						{
							for (int i=l2; i<=u2; i++)
							{
								string partType__ = 
									listOfParts[i]->partType;
							    if (partType__ != partType
										&& i < endpos) {
									endpos = i; break;
								}
							}
						}
						break;
					}
			case 4: {
						startpos = endpos = l2+1; 
						string partType__ = 
							listOfParts[l2]->partType;
						if (!partType.empty () 
								&& partType__ != partType) 
							endpos = l2;
						break;
					}
			case 5: {
						startpos = l2+1;
						if (listOfParts[l2]->isBinded) endpos = l2;
						string partType__ = 
							listOfParts[l2]->partType;
						if (!partType.empty () 
								&& partType__ != partType) 
							endpos = l2;
						break;
					}
			default: {startpos = l2; endpos = u2+1; break;}
		}
	}

	bool rVal = false;
	for (int i = startpos; i <= endpos; i++)
	{
		vector< list< pair<int,int> > > recursive;
		bool mok = substituent_m (l1+1, u1, i, u2, c, recursive); 

		if (mok)
		{
			for (int j=0; j < recursive.size (); j++)
			{
				recursive[j].push_front (make_pair (l2, i-1));
				result.push_back (recursive[j]);
			}
			rVal = true;
		}
		else continue;
	}
	return rVal;
}


