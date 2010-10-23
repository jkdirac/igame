#ifndef _IDCOMBOBOX_H_
#define _IDCOMBOBOX_H_

#include <QWidget>
#include "ui_IdSelWidget.h"

class IdSelWidget: public QWidget
{
	Q_OBJECT

	public:
		IdSelWidget(QWidget* parent);

	private:
		Ui::IdSelWidget ui;
};

#endif
