/*************************************************************************************
 *
 *            Author: liaochen- liaochen@mail.ustc.edu.cn
 *
 *            Last modified:	2010-09-23 23:13
 *
 *            Filename:		driver.h
 *
 *            Description: .
 *
 ************************************************************************************/
#ifndef DRIVER_H
#define DRIVER_H

#include "readInput.h"

class Driver
{
  public:

	Driver ();
	~Driver ();

	//
	//	return name fo SBML document of
	//	biological system
	//
	bool beginSimulation ();

  private:

	//
	//	helper functions
	//
	bool validateExampleSBML (
		SBMLDocument* sbmlDoc
		) const;
	
	bool writeExampleSBML(
		const SBMLDocument* sbmlDoc, 
		const string& filename
		) const;

};
#endif


