#ifndef _INPUT_GEN_H_
#define _INPUT_GEN_H_

#include "SpeciesData.h"
#include <QVector>

class SceneManager;
class InputGen 
{
	public:
		InputGen();
		void generateInput();

	private:
		QVector<SpeciesData>  m_listCompartments;
		QVector<SpeciesData>  m_listParts;
		SceneManager* m_scenMgr;
};

#endif
