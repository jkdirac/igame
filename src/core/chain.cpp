#include "chain.h"
#include "DebugOut.h"

Chain::Chain () {}
Chain::Chain (const Chain* orig) 
	:
		unicode (orig->unicode),
		chainLabel (orig->chainLabel),
		chainNum (orig->chainNum),
		isDNA (orig->isDNA),
		isRNA (orig->isRNA)
{
	for (int i =0; i < orig->listOfParts.size (); i++)
		this->createPart (orig->listOfParts[i]);
}

Chain::~Chain ()
{
	for (int i =0; i < listOfParts.size (); i++)
		delete listOfParts[i];
}

void Chain::setIsDNA ()
{
	isDNA = true;

	for (int i=0; i < listOfParts.size (); i++)
	{
		Part* p = listOfParts[i];
		if (p->getPartType () != "ForwardDNA"
				&& p->getPartType () != "ReverseDNA")
		{
			isDNA = false;
			return;
		}
	}
}

void Chain::setIsRNA ()
{
	isRNA = true;

	for (int i=0; i < listOfParts.size (); i++)
	{
		Part* p = listOfParts[i];
		if (p->getPartType () != "ForwardRNA"
				&& p->getPartType () != "ReverseRNA")
		{
			isRNA = false;
			return;
		}
	}
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

void Chain::turnover ()
{
	stack<Part*> stack_part;
	const int numparts = listOfParts.size ();

	for (int i=0; i < numparts; i++)
	{
		Part* p = listOfParts[i];
		stack_part.push (p);

		if (p->getPartType () == "ForwardDNA") 
			p->setPartType ("ReverseDNA");
		else if (p->getPartType () == "ReverseDNA") 
			p->setPartType ("ForwardDNA");
	}

	listOfParts.clear ();

	for (int i=0; i < numparts; i++) {
		listOfParts.push_back (stack_part.top ());	
		stack_part.pop ();
	}

	//	reset unicode
	unicode = genUnicode (0, listOfParts.size ()-1, true);
}

bool Chain::isCsymm ()
{
	//	is this chain a DNA chain?
	this->setIsDNA ();

	//	is this chain a RNA chain?
	this->setIsRNA ();

	//	yes
	if (isDNA)
	{
		string fw_unicode = genUnicode (0, listOfParts.size ()-1, true);
		string rev_unicode = genUnicode (0, listOfParts.size ()-1, false);
		if (rev_unicode < fw_unicode) {turnover (); unicode = rev_unicode; return false;}
		else if (rev_unicode > fw_unicode) {unicode = fw_unicode; return false;}
		else {unicode = fw_unicode; return true;}
	}
	else
	{
		unicode = genUnicode (0, listOfParts.size ()-1, true);
		return false;
	}
}

string Chain::genUnicode (
		const int& start, const int& end, const bool& dir
		) const
{
	string _unicode ("");

	if (dir)
	{
		for (int i=start; i<= end; i++)
		{
			const Part* p = listOfParts[i];
			_unicode += "[" + p->getPartRef ()
					 +	":" + p->getPartType ();
			if (p->isBinded) _unicode += ":*";
			_unicode += "]";
		}
	}
	else
	{
		for (int i=end; i >= start; i--)
		{
			const Part* p = listOfParts[i];
			_unicode += "[" + p->getPartRef () + ":";
		   	
			if (p->getPartType () == "ForwardDNA") _unicode += "ReverseDNA";
			else if (p->getPartType () == "ReverseDNA") _unicode += "ForwardDNA";
			else _unicode += p->getPartType ();

			if (p->isBinded) _unicode += ":*]";
			else _unicode += "]";
		}
	}

	return _unicode;
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

string Chain::getLabel () const {
	return chainLabel;
}

void Chain::setLabel (const string& label) {
	chainLabel = label;
}

void Chain::__add_chain_prefix (
		const string& prefix
		)
{
	for (int i=0; i<listOfParts.size (); i++) {
		Part* p = listOfParts[i]; 
		p->partLabel = prefix + p->partLabel;
	}
	genUnicode (0, listOfParts.size ()-1, true);
}

void Chain::Output (ostream& os) const 
{
	os << "\n5'	---- ";

	int numP = listOfParts.size ();
	for (int cnt =0; cnt < numP; cnt++)
	{
		Part* p = listOfParts[cnt];
		os << "\n			" <<  p->getPartRef ();

	    if (p->isBinded) os << "*";

		os << "(" << p->getPartType () 
		   << "," << p->getPartLabel () 
		   << ")  " ;
	}
	os << "\n----	3'";
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

	for (int i=0; i < c->listOfParts.size ();)
	{
		Part* p = c->listOfParts[i];
		string ctg = p->getPartCtg ();	

		int startpos = i;
		if (ctg != "substituent")
		{
			bool found = false;
			int j = i+1;
			for (; j < c->listOfParts.size (); j++)
			{
				Part* p1 = c->listOfParts[j];
				string ctg1 = p1->getPartCtg ();
				if (ctg1 == "substituent") {found = true;break;}
			}
			if (j == c->listOfParts.size ()) found = true;
			if (found)
			{
				ns_t.push_back (make_pair(i, j-1));
				i = j+1;
			}

		}
		else i++;
	}

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

			string mkey = c->genUnicode (start, end, true);

			for (string::size_type pos = 0;
					(pos = unicode.find (mkey, pos)) 
					!= string::npos; pos++)
			{
				int spos = count (unicode.begin (), unicode.begin ()+pos, ']');
				int epos = spos + diff;

				m_pos[cnt].push_back (make_pair (spos, epos));
			}

			if (m_pos[cnt].size () == 0) 
			{
				delete [] m_pos;
				return false;
			}
			else permAll *= m_pos[cnt].size ();
		}

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

	//	insert substituent pieces into asmb

	//	if there are only substituent-type parts
	if (ns_t.size () == 0)
	{
		int l1 = 0;
		int u1 = static_cast<int> (c->listOfParts.size ())-1;

		int l2 = 0; 
		int u2 = listOfParts.size ()-1;

		assert (u1 >= l1);
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
				int keyValue = getKeywords (partRef);

				if (keyValue != -1)
				{	
					switch (keyValue)
					{
						case 0: 
						case 1: {res.push_back (make_pair(l2,u2));break;}
						default: return false;
					}
				}
				else 
				{
					string errno ("Invalid Substituent Type: ");
				    errno += partRef + "!";
					throw CoreException (errno);
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
	int keyValue = getKeywords (partRef);
	
	if (keyValue != -1)
	{
		switch (keyValue)
		{
			case 0: {
						startpos = l2; 
						endpos = u2+1; 
						if (!partType.empty ())
						{
							for (int i=l2; i<=u2; i++)
								if (!type_match (listOfParts[i]->partType, partType))
									endpos = i; break;
						}
						break;
					}
			case 1: {
						startpos = l2; 
						endpos = u2+1;

						for (int i=l2; i<=u2; i++)
						{
							if (listOfParts[i]->isBinded) endpos = i; break;
						}

						if (!partType.empty ())
						{
							for (int i=l2; i<= endpos-1; i++)
							{
								if (!type_match (listOfParts[i]->partType, partType)) 
									endpos = i; break;
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
								if (!type_match (listOfParts[i]->partType, partType))
									endpos = i; break;
						}
						break;
					}
			case 3: {
						startpos = l2+1; 
						endpos = u2+1;

						for (int i=l2; i<=u2; i++)
						{
							if (listOfParts[i]->isBinded) endpos = i; break;
						}

						if (!partType.empty ())
						{
							for (int i=l2; i<= endpos-1; i++)
							{
								if (!type_match (listOfParts[i]->partType, partType)) 
									endpos = i; break;
							}
						}
						break;
					}
			case 4: {
						startpos = endpos = l2+1; 
						if (!type_match (listOfParts[l2]->partType, partType)) endpos = l2;
						break;
					}
			case 5: {
						startpos = endpos = l2+1;
						if (listOfParts[l2]->isBinded) endpos = l2;
						if (!type_match (listOfParts[l2]->partType, partType)) endpos = l2;
						break;
					}
			default: break;
		}
	}
	else 
	{
		string errno ("Invalid Substituent Type: ");
		errno += partRef + "!";
		throw CoreException (errno);
	}

	bool rVal = false;
	for (int i = startpos; i <= endpos; i++)
	{
		vector< list< pair<int,int> > > recursive;
		bool mok = substituent_m (l1+1, u1, i, u2, c, recursive); 

		if (mok)
		{
			if (recursive.size () == 0)
			{
				//	only push back in matchings of current part
				cMatchType only_one;
				only_one.push_back (make_pair (l2, i-1));
				result.push_back (only_one);
			}
			else
			{
				for (int j=0; j < recursive.size (); j++)
				{
					recursive[j].push_front (make_pair (l2, i-1));
					result.push_back (recursive[j]);
				}
			}
			rVal = true;
		}
		else continue;
	}
	return rVal;
}

bool Chain::type_match (
		const string& type1, 
		const string& type2
		) const
{
	if (type2.empty ()) return true;
	else if (type1 == type2) return true;
	else if (type2 == "DNA")
	{
		if (type1 == "ForwardDNA" || type1 == "ReverseDNA") return true;
		else return false;
	}
	else if (type2 == "RNA")
	{
		if (type1 == "ForwardRNA" || type1 == "ReverseRNA") return true;
		else return false;
	}
	else if (type2 == "Protein")
	{
		if (type1 == "ForwardProtein" || type1 == "ReverseProtein") return true;
		else return false;
	}
	else return false;
}

int Chain::getKeywords (const string& ref) const
{
	if (ref == "ANY") return 0;
	if (ref == "ANYUB") return 1;
	if (ref == "NZ") return 2;
	if (ref == "NZUB") return 3;
	if (ref == "ONE") return 4;
	if (ref == "ONEUB") return 5;
	return -1;
}
