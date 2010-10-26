#ifndef _SCENE_TREE_ITEM_H_
#define _SCENE_TREE_ITEM_H_

#include <QTreeWidgetItem>
class MScene;
class SceneTreeItem : public QTreeWidgetItem
{
	private:
		MScene* m_scene;

	public:
		SceneTreeItem(QTreeWidgetItem *parent, MScene *sce);
		SceneTreeItem(const QString& str);
		MScene* getScene();
		SceneTreeItem* clone();
		void setScene(MScene* sce);
};

#endif
