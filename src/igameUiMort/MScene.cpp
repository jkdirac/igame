/****************************************************************************
**
** MosQt 0.10.14 alpha (2010 Oct 14)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#include "MScene.h"
#include "MItem.h"
#include "MWidget.h"
#include "IdSelWidget.h"
#include "SceneViewWidget.h"
#include "SceneTreeItem.h"
#include "ClickableWidget.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QFile>
#include <QXmlStreamReader>
#include <QColor>
#include <QXmlStreamWriter>

#include <iostream>
#include <QDebug>

// Class MScene constructor
MScene::MScene(QObject* parent, SPECIESTYPE type, MItem* rootitem)
	: QGraphicsScene(parent)
	, dataCount(0)
	, m_minZValue(0)
	, m_maxZValue(0)
	, m_treeItem(NULL)
	  ,m_trashItem(NULL)
	  ,m_type(type)
	  ,m_rootItem(NULL)
	   ,m_rootData(NULL)
{
	if (rootitem)
	{
		qDebug() << "--------use exists item";
		m_rootData = rootitem->getSpeciesData();
	}
	init();
}

MScene::MScene(QObject* parent, const QString& id, SPECIESTYPE type, MItem* rootitem)
	: QGraphicsScene(parent)
	, dataCount(0)
	, m_minZValue(0)
	, m_maxZValue(0)
	, m_treeItem(NULL)
	  ,m_trashItem(NULL)
	  ,m_type(type)
	  ,m_rootItem(NULL)
	   ,m_rootData(NULL)
{
	if (rootitem)
	{
		qDebug() << "--------use exists item";
		m_rootData = rootitem->getSpeciesData();
	}
	m_id = id;
	init();
}

void MScene::init()
{
	m_setWidget = NULL;
	m_nFree = 0;
	m_browserItem = NULL;
	m_browserItemX = 140;
	m_browserItemY = -250;
	//    loadXml(":demoUiXml.ui.xml");
//    this->dataScene = new MItem();
//    this->addItem(this->dataScene);

//    this->dataScene->setPos(0, 0);
//    this->dataScene->setWidth(0);
//    this->dataScene->setHeight(0);

	if (m_type == SPEC_COMPARTMENT)
		m_rootItem = new MItem(":xml/scene-compartment.ui.xml", m_type, m_rootData);
	else
		m_rootItem = new MItem(":xml/scene-backbone.ui.xml", m_type, m_rootData);

	//add root Item
	m_rootItem->setId(m_id);
    addItem(m_rootItem);
	m_rootItem->setScene(this);

	m_trashItem = NULL;
	m_trashItem = new MItem(":xml/trash.ui.xml");
	addItem(m_trashItem);
	m_trashItem->setScene(this);

	//Displayed item in OverView TreeView
	SceneTreeItem* newItem = new SceneTreeItem(NULL, this);
	setTreeItem(newItem);

	setParent(this);
}

// Class MScene destructor
MScene::~MScene()
{
	qDebug() << "delete mscene";

	//递归调用
	//if child == NULL
	int nChildren = m_treeItem->childCount();
	if (nChildren != 0)
	{
		for (int i=0; i < nChildren; i++)
		{
			SceneTreeItem* pItem = (SceneTreeItem*)m_treeItem->child(i);
			if (pItem != NULL)
			{
				if(pItem->getScene() != NULL)
					delete pItem->getScene();
			}
		}
	}
	// return;
	
	//delete childScene;
	if (m_parent == this)	
	{
		delete m_treeItem;
	}
	else
	{
		m_parent->getTreeItem()->removeChild( m_treeItem );
		delete m_treeItem;
	}
	//

	//delete items
	for (int i = 0; i < dataCount; i++)
	{
		if (dataItem[i] != NULL)
			delete dataItem[i];
	}

	for (int i=0; i < m_nFree; i++)
	{
		delete dirtyItemPool[i];
		dirtyItemPool[i] = NULL;
	}

}

int MScene::addSpeciesItem(MItem *item)
{
	if (item == NULL)
		return -1;

	addItemEx(item);

	dataItem[dataCount] = item;
	dataCount++;

	qDebug() << "item count: " << dataCount;
	return dataCount-1;
}

void MScene::addItemEx(MItem *item)
{
	if (item == NULL)
		return;
	
    this->addItem(item);
	item->setScene(this);
}

void MScene::deletItemEx(MItem* item)
{
	bool bfound = false;
	int n = 0;
	if (item == NULL)
		return;

	while (n < dataCount)
	{
		if (item == dataItem[n])
		{
			bfound = true;
			break;
		}
		n++;
	}

	if (!bfound)
		return;

	deletItemEx(n);
}

void MScene::deletItemEx(int n)
{
	if ((n < 0) || (n >= dataCount))
		return;

	if (dataItem[n] != NULL)
	{
		this->removeItem(dataItem[n]);
	}

	if (m_nFree >= POOLNUM)
	{
		for (int i=0; i < POOLNUM; i++)
		{
			delete dirtyItemPool[i];
			dirtyItemPool[i] = NULL;
		}
		m_nFree = 0;
	}

	dirtyItemPool[m_nFree] = dataItem[n];

	for (int i = n; i < dataCount; i++)
	{
		dataItem[i] = dataItem[i+1];
		dataItem[i+1] = NULL;
	}

	dataCount--;
}

// Get the only selected item
MItem*
MScene::selectedItem() const
{
    QList<QGraphicsItem*> items = this->selectedItems();

    if (items.count() == 1) {
        return dynamic_cast<MItem*>(items.first());
    } else
        return 0;
}

// Bring selected item to front
void MScene::selectedItemBringToFront()
{
    MItem* item = this->selectedItem();

    if (item) {
        ++m_maxZValue;
        item->setZValue(m_maxZValue);
    }

    return;
}

// Send selected item to back
void MScene::selectedItemSendToBack()
{
    MItem* item = this->selectedItem();

    if (item) {
        --m_minZValue;
        item->setZValue(m_minZValue);
    }

    return;
}



//& Load data scene from XML
void MScene::loadXml(const QString& fileName)
{
}

//& Write data scene to XML
void MScene::writeXml(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return;
    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    for(int t = 0; t < dataCount; t++) {
        if (t == 0 || (dataItem[t - 1] == dataItem[t]->parentItem())) {
            writer.writeStartElement(dataItem[t]->text());

            if (dataItem[t]->data(0).toString() != "")
                writer.writeCharacters(dataItem[t]->data(0).toString());

        } else if (dataItem[t - 1]->parentItem() == dataItem[t]->parentItem()) {
            writer.writeEndElement();
            writer.writeStartElement(dataItem[t]->text());

            if (dataItem[t]->data(0).toString() != "")
                writer.writeCharacters(dataItem[t]->data(0).toString());

        } else {
            MItem* p = dataItem[t - 1];

            while (p->parentItem() && p->parentItem() != dataItem[t]->parentItem()) {
                writer.writeEndElement();
                p = (MItem*) (p->parentItem());
            }
            writer.writeEndElement();
            writer.writeStartElement(dataItem[t]->text());

            if (dataItem[t]->data(0).toString() != "")
                writer.writeCharacters(dataItem[t]->data(0).toString());

        }

    }
    writer.writeEndDocument();

    return;
}

void MScene::addChildScene(MScene *child)
{
	if ((m_treeItem != NULL) 
		&& (child != NULL))
	{
		qDebug() << "m_treeItem: " << (int)m_treeItem;
		SceneTreeItem* newItem = child->getTreeItem();
		m_treeItem->addChild(newItem);
		newItem->setSelected(true);
		m_treeItem->setSelected(false);
		m_treeItem->setExpanded(true);
		child->setParent(this);
	}
}

void MScene::deleteChildScene(int id)
{
}

void MScene::setParent(MScene* parent)
{
	m_parent = parent;
}

void MScene::setId(const QString& id)
{
	m_id = id;
}

QString& MScene::getId()
{
	return m_id;
}

/** 
 * @breif  
 * Set the item pointer of this scene
 * 
 * @Param item
 */
void MScene::setTreeItem(SceneTreeItem *item)
{
	if (item != NULL)
	{
		m_treeItem = item;
		item->setScene(this);
	}
}

SceneTreeItem* MScene::getTreeItem()
{
	return m_treeItem;
}

bool MScene::itemInCompartment(MItem *item)
{
	if (item == NULL)
		return false;

	if (item->collidesWithItem(m_rootItem))
		return true;
	else
		return false;
}

bool MScene::itemInTrash(MItem *item)
{
	if (item == NULL)
		return false;

	if (item->collidesWithItem(m_trashItem))
		return true;
	else
		return false;
}

bool MScene::itemDropped(MItem *item)
{
	if (item == NULL)
		return false;

	if (m_trashItem == NULL)
		return false;

	if (item == m_trashItem)
		return false;

	if ((m_browserItem == item)
			&& ((m_browserItem->x() != m_browserItemX)
			|| (m_browserItem->y() != m_browserItemY)))
	{
		qDebug() << "m_broserItem was dragged";
		m_browserItem = NULL;
	}

	if (item->collidesWithItem(m_trashItem))
	{
		item->deletOwnerScene();
		deletItemEx(item);
		return true;
	}
	else 
	{
		if (!itemInCompartment(item))
		{
			qDebug() << "invalid the scene";
			item->invalidOwnerScene(true);
		}
		else
		{
			item->invalidOwnerScene(false);
		}

		return true;
	}

	return false;
}

int MScene::childrenCount()
{
	if (m_treeItem != NULL)
		return m_treeItem->childCount();
}

MScene* MScene::getChild(int n)
{
	if (n < 0)
		return NULL;

	if (m_treeItem != NULL)
	{
		return ((SceneTreeItem*)m_treeItem->child(n))->getScene();
	}
}

QVector<MItem*>& MScene::getValidSubItems()
{
	QVector<MItem*> res;
	res.clear();

	for (int i=0; i<dataCount; i++)
	{
		if (dataItem[i] == NULL)
			continue;

		if (itemInCompartment(dataItem[i]))
			res.push_back(dataItem[i]);
	}
}

//QString MScene::generateComXmlString()
//{
//    qDebug() << "MSCene generate compartment xml string";
//    if (type() == SPEC_BACKBONE)
//    {
//        return "";
//    }

//    if (m_rootItem != NULL)
//    {
//        if (m_parent == this)
//            m_rootItem->getSpeciesData()->setParent("ROOT", SPEC_COMPARTMENT);
//        else
//            m_rootItem->getSpeciesData()->setParent(m_parent->getId(), m_parent->type());

//        return m_rootItem->getSpeciesData()->generateCompartmentXmlString();
//    }
//}

//QString MScene::generateSpeXmlString()
//{
//    qDebug() << "MSCene generate species xml string";
//    QString res;
//    res.clear();
//    if (type() == SPEC_BACKBONE)
//    {
//        if (m_rootItem == NULL)
//            return "";

//        res += "<species>\n";
//        res += "<id>"; res += m_rootItem->getSpeciesData()->id(); res += "</id>\n";
//        res += "<compartment>"; res+=m_rootItem->getSpeciesData()->parent(); res += "</compartment>\n";
//        res += "<initialConcentration>"; res += m_rootItem->getSpeciesData()->initConcentration(); res += "</initialConcentration>\n";
//        res += "<cnModel>\n";
//        res += "<listOfChains>\n";
//        res += "<chain>\n";
//        res += "<listOfParts>\n";


//        for (int i = 0; i < dataCount; i++)
//        {
//            MItem* tmp = dataItem[i];
//            if (tmp == NULL)
//                continue;
//            if (!itemInCompartment(tmp))
//                continue;

//            if (tmp->type() != SPEC_BIOBRICK)
//                continue;

//            res += tmp->getSpeciesData()->generatePartsXmlString();
//        }

//        res += "</listOfParts>\n";
//        res += "</chain>\n";
//        res += "</listOfChains>\n";
//        res += "</cnModel>\n";
//        res += "</species>\n";
//    }
//    else
//    {
//        for (int i=0; i < dataCount; i++)
//        {
//            MItem* tmp = dataItem[i];
//            if (tmp == NULL)
//                continue;
//            if (!itemInCompartment(tmp))
//                continue;

//            if (tmp->type() == SPEC_BACKBONE)
//                continue;

//            res += tmp->getSpeciesData()->generateSpeciesXmlString();
//        }
//    }

//    return res;
//}

void MScene::addBrowserItem(MItem *item)
{
	if (item == NULL)
	{
		return ;
	}

	//check position
	//if m_browserItem was not in init region, confirmed inserted in the scene
	//else delete the m_browserItem 
	//
	if (m_browserItem)
	{
		deletItemEx(m_browserItem);
		m_browserItem = NULL;
	}

	m_browserItem = item;
	m_browserItem->setX(m_browserItemX);
	m_browserItem->setY(m_browserItemY);
	addSpeciesItem(m_browserItem);
}

void MScene::invalidTree(bool invalid)
{
	if (m_treeItem == NULL)
		return;
	qDebug() << "Disable the tree item";
	m_treeItem->setDisabled(invalid);
}

/** 
 * @breif  
 *	This function is for Items in the Scene
 *	to ask for show setting widget of this item
 */
void MScene::showSettWidget(SettingWidget *set)
{
	if (set == NULL)
		return;

	if (m_setWidget != NULL)
		m_setWidget->close();

	m_setWidget = set;
	set->show();
}

/** 
 * @breif  
 *	This function is for Items in the Scene
 *	to ask for close setting widget of this item
 */
void MScene::closeSettWidget(SettingWidget *set)
{
	if (set == NULL)
		return;

	m_setWidget = NULL;
	set->close();
}

bool MScene::itemIsRootItem(MItem* item)
{
	if ((item == NULL) || (m_rootItem == NULL))
		return false;

	return item == m_rootItem;
}

MScene* MScene::itemApplyNewScene(MItem *item)
{
	if (item == NULL)
		return NULL;

	MScene* sce = new MScene(NULL, item->id(), item->type(), item);
//    addChildScene(item);
	return sce;
}
