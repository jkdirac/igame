#ifndef _SCENE_VIEW_WIDGET_H_
#define _SCENE_VIEW_WIDGET_H_

#include <QWidget>
#include "ui_SceneViewWidget.h"

class SceneTreeItem;
class SceneViewWidget: public QWidget
{
	Q_OBJECT

	public:
		SceneViewWidget(QWidget* parent);
		void setTreeRootItem(SceneTreeItem* root);
		static SceneViewWidget* getSceneView();

	private:
		Ui::SceneViewWidget	ui;
		static SceneViewWidget* _single_instance;

//        SceneTreeItem* m_tree;
		QTreeWidgetItem* m_tree;
		void copyScene(SceneTreeItem* root);
};

#endif
