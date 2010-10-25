#ifndef _IDCOMBOBOX_H_
#define _IDCOMBOBOX_H_

#include <QWidget>
#include "ui_IdSelWidget.h"
#include "bdbInterface.h"
#include <string>

class IdSelWidget: public QWidget
{
	Q_OBJECT

	public:
		IdSelWidget(QWidget* parent);
		void setCompartments(QStringList &list);

	private:
		Ui::IdSelWidget ui;
		QStringList m_compList;
};

#endif
