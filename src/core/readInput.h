/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified: 2010-09-24 08:44
*
*            Filename: readInput.h
*
*            Description: .
*
************************************************************************************/
#ifndef READ_INPUT_H
#define READ_INPUT_H

#include "readDataBase.h"
#include "mysbmldoc.h"

class readInput:
  public readDataBase
{
  public:

	readInput ();
	~readInput ();

	//
	//	config biological system
	//	setups based on input file
	//
	void config (
		MySBMLDocument* mysbmldoc
		);
  
};

#endif
