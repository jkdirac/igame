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
		void setTreeView();
		void setUi(STATE curState);
		void setState(STATE curState);

		void compartmentScene();
		void plasmidScene();

	private:
		int m_state;
		QRect m_mainRect;
		QRect m_fullRect;

		QStringList m_compList;
		QStringList m_backboneList;
		QStringList m_bioList;
		SceneManager* m_scenemgr;

		bool m_showBackforward;

		void getCompartFromDb();
		void getBackboneFromDb();
		void getBiobricksFromDb();
		void getCompoundFromDb();

		void setBiobricks(QStringList &list);
		void setBackbone(QStringList &list);
		void setCompartments(QStringList &list);
		void setCompounds(QStringList &list);

		private slots:
		void highlightComCombx(const QString &name);
		void highlightbackboneCombx(const QString &name);
		void highlightBioCombx(const QString &name);
		void highlightCompoundCombx(const QString &name);
		void createNewCompartment(const QString& partname);
		void activateCombx(const QString& partname);
		void runDemo();
		void getStart();
		void sceneNext();
		void loadDb();
		void backToMainMenu();
		void sceneBackForward();
};

#endif
