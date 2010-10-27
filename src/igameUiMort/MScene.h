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
#include <QVector>
#include "MWidget.h"

#include "Species.h"

//#include "SceneTreeItem.h"

class MItem;
class SceneTreeItem;
class SceneViewWidget;

class MScene : public QGraphicsScene {
    Q_OBJECT

public:

    MScene(QObject* parent = 0, SPECIESTYPE type=SPEC_COMPARTMENT);
    MScene(QObject* parent, const QString& id, SPECIESTYPE=SPEC_COMPARTMENT);
    ~MScene();

    MItem* selectedItem() const;
    void selectedItemBringToFront();
    void selectedItemSendToBack();

    void loadXml(const QString& fileName); //&
    void writeXml(const QString& fileName); //&

	void setTreeItem(SceneTreeItem *item);
	SceneTreeItem* getTreeItem();

	void addChildScene(MScene *child);
	void deleteChildScene(int id);
	void setParent(MScene* parent);

	int addItemEx(MItem *item);
	void deletItemEx(int n);
	void deletItemEx(MItem* item);

    MItem* dataScene;
	MItem* m_comItem;
	MItem* m_trashItem;
    MItem* dataItem[1024];
    int dataCount;

	QString& getId();
	void setId(const QString& id);

	//Item drag and clicked handler
	bool itemInCompartment(MItem *item);
	bool itemDropped(MItem *item);

	SPECIESTYPE type() {return m_type; }

private:
	QString m_id;
	QString m_name;
    qreal m_minZValue;
    qreal m_maxZValue;
	QVector<MScene*> m_childern;
	MItem* m_rootItem;
	MScene* m_parent;

	SPECIESTYPE m_type;

	void init();
	MWidget* selWidget;
	SceneViewWidget* m_overviewWidget;
	SceneTreeItem* m_treeItem;
};

#endif
