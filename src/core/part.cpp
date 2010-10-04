#include "part.h"

Part::Part () :isBinded (false) {}

Part::Part (const Part* orig) : 
	partRef (orig->partRef), 
	partLabel (orig->partLabel),
  	partType (orig->partType),
  	partCtg (orig->partCtg),
	isBinded (orig->isBinded)
{}

Part::~Part (){}

void Part::setPart (
		const string& __ref, 
		const string& __label, 
		const string& __type, 
		const string& __ctg, 
		const string& __isb 
		)
{
	partRef = __ref;
	partLabel = __label;
	partType = __type;
	partCtg = __ctg;
	isBinded = __isb;
}

void Part::setPartRef (const string& __ref) {
	partRef = __ref
}

void Part::setPartLabel (const string& __label) {
  	partLabel = __label;
}

void Part::setPartType (const string& __type) {
  	partType = __type;
}

void Part::setPartCtg (const string& __ctg) {
  	partCtg = _ctg;
}

void Part::setIsBinded (const bool& isb) {
	isBinded = isb;
}

string Part::getPartRef () const {return dbId;}

string Part::getPartLabel () const {return partLabel;}

string Part::getPartType () const {return partType;}

string Part::getPartCtg () const {return partCtg;}

bool Part::getIsBinded () const {return isBinded;}
