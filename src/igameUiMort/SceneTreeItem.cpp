#include "SceneTreeItem.h"
#include "MScene.h"

SceneTreeItem::SceneTreeItem(QTreeWidget *parent, MScene *sce) : QTreeWidgetItem(parent)
{
	if (sce == NULL)
		return;

	m_scene = sce;
	setText(0, sce->getId());
}

MScene* SceneTreeItem::getScene()
{
	return m_scene;
}
