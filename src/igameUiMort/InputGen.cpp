#include "InputGen.h"
#include <QQueue>
#include "SceneManager.h"

InputGen::InputGen() : m_scenMgr(NULL)
{
	m_listCompartments.clear();
	m_listParts.clear();
	m_scenMgr = SceneManager::getSceneManger();
}

void InputGen::generateInput()
{
	MScene* rootScene = m_scenMgr->getRootScene();

	if (rootScene == NULL)
		return;

	//iterator the tree
//    QQueue<MScene *> queue;
//    queue.enqueue(rootScene);

//    MScene* tmpScene = queue.head();
//    while (tmpScene->childrenCount() > 0)
//    {
//        QVector<MItem*> subItems = tmpScene->getValidSubItems();
//        tmpScene = que
//    }
//    MScene::iterator* itr = rootScene->getIterator();
}
