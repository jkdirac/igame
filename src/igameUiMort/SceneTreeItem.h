#ifndef _SCENE_TREE_ITEM_H_
#define _SCENE_TREE_ITEM_H_

#include <QTreeWidgetItem>
class MScene;
class SceneTreeItem : public QTreeWidgetItem
{
	private:
		MScene* m_scene;

	public:
		SceneTreeItem(QTreeWidget *parent, MScene *sce);
		MScene* getScene();
};

#endif
