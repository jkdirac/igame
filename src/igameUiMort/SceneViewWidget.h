#ifndef _SCENE_VIEW_WIDGET_H_
#define _SCENE_VIEW_WIDGET_H_

#include <QWidget>
#include <QStandardItemModel>
#include "ui_SceneViewWidget.h"

class SceneTreeItem;
class SceneViewWidget: public QWidget
{
	Q_OBJECT

	public:
		SceneViewWidget(QWidget* parent);
		void setTreeRootItem(SceneTreeItem* root);

	private:
		Ui::SceneViewWidget	ui;

		QStandardItemModel *model;
};

#endif
