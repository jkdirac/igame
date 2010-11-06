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

#include <QTreeWidgetItemIterator>
#include "SpeciesData.h"
#include "SceneTreeItem.h"
#include "SettingWidget.h"

//#include "SceneTreeItem.h"

class MItem;
class SceneTreeItem;
class SceneViewWidget;

class MScene : public QGraphicsScene {
    Q_OBJECT

public:
    MScene(QObject* parent = 0, SPECIESTYPE type=SPEC_COMPARTMENT, MItem* root = NULL);
    MScene(QObject* parent, const QString& id, SPECIESTYPE=SPEC_COMPARTMENT, MItem* root = NULL);
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

	MScene* itemApplyNewScene(MItem *item);

	void deletItemEx(int n);
	void deletItemEx(MItem* item);

	QString& getId();
	void setId(const QString& id);

	//Item drag and clicked handler
	bool itemInTrash(MItem *item);
	bool itemInCompartment(MItem *item);
	bool itemIsRootItem(MItem* item);
	virtual bool itemDropped(MItem *item);

	SPECIESTYPE type() {return m_type; }

	int childrenCount();
	MScene* getChild(int n);
	QVector<MItem*>& getValidSubItems();

	virtual QString generateComXmlString();
	virtual QString generateSpeXmlString();
	QString generateRuleFuncXmlString();
	QString generateParameterXmlString();

	int addSpeciesItem(MItem *item);
	void addBrowserItem(MItem *item);

	MScene* parent() { return m_parent; };

	void invalidTree(bool invalid);
	
	void showSettWidget(SettingWidget *wid);
	void closeSettWidget(SettingWidget *wid);

protected:
	MItem* m_rootItem;
	SpeciesData* m_rootData;
    MItem* dataScene;
	MItem* m_trashItem;
#define ITEMBUFNUM 1024
    MItem* dataItem[ITEMBUFNUM];
    int m_dataCount;
	qreal m_browserItemX;
	qreal m_browserItemY;
	SPECIESTYPE m_type;
	QString m_id;

	//dirty pool
#define POOLNUM 16
	MItem* dirtyItemPool[POOLNUM];
	int m_nFree;

	void addItemEx(MItem *item);
	void init();

private:

	QString m_name;
    qreal m_minZValue;
    qreal m_maxZValue;
	QVector<MScene*> m_childern;
	MScene* m_parent;
	MWidget* selWidget;
	SceneViewWidget* m_overviewWidget;
	SceneTreeItem* m_treeItem;

	MItem* m_browserItem;
	int m_browserItemId;

	SettingWidget *m_setWidget;
};


#endif
