#include "chain.h"

Chain::Chain ()
{}

Chain::Chain (
	const Chain* orig
	):
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
  Part* newPart = new Part;
  listOfParts.push_back (newPart);
  return newPart;
}

Part* Chain::createPart (const Part* p)
{
  Part* newPart = new Part (p);
  listOfParts.push_back (newPart);
  return newPart;
}

Part* Chain::createPart (
		const string& partReference,
		const string& partLabel,
		const string& partType,
		const string& partCategory,
		const bool& isBinded
		)
{
	Part* newPart = new Part;
	
	//	set data members
	newPart->dbId = partReference;
	newPart->partLabel = partLabel;
	newPart->partType = partType;
	newPart->partCategory = partCategory;
	newPart->isBinded = isBinded;

	//	push back in parts list
	listOfParts.push_back (newPart);
	return newPart;
}
	
int Chain::getNumOfParts () const
{
  return listOfParts.size ();
}

void Chain::genChainLabel (
	const string& slabel,
	const int& num
	)
{
  ostringstream oss;
  oss << slabel << "cHaiN" << num;
  chainLabel = string (oss.str ());
}

string Chain::genUnicode (
	const Part* ps,
	const Part* pe
	) const
{
  string _unicode ("");
  for (const Part* p = ps; p != pe; p++)
  {
	//database id
	_unicode += "[" + p->getDbId ();
  
	//database type
	_unicode += ":" + p->getPartType ();

	//is binded?
	if (p->isBinded) _unicode += ":*";

	_unicode += "]";
  }
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
	unicode += "[" + p->getDbId ();
  
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

Part* Chain::getPart (
	const int& n
	)
{
  if (n < listOfParts.size () && n >= 0)
	return listOfParts[n];
  else return NULL;
}

const Part* Chain::getPart (
	const int& n
	) const
{ 
  if (n < listOfParts.size () && n >= 0)
	return listOfParts[n];
  else return NULL;
}

Part* Chain::getPart (
	const string& label
	)
{
  for (int i=0; i <listOfParts.size (); i++)
  {
	Part* p = listOfParts[i];
	if (label == p->getPartLabel ()) return p;
  }
  return NULL;
}

const Part* Chain::getPart (
	const string& label
	) const
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

string Chain::getChainLabel () const
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
	os << p->getDbId () << "(" 
	  << p->getPartType () << ","  
	  << p->getPartLabel () << ") - " ;
  }

  os << "3'";
}

bool Chain::equal (
	const Chain* rhs
	) const
{
  return unicode == rhs->unicode;
}

bool Chain::match ( 
	const Chain* c, 
	vector<cMatchType>& xyz
	) const 
{		

//
//	find parts of non-substituent type
//
  vector<markType> ns_t;
  vector<cMatchType> asmb; 

  bool start = true;
  int numParts = c->listOfParts.size ();
  for (int cnt =0; cnt < listOfParts.size (); cnt++)
  {
	Part* p = listOfParts[cnt];
	string ctg = p->getPartCategory ();	
	if (ctg != "substituent") 
	{
	  if (start) 
	  {
		ns_t.push_back (make_pair (cnt, 0));
		start = false;
	  }
	}
	else 
	{
		ns_t.back ().second = cnt-1;
		start = true;
	}
  }

  if (ns_t.size () > 0)
  {
	vector< markType >* m_pos = 
	  new vector< markType > [ns_t.size ()];

	//
	//	for each non-substituent part, find its possible
	//	matching points in this chain 
	//
	int permAll = 0;
	for (int cnt =0; cnt < ns_t.size (); cnt++) 
	{
	  int start = ns_t[cnt].first;
	  int end = ns_t[cnt].second;
	  int diff = end-start;

	  Part* ps = listOfParts[start];
	  Part* pe = listOfParts[end];

	  string mkey = genUnicode (ps, pe);

	  for (string::size_type pos = 0;
		  (pos = unicode.find_first_of (mkey, pos)) 
		  != string::npos; pos++)
	  {
		int spos = count (unicode.begin (), unicode.begin ()+pos, ']');
		int epos = spos + diff;

		m_pos[cnt].push_back (make_pair (spos, epos));
	  }

	  if (m_pos[cnt].size () == 0) 
	  {
		delete [] m_pos;
		return 0;
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
  }

//
//	insert substituent pieces into asmb
//
  for (int cnt =0; cnt < asmb.size (); cnt++)
  {
	int lastf1, lastf2;
	lastf1 = lastf2 = 0;
	bool found = true;

	//
	//	*it ==> pair<int,int>
	//
	vector<cMatchType> pm;
	cMatchType::const_iterator it = asmb[cnt].begin ();
	
	vector<cMatchType> tmp;
	bool mok = substituent_m (
		0, ns_t[0].first-1, 0, it->first-1, c, tmp
		);
	if (mok)
	{
	  for (int i = 0; i < tmp.size (); i++)
		pm.push_back (tmp[i]);
	}
	else continue;

	//
	for (int cnt2 =0; cnt2 < ns_t.size (); cnt2++, it++)
	{
	  int start1 = ns_t[cnt2].first;
	  int end1 = ns_t[cnt2].second;

	  int start2 = it->first;
	  int end2 = it->second;
	  
	  //
	  //  add non-substituent type matching	
	  //
	  for (int cnt3 =0; cnt3 < pm.size (); cnt3++)
	  {
		for (int k =start2; k <= end2; k++)
		  pm[cnt3].push_back (make_pair (k,k));
	  }

	  //
	  //  add substituent type matching
	  //
	  bool mok = substituent_m (
		  lastf1, start1-1, lastf2, start2-1, c, tmp
		  );
	  if (mok)
	  {
		vector<cMatchType>::iterator iter = pm.begin ();

		int k = -1;
		int currsize = pm.size ();
		while (++k < currsize)
		{
		  cMatchType tmp1 = pm[k];
		  pm.erase (iter + k);

		  //  tmp ==> vector<cMatchType>
		  for (int i =0; i < tmp.size (); i++)
		  {
			cMatchType tmp2 = tmp1;
			tmp2.insert (tmp2.end (), tmp[i].begin (), tmp[i].end ());
			pm.push_back (tmp2);
		  }
		}
	  }
	  else
	  {
		found = false;
		break;
	  }

	  //
	  //  update
	  //
	  lastf1 = end1+1;
	  lastf2 = end2+1;
	}

	if (!found) continue;
	else
	{
	  for (int i =0; i < pm.size (); i++)
		xyz.push_back (pm[cnt]);
	}
  }

  if (xyz.empty ()) return false;
  return true;
}

bool Chain::substituent_m (
	const int& l1,
	const int& u1,
	const int& l2,
	const int& u2,
	const Chain* c,
	vector<cMatchType>& pm
	) const
{
  if (l1 > u1 && l2 > u2) return true;
  else if (l2 > u2) return false;
  else if (l1 > u1) return false;
  else
  {
	if (!pm.empty ()) pm.clear ();

	//
	//	only handle one part and left recuisively
	//
	string type = c->listOfParts[l1]->getDbId ();
	if (type == "X")
	{
	  bool rVal = false;
	  for (int cnt =l2; cnt <= u2+1; cnt++)
	  {
		vector< list< pair<int,int> > > m;
		bool mok = substituent_m (l1+1, u1, cnt, u2, c, m); 
	
		if (mok)
		{
		  for (int cnt2 =0; cnt2 < m.size (); cnt2++)
		  {
			m[cnt2].push_front (make_pair (l2, cnt-1));
			pm.push_back (m[cnt2]);
		  }
		  rVal = true;
		}
		else continue;
	  }
	  return rVal;
	}
	else if (type == "T")
	{
	  vector< list< pair<int,int> > > m;
	  bool mok = substituent_m (l1+1, u1, l2+1, u2, c, m); 
	  if (mok)
	  {
		for (int cnt2 =0; cnt2 < m.size (); cnt2++)
		{
		  m[cnt2].push_front (make_pair (l2, l2));
		  pm.push_back (m[cnt2]);
		}
		return true;
	  }
	  else return false;
	}
	else if (type == "Y")
	{
	  vector< list< pair<int,int> > > m;
	  bool mok = substituent_m (l1+1, u1, l2, u2, c, m); 
	  if (mok)
	  {
		for (int cnt2 =0; cnt2 < m.size (); cnt2++)
		{
		  m[cnt2].push_front (make_pair (l2, l2-1));
		  pm.push_back (m[cnt2]);
		}
		return true;
	  }
	  else return false;
	}
	else if (type == "Z")
	{
	  bool rVal = false;
	  for (int cnt =l2+1; cnt <= u2+1; cnt++)
	  {
		vector< list< pair<int,int> > > m;
		bool mok = substituent_m (l1+1, u1, cnt, u2, c, m); 
		if (mok)
		{
		  for (int cnt2 =0; cnt2 < m.size (); cnt2++)
		  {
			m[cnt2].push_front (make_pair(l2, cnt-1));
			pm.push_back (m[cnt2]);
		  }
		  rVal = true;
		}
		else continue;
	  }
	  return rVal;
	}
	else
	{
	  cout << "\nNo Such Substituent Type!" << endl;
	  terminate ();
	}
  }
}


