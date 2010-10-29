#include "SceneManager.h"
#include <QApplication>
#include <QDebug>
#include "SceneTreeItem.h"
#include "MainGraphicsView.h"

SceneManager* SceneManager::_single_instance = NULL;

SceneManager::SceneManager()
	: m_view(NULL),
	m_rootscene(NULL),
	m_currentscene(NULL)
{
	m_rootItem = new SceneTreeItem(NULL, NULL);
}

void SceneManager::destoryShow()
{
	if (m_rootscene != NULL)
	{
		delete m_rootscene;
		m_rootscene = NULL;
	}
}

void SceneManager::startShow()
{
	qDebug() << "start to show!";
	if (m_rootscene != NULL)
	{
		m_rootItem = m_rootscene->getTreeItem();
		setCurrentScene(m_rootscene);
		return;
	}

	m_rootscene = new MScene(NULL, "Flask");

	if ( m_rootscene != NULL)
	{
		m_rootItem = m_rootscene->getTreeItem();

		setCurrentScene(m_rootscene);
	}

	m_mainWindow->setTreeView();
}

SceneManager* SceneManager::setMainWindow(MainGraphicsView *win)
{
	if (win != NULL)
	{
		m_mainWindow = win;
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

void SceneManager::setMainView(QGraphicsView* view)
{
	if (view != NULL)
		m_view = view;
}

void SceneManager::setCurrentScene(MScene* scene)
{
	if (scene == NULL)
		return;

	if (m_view != NULL)
	{
		m_currentscene = scene;

		if (m_rootscene == NULL)
		{
			m_rootscene = scene;
		}

		m_view->setScene(m_currentscene);

		if (m_currentscene->type() == SPEC_COMPARTMENT)
		{
			m_mainWindow->compartmentScene();
		}
		if (m_currentscene->type() == SPEC_BACKBONE)
		{
			m_mainWindow->plasmidScene();
		}
	}
}

void SceneManager::browserItem(MItem* item)
{
	m_currentscene->addBrowserItem(item);
}

SceneTreeItem* SceneManager::getRootItem()
{
	m_rootItem = m_rootscene->getTreeItem();
	return m_rootItem;
}

void SceneManager::addNewScene(MScene* newScene)
{
	if (newScene == NULL)
		return;
	
	m_currentscene->addChildScene(newScene);
	setCurrentScene(newScene);
}

void SceneManager::broswerScene(QTreeWidgetItem * current, int cl)
{
	if (current == NULL)
		return;

	qDebug() << "broswer Scene";

	SceneTreeItem* curSceneItem = (SceneTreeItem*)current;
	MScene* setScene = curSceneItem->getScene();
	
	setCurrentScene(setScene);
}

void SceneManager::broswerScene1(QTreeWidgetItem * current, int previous)
{
	qDebug() << "broswer Scene";
	SceneTreeItem* curSceneItem = (SceneTreeItem*)current;
	MScene* setScene = curSceneItem->getScene();
	
	setCurrentScene(setScene);
}

MScene* SceneManager::getRootScene()
{
	return m_rootscene;
}
