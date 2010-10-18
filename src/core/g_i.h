/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified: 2010-09-25 02:22
*
*            Filename: g_i.h
*
*            Description: .
*
************************************************************************************/
#ifndef GLOBAL_INCLUDES_H
#define GLOBAL_INCLUDES_H

//====================
//C++ STANDARD LIBRARY
//====================
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <ctime>
#include <new>
#include <string>
#include <iterator>
#include <functional>
#include <utility>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stdexcept>
#include <exception>

//====================
//    LIBSBML       //
//====================
#include <sbml/SBMLTypes.h>

//====================
//    JkDirac       //
//====================
#include "strcacu/str_cacu.h"
#include "CoreException.h"

//LIBSBML_CPP_NAMESPACE_USE
using namespace std;

//====================
//    TYPEDEF       //
//====================
typedef pair<int,int> markType;

typedef list<markType> cMatchType;

typedef vector<cMatchType> cMatchsType;

typedef pair<cMatchType, int> cMatchType2;

typedef vector<cMatchType2> cMatchsType2;

typedef vector<cMatchsType2> cMatchsArray;

typedef pair<int, cMatchsType2> speciesMatch;

typedef vector<speciesMatch> speciesArrayMatch;

typedef pair<speciesArrayMatch, speciesArrayMatch> reactionMatch;

typedef pair<reactionMatch, map<string, int> > reactionPairMatch;

typedef vector<reactionPairMatch> reactionArrayMatch;

typedef vector<int> vi;

typedef vector<vi> dvi;

typedef vector<dvi> tvi;

typedef tvi permType;

typedef pair<string,string> subsp;

typedef pair<vector<string>, string> constraintType;

#endif
