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
		typedef enum
		{
			START,
			GAMESCENE,
			REVIEW,
			SIMULATE
		} STATE;

		Ui::MainGraphicsView ui;
		MainGraphicsView(QWidget* parent);
		void setCompartments(QStringList &list);
		void setTreeView();
		void setUi(STATE curState);
		void setState(STATE curState);

	private:
		int m_state;
		QRect m_mainRect;

		QStringList m_compList;
		SceneManager* m_scenemgr;
		void getCompartFromDb();

		private slots:
		void highlightCombx(const QString &name);
		void createNewCompartment(const QString& partname);
		void activateCombx(const QString& partname);
		void runDemo();
		void getStart();
		void sceneNext();
		void loadDb();
};

#endif
