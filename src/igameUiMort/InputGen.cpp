#include "InputGen.h"
#include <QQueue>
#include "SceneManager.h"
#include <QTreeWidgetItemIterator>

InputGen::InputGen() : m_scenMgr(NULL)
{
	m_listCompartments.clear();
	m_listParts.clear();
	m_scenMgr = SceneManager::getSceneManger();
}

void InputGen::generateInput()
{
//    MScene* rootScene = m_scenMgr->getRootScene();
	SceneTreeItem* rootItem = m_scenMgr->getRootItem();

	if (rootItem == NULL)
	{
		qDebug() << "error rootItem NULL";
		return;
	}

	QTreeWidgetItemIterator iter((QTreeWidgetItem*)rootItem); 

	// collect all validate compartment or plasmid
	while (*iter)
	{
		MScene* scene = ((SceneTreeItem*)*iter) -> getScene();

		if (scene != NULL)
			m_listCompartments.push_back(scene);
		
		m_listParts.push_back(data);

		iter++;
	}

	//

}
