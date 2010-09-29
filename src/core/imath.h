/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-09-25 16:54
*
*            Filename:		math.h
*
*            Description: .
*
************************************************************************************/
#ifndef MATH_H
#define MATH_H

#include "g_i.h"

class Math
{
  public:

	static void ordered_FullArray (
		const vector<int>& orig, 
		vector< vector<int> >& fullarray
		);

  private:

	static int Factorial (
		const int& n
		);
};
#endif
