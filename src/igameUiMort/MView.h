/****************************************************************************
**
** MosQt 0.10.14 alpha (2010 Oct 14)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#ifndef MView_h
#define MView_h

#include <QGraphicsView>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>

class MView : public QGraphicsView {
    Q_OBJECT

public:
    MView(QWidget* parent = 0);
    ~MView();

protected:
//    void keyPressEvent(QKeyEvent* event);
//    void keyReleaseEvent(QKeyEvent* event);
//    void mouseDoubleClickEvent(QMouseEvent* event);
//    void mouseMoveEvent(QMouseEvent* event);
//    void mousePressEvent(QMouseEvent* event);
//    void mouseReleaseEvent(QMouseEvent* event);

};

#endif
