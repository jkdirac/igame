#include "InputGen.h"
#include <QQueue>
#include "SceneManager.h"
#include <QTreeWidgetItemIterator>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "CoreException.h"

InputGen::InputGen() : m_scenMgr(NULL)
{
	m_listCompartments.clear();
	m_listScene.clear();
	m_inputContent.clear();
	m_scenMgr = SceneManager::getSceneManger();
}

QString& InputGen::generateInput()
{
//    MScene* rootScene = m_scenMgr->getRootScene();
	SceneTreeItem* rootItem = m_scenMgr->getRootItem();

	if (rootItem == NULL)
	{
		throw CoreException("GeneratoInput error rootItem NULL");
	}

	QTreeWidgetItemIterator iter((QTreeWidgetItem*)rootItem); 

	// collect all validate compartment or plasmid
	while (*iter)
	{
		MScene* scene = ((SceneTreeItem*)*iter) -> getScene();

		if (!(*iter)->isDisabled())
		{
			if (scene != NULL)
			{
				m_listScene.push_back(scene);
			}
		}

		iter++;
	}

	m_listCompartments += "\n<listOfCompartments>\n";
	m_listSpecies += "\n<listOfSpecies>\n";
	for (int i = 0; i < m_listScene.size(); i++)
	{
		if (m_listScene[i] == NULL)
			continue;

//        m_listCompartments += m_listScene[i]->generateComXmlString();
//        m_listSpecies += m_listScene[i]->generateSpeXmlString();
	}

	m_listCompartments += "</listOfCompartments>\n";
	m_listSpecies += "</listOfSpecies>\n";

	m_xmlStart = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<MoDeL>\n<dbInterface>\n<input>\n";
	m_xmlEnd = "\n</input>\n</dbInterface>\n</MoDeL>\n";

	m_inputContent += m_xmlStart;
    m_inputContent += m_listCompartments;
    m_inputContent += m_listSpecies;
	m_inputContent += m_xmlEnd;
	return m_inputContent;
}
