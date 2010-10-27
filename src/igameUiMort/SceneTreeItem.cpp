#include "SceneTreeItem.h"
#include "MScene.h"
#include <QDebug>

SceneTreeItem::SceneTreeItem(const QString& str) : QTreeWidgetItem(NULL)
{
	setText(0, str);
}

SceneTreeItem::SceneTreeItem(QTreeWidgetItem *parent, MScene *sce) : QTreeWidgetItem(parent)
{
	if (sce == NULL)
		return;

	m_scene = sce;
	qDebug() << "new Scene tree item " << sce->getId();
	setText(0, sce->getId());
}

MScene* SceneTreeItem::getScene()
{
	return m_scene;
}

void SceneTreeItem::setScene(MScene *sce)
{
	if (sce != NULL)
		m_scene = sce;

	setText(0, sce->getId());
}

SceneTreeItem* SceneTreeItem::clone()
{
}
