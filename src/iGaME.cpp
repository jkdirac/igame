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
 * iGaME demo (built on 15 October 2010)
 * 
 * based on MosQt framework 0.10.14 alpha
 *
 * Copyright (C) 2010 Mort Yao.
 * All rights reserved.
 * Contact: Mort Yao (mort.yao@gmail.com)
 * 
 */

#include <MosQt>

#define UI_VERSION 20101015

#if UI_VERSION == 20101015

namespace uiObjects {

MView * mainView;
MScene * mainMenu;
MItem * logo;
MItem * menu1, * menu2, * menu3, * menu4, * menu5, * menu6, * menu7, * menu8;
MItem * sub1, * sub2, * sub3, * sub4, * sub5, * sub6, * sub7;

};

using namespace uiObjects;

BEGIN(iGaME)
{
    iGaME->setPixmap("./iGaME.images/splash.png");
    
    mainView = new MView();
    
    mainView->showFullScreen();
    mainView->setSceneRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height());
    mainView->setWindowTitle("iGaME demo");
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainMenu = new MScene();
    mainView->setScene(mainMenu);

    logo = new MItem();
    mainMenu->addItem(logo);
    logo->setPixmap("./iGaME.images/ustc_software.png");
    logo->setWidth(400);
    logo->setHeight(200);
    logo->setPos(640, 200);

    menu1 = new MItem();
    mainMenu->addItem(menu1);
    menu1->setText("GETTING STARTED");
    menu1->setFigure("ROUND_RECTANGLE");
    menu1->setFigureColor(QColor(255, 255, 255));
    menu1->setAlternativeFigure("ROUND_RECTANGLE");
    menu1->setAlternativeFigureColor(QColor(0, 0, 0));
    menu1->setWidth(120);
    menu1->setHeight(60);
    menu1->setPos(220, 400);
    menu1->setSelectable(true);

    menu2 = new MItem();
    mainMenu->addItem(menu2);
    menu2->setText("iGaME");
    menu2->setFigure("ROUND_RECTANGLE");
    menu2->setFigureColor(QColor(255, 255, 255));
    menu2->setAlternativeFigure("ROUND_RECTANGLE");
    menu2->setAlternativeFigureColor(QColor(0, 0, 0));
    menu2->setWidth(120);
    menu2->setHeight(60);
    menu2->setPos(menu1->x() + 120, 400);
    menu2->setSelectable(true);

    menu3 = new MItem();
    mainMenu->addItem(menu3);
    menu3->setText("TOOLS");
    menu3->setFigure("ROUND_RECTANGLE");
    menu3->setFigureColor(QColor(255, 255, 255));
    menu3->setAlternativeFigure("ROUND_RECTANGLE");
    menu3->setAlternativeFigureColor(QColor(0, 0, 0));
    menu3->setWidth(120);
    menu3->setHeight(60);
    menu3->setPos(menu2->x() + 120, 400);
    menu3->setSelectable(true);

    menu4 = new MItem();
    mainMenu->addItem(menu4);
    menu4->setText("HELP");
    menu4->setFigure("ROUND_RECTANGLE");
    menu4->setFigureColor(QColor(255, 255, 255));
    menu4->setAlternativeFigure("ROUND_RECTANGLE");
    menu4->setAlternativeFigureColor(QColor(0, 0, 0));
    menu4->setWidth(120);
    menu4->setHeight(60);
    menu4->setPos(menu3->x() + 120, 400);
    menu4->setSelectable(true);

    menu5 = new MItem();
    mainMenu->addItem(menu5);
    menu5->setText("WIKI");
    menu5->setFigure("ROUND_RECTANGLE");
    menu5->setFigureColor(QColor(255, 255, 255));
    menu5->setAlternativeFigure("ROUND_RECTANGLE");
    menu5->setAlternativeFigureColor(QColor(0, 0, 0));
    menu5->setWidth(120);
    menu5->setHeight(60);
    menu5->setPos(menu4->x() + 120, 400);
    menu5->setSelectable(true);

    menu6 = new MItem();
    mainMenu->addItem(menu6);
    menu6->setText("UPDATE");
    menu6->setFigure("ROUND_RECTANGLE");
    menu6->setFigureColor(QColor(255, 255, 255));
    menu6->setAlternativeFigure("ROUND_RECTANGLE");
    menu6->setAlternativeFigureColor(QColor(0, 0, 0));
    menu6->setWidth(120);
    menu6->setHeight(60);
    menu6->setPos(menu5->x() + 120, 400);
    menu6->setSelectable(true);

    menu7 = new MItem();
    mainMenu->addItem(menu7);
    menu7->setText("ABOUT");
    menu7->setFigure("ROUND_RECTANGLE");
    menu7->setFigureColor(QColor(255, 255, 255));
    menu7->setAlternativeFigure("ROUND_RECTANGLE");
    menu7->setAlternativeFigureColor(QColor(0, 0, 0));
    menu7->setWidth(120);
    menu7->setHeight(60);
    menu7->setPos(menu6->x() + 120, 400);
    menu7->setSelectable(true);

    menu8 = new MItem();
    mainMenu->addItem(menu8);
    menu8->setText("EXIT");
    menu8->setFigure("ROUND_RECTANGLE");
    menu8->setFigureColor(QColor(255, 255, 255));
    menu8->setAlternativeFigure("ROUND_RECTANGLE");
    menu8->setAlternativeFigureColor(QColor(0, 0, 0));
    menu8->setWidth(120);
    menu8->setHeight(60);
    menu8->setPos(menu7->x() + 120, 400);
    menu8->setSelectable(true);

    sub1 = new MItem();
    mainMenu->addItem(sub1);
    sub1->setFigure("ROUND_RECTANGLE");
    sub1->setFigureColor(QColor(255, 255, 255));
    sub1->setWidth(960);
    sub1->setHeight(300);
    sub1->setPos(640, 600);
    sub1->setVisible(false);

    sub2 = new MItem();
    mainMenu->addItem(sub2);
    sub2->setFigure("ROUND_RECTANGLE");
    sub2->setFigureColor(QColor(255, 255, 255));
    sub2->setWidth(960);
    sub2->setHeight(300);
    sub2->setPos(640, 600);
    sub2->setVisible(false);
    
    sub3 = new MItem();
    mainMenu->addItem(sub3);
    sub3->setFigure("ROUND_RECTANGLE");
    sub3->setFigureColor(QColor(255, 255, 255));
    sub3->setWidth(960);
    sub3->setHeight(300);
    sub3->setPos(640, 600);
    sub3->setVisible(false);
    
    sub4 = new MItem();
    mainMenu->addItem(sub4);
    sub4->setFigure("ROUND_RECTANGLE");
    sub4->setFigureColor(QColor(255, 255, 255));
    sub4->setWidth(960);
    sub4->setHeight(300);
    sub4->setPos(640, 600);
    sub4->setVisible(false);

    sub5 = new MItem();
    mainMenu->addItem(sub5);
    sub5->setFigure("ROUND_RECTANGLE");
    sub5->setFigureColor(QColor(255, 255, 255));
    sub5->setWidth(960);
    sub5->setHeight(300);
    sub5->setPos(640, 600);
    sub5->setVisible(false);
    
    sub6 = new MItem();
    mainMenu->addItem(sub6);
    sub6->setFigure("ROUND_RECTANGLE");
    sub6->setFigureColor(QColor(255, 255, 255));
    sub6->setWidth(960);
    sub6->setHeight(300);
    sub6->setPos(640, 600);
    sub6->setVisible(false);

    sub7 = new MItem();
    mainMenu->addItem(sub7);
    sub7->setFigure("ROUND_RECTANGLE");
    sub7->setFigureColor(QColor(255, 255, 255));
    sub7->setWidth(960);
    sub7->setHeight(300);
    sub7->setPos(640, 600);
    sub7->setVisible(false);
    
    
    
}
END(iGaME)

BEGIN_EVENTS(iGaME)
{
    if(EVENT_ITEM) {
        if(MOUSE_LEFT && EVENT_ITEM->text() == "GETTING STARTED") {
            sub1->setVisible(true);
            sub2->setVisible(false);
            sub3->setVisible(false);
            sub4->setVisible(false);
            sub5->setVisible(false);
            sub6->setVisible(false);
            sub7->setVisible(false);

        } else if(MOUSE_LEFT && EVENT_ITEM->text() == "iGaME") {
            sub1->setVisible(false);
            sub2->setVisible(true);
            sub3->setVisible(false);
            sub4->setVisible(false);
            sub5->setVisible(false);
            sub6->setVisible(false);
            sub7->setVisible(false);
            
        } else if(MOUSE_LEFT && EVENT_ITEM->text() == "TOOLS") {
            sub1->setVisible(false);
            sub2->setVisible(false);
            sub3->setVisible(true);
            sub4->setVisible(false);
            sub5->setVisible(false);
            sub6->setVisible(false);
            sub7->setVisible(false);
            
        } else if(MOUSE_LEFT && EVENT_ITEM->text() == "HELP") {
            sub1->setVisible(false);
            sub2->setVisible(false);
            sub3->setVisible(false);
            sub4->setVisible(true);
            sub5->setVisible(false);
            sub6->setVisible(false);
            sub7->setVisible(false);
            
        } else if(MOUSE_LEFT && EVENT_ITEM->text() == "WIKI") {
            sub1->setVisible(false);
            sub2->setVisible(false);
            sub3->setVisible(false);
            sub4->setVisible(false);
            sub5->setVisible(true);
            sub6->setVisible(false);
            sub7->setVisible(false);
            
        } else if(MOUSE_LEFT && EVENT_ITEM->text() == "UPDATE") {
            sub1->setVisible(false);
            sub2->setVisible(false);
            sub3->setVisible(false);
            sub4->setVisible(false);
            sub5->setVisible(false);
            sub6->setVisible(true);
            sub7->setVisible(false);
            
        }  else if(MOUSE_LEFT && EVENT_ITEM->text() == "ABOUT") {
            sub1->setVisible(false);
            sub2->setVisible(false);
            sub3->setVisible(false);
            sub4->setVisible(false);
            sub5->setVisible(false);
            sub6->setVisible(false);
            sub7->setVisible(true);
            
        } else if(MOUSE_LEFT && MOUSE_EVENT->type() == QEvent::MouseButtonRelease && EVENT_ITEM->text() == "EXIT")
            mainView->close();
        
    }
    
}
END_EVENTS(iGaME)

#endif
