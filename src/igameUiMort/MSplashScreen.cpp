/****************************************************************************
**
** MosQt 0.10.14 alpha (2010 Oct 14)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#include "MSplashScreen.h"

#include <QWidget>
#include <QSplashScreen>
#include <QFont>
#include <QKeyEvent>
#include <QPixmap>

#include <iostream>

// Class MSplashScreen constructor
MSplashScreen::MSplashScreen(QWidget* parent)
    : QSplashScreen(parent)
    , m_pixmap("./iGaME.images/splash.png")
    , m_text("")
    , m_textAlignment(Qt::AlignCenter || Qt::AlignBottom)
    , m_textColor(Qt::black)
    , m_textFont(QFont::QFont("Arial", 20, QFont::Normal))
{
    this->renew();

}

// Class MSplashScreen destructor
MSplashScreen::~MSplashScreen()
{

}



// Renew MSplashScreen display
void MSplashScreen::renew()
{
    this->setPixmap(QPixmap(m_pixmap));
    this->setFont(m_textFont);
    this->showMessage(m_text, m_textAlignment, m_textColor);

    return;
}



// Process MSplashScreen key press event
void MSplashScreen::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
        this->close();
    else
        ;

    return;
}


