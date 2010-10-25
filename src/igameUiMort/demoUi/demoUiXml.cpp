/*
 * 
     .--.  
    /( @ >    ,-. 
   / ' .'--._/  /
   :   ,    , .'
   '. (___.'_/
    ((-((-''
 * ------------------------------------
 * HUMAN RIGHTS FOR EVERYONE EVERYWHERE
 * ------------------------------------
 * 
 * iGaME UI demo (built on 20 October 2010)
 * 
 * based on MosQt framework 0.10.14 alpha
 *
 * Copyright (C) 2010 Mort Yao.
 * All rights reserved.
 * Contact: Mort Yao (mort.yao@gmail.com)
 * 
 */
 
#include <MosQt>
#include "IdSelWidget.h"
#include "SceneViewWidget.h"
#include "SceneManager.h"
#include "ClickableWidget.h"
#include "GlobalSetting.h"
#include "CoreException.h"

namespace uiObjects {

MView * mainView;
MScene * mainScene;
MWidget * w;
};

using namespace uiObjects;

bool init_global_dir_setting()
{
	QDir dir = QDir::home();

	QString igame_home_path = ".igame";

	bool b_succ = true;

	if (dir.exists())
	{
		if (!dir.exists(igame_home_path))
		{
			b_succ = dir.mkdir(igame_home_path);
		}
	}

	if (!b_succ)
	{
		dir = QDir::current();
		if (!dir.exists(igame_home_path))
		{
			b_succ = dir.mkdir(igame_home_path);
		}
	}

	if (b_succ)
	{
		QString dir_path = dir.path() + "/" +  igame_home_path;
		set_igame_home(dir_path.toLatin1().constData());
	}
	else
	{
		//set current file
		set_igame_home(QDir::currentPath().toLatin1().constData());
		// notify the user check the file system full 
		// or have not the write permission of path %HOME and "./" 
	}

	return b_succ;
}

BEGIN(demoUiXml)
{
	bool bSucc;
	bSucc = init_global_dir_setting();
	if (!bSucc)
	{
		qDebug() << "global dir setting error: " << endl;
		return 0;
	}

	SceneManager* sceneMgr = SceneManager::getSceneManger();

	int deskWidth = QApplication::desktop()->width();
	int deskheight = QApplication::desktop()->height();

    MView* mainview = new MView();

    mainview->setWindowTitle("demoUiXml");
    mainview->showMaximized();
	mainview->setSceneRect(0, 0, deskWidth, deskheight);
    mainview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainScene = new MScene();
    mainScene->loadXml(":demoUiXml.ui.xml");
	mainScene->setBackgroundBrush(QPixmap(":/images/demobg.png"));

	MWidget* widget[100];
	// 创建MWidget界面对象
	// MWidget界面对象是用于Qt原生widget的容器
	// 可以通过MWidget向场景中添加任何Qt原生widget
	//
	
	IdSelWidget* IdSel = new IdSelWidget(NULL);
	widget[1] = (MWidget*)mainScene->addWidget(IdSel);
	widget[1]->setX(0);
	widget[1]->setY(0);

	SceneViewWidget* sceneView = new SceneViewWidget(NULL);
	widget[2] = (MWidget*)mainScene->addWidget(sceneView);
	widget[2]->setX(0);
	widget[2]->setY(300);

	MItem* Item = new MItem(":xml/compartment.ui.xml");
//    ClickableWidget* cItem = new ClickableWidget(":demoUiXml.ui.xml");
	int Item_id = mainScene->addItemEx(Item);

//    ClickableWidget* cItem = new ClickableWidget(":xml/compartment.ui.xml");
//    ClickableWidget* cItem = new ClickableWidget(":demoUiXml.ui.xml");
//    int Item_clickable_id = mainScene->addItemEx(cItem);

	sceneMgr->setMainView(mainview);
	sceneMgr->setCurrentScene(mainScene);
}
END(demoUiXml)

BEGIN_EVENTS(demoUiXml)
{
    ;
    
}
END_EVENTS(demoUiXml)
