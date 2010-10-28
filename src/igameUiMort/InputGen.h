#ifndef _INPUT_GEN_H_
#define _INPUT_GEN_H_

#include "SpeciesData.h"
#include <QVector>

class SceneManager;
class MScene;
class InputGen 
{
	public:
		InputGen();
		void generateInput();

	private:
		QVector<SpeciesData*>  m_listCompartments;
		QVector<MScene*>  m_listParts;
		QVector<MScene*>  m_listScene;
		SceneManager* m_scenMgr;
};

#endif
