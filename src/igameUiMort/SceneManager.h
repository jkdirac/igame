#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "MScene.h"
#include "MView.h"

class SceneManager
{
	private:
		static SceneManager *_single_instance;
		SceneManager();

		MScene* m_rootscene;
		MScene* m_currentscene;
		MView* m_view;

	public:
		static SceneManager* getSceneManger();
		void setCurrentScene(MScene* scene);
		void setMainView(MView* view);
};

#endif
