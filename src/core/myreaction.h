/*************************************************************************************
*
*            Author: liaochen- liaochen@mail.ustc.edu.cn
*
*            Last modified:	2010-09-27 19:45
*
*            Filename:		myreaction.h
*
*            Description: .
*
************************************************************************************/
#ifndef MY_REACTION_H
#define MY_REACTION_H

#include "reactionTemplate.h"
#include "mycompartment.h"
#include "myspecies.h"

class MyReaction:
  public Reaction
{
  public:

	MyReaction ();
	~MyReaction ();

	//
	//	return false if it is an intramolecular reaction
	//
	void completeReaction (
		vector<MyCompartment*>& listOfMyCompartments,
		vector<MySpecies*>& listOfMySpecies,
		vector<MySpecies*>& productsBody,
		const reactionTemplate::speciesArrayMatch& reactantsM,
		const reactionTemplate::speciesArrayMatch& modifiersM,
		const reactionTemplate* RT
		);


  private:
	
	vector<MySpecies*> listOfMyReactants;
	vector<MySpecies*> listOfMyModifiers;
	vector<MySpecies*> listOfMyProducts;
};

#endif
