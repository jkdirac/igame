/****************************************************************************
**
** MosQt 0.10.14 alpha (2010 Oct 14)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#ifndef MScene_h
#define MScene_h

#include <QGraphicsScene>
#include <QString>

class MItem;

class MScene : public QGraphicsScene {
    Q_OBJECT

public:
    MScene(QObject* parent = 0);
    ~MScene();

    MItem* selectedItem() const;
    void selectedItemBringToFront();
    void selectedItemSendToBack();

    void loadXml(const QString& fileName); //&
    void writeXml(const QString& fileName); //&

    MItem* dataScene;
    MItem* dataItem[1024];
    int dataCount;

private:
    qreal m_minZValue;
    qreal m_maxZValue;

};

#endif
