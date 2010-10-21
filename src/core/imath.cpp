#include "imath.h"

void Math::ordered_FullArray (
		const vector<int>& orig, 
		vector< vector<int> >& fullarray
		)
{
	if (orig.empty ()) return;

	const int n = Factorial (orig.size ());
	fullarray = vector< vector<int> > (n);

	for (int i = 0; i < n; i++)
	{
		int divide = i;
		fullarray[i].push_back (orig.at(0));
		for (int j = 2; j <= orig.size (); j++)
		{
			vector<int>::iterator it = 
				fullarray[i].begin ();
			advance (it, divide % j);

			if (it == fullarray[i].end ()) 
				fullarray[i].push_back (orig[j-1]);
			else fullarray[i].insert (it, orig[j-1]);

			divide /= j;
		}
	}
}

int Math::Factorial (
		const int& n
		)
{
	assert (n >= 0);
	if (n == 0) { return 1; }
	else return n * Factorial(n - 1);
}


