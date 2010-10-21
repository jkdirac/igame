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

namespace uiObjects {

MView * mainView;
MScene * mainScene;

};

using namespace uiObjects;

BEGIN(demoUiXml)
{
    mainView = new MView();
    
    mainView->setWindowTitle("demoUiXml");
    mainView->showMaximized();
    mainView->setSceneRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height());
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainScene = new MScene();
    mainScene->loadXml("./demoUiXml.ui.xml");
    mainView->setScene(mainScene);
    
    
    
}
END(demoUiXml)

BEGIN_EVENTS(demoUiXml)
{
    ;
    
}
END_EVENTS(demoUiXml)
