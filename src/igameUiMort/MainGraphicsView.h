#ifndef _MAIN_GRAPHICS_VIEW_H_
#define _MAIN_GRAPHICS_VIEW_H_

#include <QWidget>
#include "ui_MainGraphicsView.h"
#include <string>
#include "SceneManager.h"
#include "bdbInterface.h"

class MainGraphicsView : public QWidget
{
	Q_OBJECT

	public:
		Ui::MainGraphicsView ui;
		MainGraphicsView(QWidget* parent);
		void setCompartments(QStringList &list);
		void setTreeView();

	private:

		QStringList m_compList;
		SceneManager* m_scenemgr;

		private slots:
		void highlightCombx(const QString &name);
		void createNewCompartment(const QString& partname);
		void activateCombx(const QString& partname);
};

#endif
