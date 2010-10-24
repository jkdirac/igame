#include "SceneManager.h"
#include <QApplication>

SceneManager* SceneManager::_single_instance = NULL;

SceneManager::SceneManager()
	: m_view(NULL),
	m_rootscene(NULL),
	m_currentscene(NULL)
{
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

	if (m_rootscene = NULL)
		m_rootscene = scene;

	if (m_view != NULL)
	{
		m_currentscene = scene;
		m_view->setScene(m_currentscene);
	}
}
