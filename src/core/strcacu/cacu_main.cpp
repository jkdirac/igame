#include <map>
#include <string>
#include <iostream>

//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include "str_cacu.h"
#include "CoreException.h"
#include "DebugOut.h"

using namespace std;

void function_tests()
{
	double res;
	vector<string> pars;
	vector<string> exprs;
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a+b"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a+b > a+b*2"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a+b < a+b*2"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a+b*2 > a+b"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a+b*2 < a+b"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a-b*2 >= a+b"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a-b*2 <= a+b"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a-b*2 <= a+b"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("a-b*2 >= a+b"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("b/2 == a"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("b/2 != a"));

	pars.push_back(string("a=1,b=2,c=3,d=4")); exprs.push_back(string("a-b*2+c <= a+b+d"));
	pars.push_back(string("a=1,b=2,c=3,d=4")); exprs.push_back(string("a-b*2+c >= a+b+d"));
	pars.push_back(string("a=1,b=2,c=3,d=4")); exprs.push_back(string("a-b*2+c <= a+b+d || a-b*2+c >= a+b+d"));
	pars.push_back(string("a=1,b=2,c=3,d=4")); exprs.push_back(string("a-b*2+c <= a+b+d && a-b*2+c >= a+b+d"));
	pars.push_back(string("a=1,b=2,c=3,d=4")); exprs.push_back(string("(a-b*2+c <= a+b+d) || (a-b*2+c >= a+b+d)"));
	pars.push_back(string("a=1,b=2,c=3,d=4")); exprs.push_back(string("(a-b*2+c <= a+b+d) && (a-b*2+c >= a+b+d)"));

	pars.push_back(string("a=1,b=2,c=3,d=4")); exprs.push_back(string("(a-b*2+c <= a+b+d && (a-b*2+c >= a+b+d)"));
	pars.push_back(string("a=1,b=2")); exprs.push_back(string("(a-b*2+c <= a+b+d) && (a-b*2+c >= a+b+d)"));

	for (int i=0; i<pars.size(); i++)
	{
		debugOut() << "start test: " << i+1 << " in " << pars.size() << "\t";
		try
		{
			res = cacu_str_exp(pars[i].c_str(), exprs[i].c_str());
			debugOut() << "-- test cacu_string_exp : " << pars[i] << " (" << exprs[i] << ") = " << res;
		} catch (CoreException &se)
		{
			debugOut() << "!! cacu err: " << se.what() << " parameter: " << pars[i].c_str() <<  " expression: "
				<< exprs[i].c_str();
		}
		debugOut() << endl;
	}
}

int main (int argc, char **argv)
{
	int res;

	function_tests();

	return 0;
}
