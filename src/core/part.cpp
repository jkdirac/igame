#include "part.h"

Part::Part ()
  :isBinded (false)
{}

Part::Part (
	const Part* orig
	):
  dbId (orig->dbId),
  partLabel (orig->partLabel),
  partType (orig->partType),
  partCategory (orig->partCategory),
  isBinded (orig->isBinded)
{}

Part::~Part ()
{}

void Part::setDbId (
	const string& dbid
	) 
{
  dbId = dbid;
}

void Part::setPartLabel (
	const string& label
	)
{
  partLabel = label;
}

void Part::setPartType (
	const string& type
	)
{
  partType = type;
}

void Part::setPartCategory (
	const string& category
	)
{
  partCategory = category;
}

void Part::setIsBinded (
	const bool& isb
	)
{
  isBinded = isb;
}

string Part::getDbId () const
{
  return dbId;
}

string Part::getPartLabel () const
{
  return partLabel;
}

string Part::getPartType () const
{
  return partType;
}

string Part::getPartCategory () const
{
  return partCategory;
}

bool Part::getIsBinded () const
{
  return isBinded;
}
