#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "MScene.h"
#include "MView.h"
#include "MItem.h"

class SceneManager
{
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

	public:
		static SceneManager* getSceneManger();

		void setCurrentScene(MScene* scene);
		void setMainView(QGraphicsView* view);

		SceneTreeItem* getRootItem();

		void startShow();

		void browserItem(MItem* item);
//        void confirmItem(MItem* item);
};

#endif
