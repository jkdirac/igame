#ifndef _SCENE_VIEW_WIDGET_H_
#define _SCENE_VIEW_WIDGET_H_

#include <QWidget>
#include "ui_SceneViewWidget.h"

class SceneViewWidget: public QWidget
{
	Q_OBJECT

	public:
		SceneViewWidget(QWidget* parent);

	private:
		Ui::SceneViewWidget	ui;
};

#endif
