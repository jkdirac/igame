#include "SceneViewWidget.h"
#include "SceneTreeItem.h"
#include "SceneManager.h"
#include <QStringList>
#include <QList>
#include <QTreeWidgetItem>
#include <QDebug>

SceneViewWidget* SceneViewWidget::_single_instance = NULL;

SceneViewWidget::SceneViewWidget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);

	ui.overViewWidget->setColumnCount(1);
	SceneManager* mgr = SceneManager::getSceneManger();
}

SceneViewWidget* SceneViewWidget::getSceneView()
{
	if (_single_instance == NULL)
	{
		_single_instance = new SceneViewWidget(NULL);
	}

	return _single_instance;
}

void SceneViewWidget::setTreeRootItem(SceneTreeItem* rootItem)
{
	qDebug() << "--view widget start: rootItem: " << (int)rootItem;
	if (rootItem == NULL)
		return;

	m_tree = rootItem->clone();

	QList<QTreeWidgetItem*> rootList; 
	rootList << (QTreeWidgetItem*)m_tree; 
	ui.overViewWidget->insertTopLevelItems(0, rootList); 
}
