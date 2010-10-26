#include "SceneManager.h"
#include <QApplication>
#include <QDebug>
#include "SceneTreeItem.h"

SceneManager* SceneManager::_single_instance = NULL;

SceneManager::SceneManager()
	: m_view(NULL),
	m_rootscene(NULL),
	m_currentscene(NULL),
	m_browserItem(NULL),
	m_browserItemId(0)
{
	m_browserItemX = 200;
	m_browserItemY = 700;

	m_rootItem = new SceneTreeItem(NULL, NULL);
}

void SceneManager::startShow()
{
	m_rootscene = new MScene();
	if ( m_rootscene != NULL)
	{
		m_rootscene->setId("Flask");
		m_rootscene->loadXml(":demoUiXml.ui.xml");

		qDebug() << "start to show!";
		m_rootscene->setTreeItem(m_rootItem);
		setCurrentScene(m_rootscene);
	}
}

SceneManager* SceneManager::getSceneManger()
{
	if (_single_instance == NULL)
	{
		_single_instance = new SceneManager();
	}

	return _single_instance;
}

void SceneManager::setMainView(MView* view)
{
	if (view != NULL)
		m_view = view;
}

void SceneManager::setCurrentScene(MScene* scene)
{
	if (scene == NULL)
		return;

	if (m_rootscene == NULL)
	{
		m_rootscene = scene;
	}

	if (m_view != NULL)
	{
		m_currentscene = scene;
		m_currentscene->showTreeWidget(m_rootItem);
		m_view->setScene(m_currentscene);
	}
}

void SceneManager::browserItem(MItem* item)
{
	if (item == NULL)
	{
		return;
	}

	//check position
	//if m_browserItem was not in init region, confirmed inserted in the scene
	//else delete the m_browserItem 
	if (m_browserItem 
			&& (m_browserItem->x() == m_browserItemX)
			&& (m_browserItem->y() == m_browserItemY))
	{
		m_currentscene->deletItemEx(m_browserItemId);
//        delete m_browserItem;
	}

	m_browserItem = item;
	m_browserItem->setX(m_browserItemX);
	m_browserItem->setY(m_browserItemY);
	m_browserItemId = m_currentscene->addItemEx(m_browserItem);
}

SceneTreeItem* SceneManager::getRootItem()
{
	return m_rootItem;
}

void SceneManager::addNewScene(MScene* newScene)
{
	if (newScene == NULL)
		return;
	
	m_currentscene->addChildScene(newScene);
	setCurrentScene(newScene);
}
