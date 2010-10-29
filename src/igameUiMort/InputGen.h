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
		QString& generateInput();

	private:
		QString m_listCompartments;
		QString m_listSpecies;
		QString m_xmlStart;
		QString m_xmlEnd;
		QString m_inputContent;
		QVector<MScene*> m_listScene;
		SceneManager* m_scenMgr;
};

#endif
