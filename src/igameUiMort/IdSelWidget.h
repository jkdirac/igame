#ifndef _IDCOMBOBOX_H_
#define _IDCOMBOBOX_H_

#include <QWidget>
#include <string>
#include "SceneManager.h"
#include "ui_IdSelWidget.h"
#include "bdbInterface.h"

class IdSelWidget: public QWidget
{
    Q_OBJECT

	public:
			IdSelWidget(QWidget* parent);
			void setCompartments(QStringList &list);

			private slots:
				void createNewCompartment(const QString& partname);
			void activateCombx(const QString& partname);
			void highlightCombx(const QString &);

	private:
			Ui::IdSelWidget ui;
			QStringList m_compList;
			SceneManager* scenemgr;
};

#endif
