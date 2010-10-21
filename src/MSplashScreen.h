/****************************************************************************
**
** MosQt 0.10.14 alpha (2010 Oct 14)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#ifndef MSplashScreen_h
#define MSplashScreen_h

#include <QSplashScreen>
#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QColor>
#include <QFont>
#include <QKeyEvent>

class MSplashScreen : public QSplashScreen {
    Q_OBJECT

public:

    MSplashScreen(QWidget* parent = 0);
    ~MSplashScreen();
    
    void renew();
    
    QString pixmap() { return m_pixmap; }
    void setPixmap(QString pixmap) { m_pixmap = pixmap; this->renew(); }
    void setPixmap(QPixmap pixmap) { QSplashScreen::setPixmap(pixmap); }
    
    QString text() { return m_text; }
    void setText(QString text) { m_text = text; this->renew(); }
    
    int textAlignment() { return m_textAlignment; }
    void setTextAlignment(int textAlignment) { m_textAlignment = textAlignment; this->renew(); }
    
    QColor textColor() { return m_textColor; }
    void setTextColor(QColor textColor) { m_textColor = textColor; this->renew(); }
    
    QFont textFont() { return m_textFont; }
    void setTextFont(QFont textFont) { m_textFont = textFont; this->renew(); }

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    QString m_pixmap;
    QString m_text;
    int m_textAlignment;
    QColor m_textColor;
    QFont m_textFont;

};

#endif
