/****************************************************************************
**
** MosQt 0.10.14 alpha (2010 Oct 14)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#include "MView.h"

#include "MScene.h"
#include "MItem.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QGraphicsView>

#include <iostream>

int handler(MView*, MScene*, MItem*, QMouseEvent*, QKeyEvent*);

// Class MView constructor
MView::MView(QWidget* parent)
    : QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    this->setMouseTracking(true); // enable mouse move tracking
    //this->setDragMode(QGraphicsView::RubberBandDrag);

    this->showMaximized();
    this->setSceneRect(0, 0, 800, 600);

}

// Class MView destructor
MView::~MView()
{

}


#if 0
// Process MView key press event
void MView::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
        this->close();

    handler((MView*)this, (MScene*)(this->scene()), (MItem*)0, (QMouseEvent*)0, (QKeyEvent*)event);

    return QGraphicsView::keyPressEvent(event);
}

// Process MView key release event
void MView::keyReleaseEvent(QKeyEvent* event)
{
    handler((MView*)this, (MScene*)(this->scene()), (MItem*)0, (QMouseEvent*)0, (QKeyEvent*)event);

    return QGraphicsView::keyReleaseEvent(event);
}

// Process MView mouse double click event
void MView::mouseDoubleClickEvent(QMouseEvent* event)
{
    MItem* item = qgraphicsitem_cast<MItem*> (this->scene()->itemAt(event->pos().x(), event->pos().y()));

	handler((MView*)this, (MScene*)(this->scene()), (MItem*)item, (QMouseEvent*)event, (QKeyEvent*)0);
//    item->mouseDoubleClickEvent(event);
    return QGraphicsView::mouseDoubleClickEvent(event);
}

// Process MView mouse move event
void MView::mouseMoveEvent(QMouseEvent* event)
{
    //this->scene()->clearSelection();

    MItem* item = qgraphicsitem_cast<MItem*> (this->scene()->itemAt(event->pos().x(), event->pos().y()));

    if (item)
        if(item->isMouseOverSelectable())
            item->setSelected(true);



    handler((MView*)this, (MScene*)(this->scene()), (MItem*)item, (QMouseEvent*)event, (QKeyEvent*)0);

    return QGraphicsView::mouseMoveEvent(event);
}

// Process MView mouse press event
void MView::mousePressEvent(QMouseEvent* event)
{
    this->scene()->clearSelection();

    MItem* item = qgraphicsitem_cast<MItem*> (this->scene()->itemAt(event->pos().x(), event->pos().y()));

    if (item)
        if(item->isSelectable())
            item->setSelected(true);



    handler((MView*)this, (MScene*)(this->scene()), (MItem*)item, (QMouseEvent*)event, (QKeyEvent*)0);

    return QGraphicsView::mousePressEvent(event);
}

// Process MView mouse release event
void MView::mouseReleaseEvent(QMouseEvent* event)
{
    MItem* item = qgraphicsitem_cast<MItem*> (this->scene()->itemAt(event->pos().x(), event->pos().y()));

    handler((MView*)this, (MScene*)(this->scene()), (MItem*)item, (QMouseEvent*)event, (QKeyEvent*)0);

    return QGraphicsView::mouseReleaseEvent(event);
}

#endif
