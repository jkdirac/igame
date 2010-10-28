#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "MScene.h"
#include "MView.h"
#include "MItem.h"
#include <QTreeWidgetItem>

class MainGraphicsView;
class SceneManager : public QObject
{
	Q_OBJECT
	private:
		static SceneManager *_single_instance;
		SceneManager();

		MScene* m_rootscene;
		MScene* m_currentscene;

		SceneTreeItem* m_rootItem;

		QGraphicsView* m_view;

		MItem* m_browserItem;
		int m_browserItemId;
		qreal m_browserItemX;
		qreal m_browserItemY;

		private slots:
			void broswerScene(QTreeWidgetItem * current, 
					int cl);
		void broswerScene1(QTreeWidgetItem * current, int column);
	public:
		static SceneManager* getSceneManger();

		MainGraphicsView* m_mainWindow;
		SceneManager* setMainWindow(MainGraphicsView *win);

		void setCurrentScene(MScene* scene);
		void setMainView(QGraphicsView* view);
		void addNewScene(MScene* newScene);

		SceneTreeItem* getRootItem();

		void startShow();

		MScene* getRootScene();
		void deleteAllScene();
		void browserItem(MItem* item);
//        void confirmItem(MItem* item);
//
};

#endif
