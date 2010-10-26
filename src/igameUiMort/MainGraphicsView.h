#ifndef _MAIN_GRAPHICS_VIEW_H_
#define _MAIN_GRAPHICS_VIEW_H_

#include <QWidget>
#include "ui_MainGraphicsView.h"

class MainGraphicsView : public QWidget
{
	Q_OBJECT

	public:
		MainGraphicsView(QWidget* parent);

		Ui::MainGraphicsView ui;

};

#endif
