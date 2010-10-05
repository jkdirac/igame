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

		/**
		 * create reactions from template
		 */
		void createReactionsFromTemplate (
				bdbXMLInterface&, 
				const speciesArrayMatch&, 
				const speciesArrayMatch&, 
				vector<MySpecies*>&,
				vector<MySpecies*>&, 
				vector<MyCompartment*>&, 
				const reactionTemplate*
				);

		/**
		 * transcription and translation reaction
		 */
		void addSpecialReaction (
				MySpecies*, 
				MySpecies*, 
				const string&, 
				const string&, 
				const double&, 
				const string&
				);

	private:

		vector<MySpecies*> listOfMyReactants, listOfMyModifiers, listOfMyProducts;
};

#endif
