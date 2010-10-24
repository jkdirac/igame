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

namespace uiObjects {

MView * mainView;
MScene * mainScene;
MWidget * w;
};

using namespace uiObjects;

BEGIN(demoUiXml)
{
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
//    mainScene->setBackgroundBrush(QPixmap(":/images/demobg.png"));

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

//    ClickableWidget* cItem = new ClickableWidget(":xml/compartement.ui.xml");
//    int Item_clickable_id = mainScene->addItem(cItem);

	sceneMgr->setMainView(mainview);

	sceneMgr->setCurrentScene(mainScene);
}
END(demoUiXml)

BEGIN_EVENTS(demoUiXml)
{
    ;
    
}
END_EVENTS(demoUiXml)
