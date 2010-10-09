#include "driver.h"

Driver::Driver ()
{}

Driver::~Driver ()
{}

bool Driver::beginSimulation ()
{
	readInput dbreader;
	const string DB_PATH = "../../../example2";
	bool SBMLok =	false;

	//
	//  (3) core programs to complete reaction networks
	//
	try
	{
		MySBMLDocument* mysbmldoc = new MySBMLDocument;
		dbreader.add_directory (DB_PATH);
		dbreader.config (mysbmldoc);
		mysbmldoc->run (dbreader);

		//	for test
		ofstream ofs ("toSBML.xml", ios::out);
		ofs << mysbmldoc->toSBML () << endl;

		//	validate 
		SBMLok  = validateExampleSBML(mysbmldoc);
		if (SBMLok) writeExampleSBML(mysbmldoc, "network.xml");
		delete mysbmldoc;
		if (!SBMLok) return 1;
	}
	catch (XmlException& xe)
	{
		cerr << xe.what () << "\n: Unable to parse xml file." << endl;
		return 1;
	}
	catch (std::bad_alloc& e)
	{
		cerr << e.what() << "\n: Unable to allocate memory." << endl;
		return 1;
	}
	catch (StrCacuException& e)
	{
		cerr << e.what () << "\n: Invalid data term." << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "\nUnexpected exceptional condition encountered." << endl;
		return 1;
	}

	// A 0 return status is the standard Unix/Linux way to say "all ok".
	return 0;
}

//===============================================================================
//
//
// Helper functions for writing/validating the given SBML documents.
// 
//
//===============================================================================

/**
 *  
 *  Validates the given SBMLDocument.
 *
 *   This function is based on validateSBML.cpp implemented by
 *   Sarah Keating, Ben Bornstein, and Michael Hucka.
 *
 */
bool Driver::validateExampleSBML (
		SBMLDocument* sbmlDoc
		) const
{
	if (!sbmlDoc)
	{
		cerr << "validateExampleSBML: given a null SBML Document" << endl;
		return false;
	}

	string consistencyMessages;
	string validationMessages;
	bool noProblems                  = true;
	unsigned int numCheckFailures       = 0;
	unsigned int numConsistencyErrors   = 0;
	unsigned int numConsistencyWarnings = 0;
	unsigned int numValidationErrors    = 0;
	unsigned int numValidationWarnings  = 0;

	// LibSBML 3.3 is lenient when generating models from scratch using the
	// API for creating objects.  Once the whole model is done and before it
	// gets written out, it's important to check that the whole model is in
	// fact complete, consistent and valid.

	numCheckFailures = sbmlDoc->checkInternalConsistency();
	if ( numCheckFailures > 0 )
	{
		noProblems = false;
		for (unsigned int i = 0; i < numCheckFailures; i++)
		{
			const SBMLError* sbmlErr = sbmlDoc->getError(i);
			if ( sbmlErr->isFatal() || sbmlErr->isError() )
			{
				++numConsistencyErrors;
			}
			else
			{
				++numConsistencyWarnings;
			}      
		} 
		ostringstream oss;
		sbmlDoc->printErrors(oss);
		consistencyMessages = oss.str(); 
	}

	// If the internal checks fail, it makes little sense to attempt
	// further validation, because the model may be too compromised to
	// be properly interpreted.

	if (numConsistencyErrors > 0)
	{
		consistencyMessages += "Further validation aborted."; 
	}
	else
	{
		numCheckFailures = sbmlDoc->checkConsistency();
		if ( numCheckFailures > 0 )
		{
			noProblems = false;
			for (unsigned int i = 0; i < numCheckFailures; i++)
			{
				const SBMLError* sbmlErr = sbmlDoc->getError(i);
				if ( sbmlErr->isFatal() || sbmlErr->isError() )
				{
					++numValidationErrors;
				}
				else
				{
					++numValidationWarnings;
				}      
			} 
			ostringstream oss;
			sbmlDoc->printErrors(oss);
			validationMessages = oss.str(); 
		}
	}

	if (noProblems)
		return true;
	else
	{
		if (numConsistencyErrors > 0)
		{
			cout << "ERROR: encountered " << numConsistencyErrors 
				<< " consistency error" << (numConsistencyErrors == 1 ? "" : "s")
				<< " in model '" << sbmlDoc->getModel()->getId() << "'." << endl;
		}
		if (numConsistencyWarnings > 0)
		{
			cout << "Notice: encountered " << numConsistencyWarnings
				<< " consistency warning" << (numConsistencyWarnings == 1 ? "" : "s")
				<< " in model '" << sbmlDoc->getModel()->getId() << "'." << endl;
		}
		cout << endl << consistencyMessages;

		if (numValidationErrors > 0)
		{
			cout << "ERROR: encountered " << numValidationErrors
				<< " validation error" << (numValidationErrors == 1 ? "" : "s")
				<< " in model '" << sbmlDoc->getModel()->getId() << "'." << endl;
		}
		if (numValidationWarnings > 0)
		{
			cout << "Notice: encountered " << numValidationWarnings
				<< " validation warning" << (numValidationWarnings == 1 ? "" : "s")
				<< " in model '" << sbmlDoc->getModel()->getId() << "'." << endl;
		}
		cout << endl << validationMessages;

		return (numConsistencyErrors == 0 && numValidationErrors == 0);
	}
}


/**
 *
 * Writes the given SBMLDocument to the given file.
 *
 */ 
bool Driver::writeExampleSBML(
		const SBMLDocument* sbmlDoc, 
		const string& filename
		) const
{
	SBMLWriter sbmlWriter;

	bool result = sbmlWriter.writeSBML(sbmlDoc, filename);

	if (result)
	{
		cout << "Wrote file \"" << filename << "\"" << endl;
		return true;
	}
	else
	{
		cerr << "Failed to write \"" << filename << "\"" << endl;
		return false;
	}
}
