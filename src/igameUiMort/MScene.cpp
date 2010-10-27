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

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QFile>
#include <QXmlStreamReader>
#include <QColor>
#include <QXmlStreamWriter>

#include <iostream>
#include <QDebug>

// Class MScene constructor
MScene::MScene(QObject* parent)
	: QGraphicsScene(parent)
	, dataCount(0)
	, m_minZValue(0)
	, m_maxZValue(0)
	, m_treeItem(NULL)
	  ,m_overviewWidget(NULL)
{
    this->dataScene = new MItem();
    this->addItem(this->dataScene);

    this->dataScene->setPos(0, 0);
    this->dataScene->setWidth(0);
    this->dataScene->setHeight(0);

	IdSelWidget* IdSel = new IdSelWidget(NULL);
	selWidget = (MWidget*)addWidget(IdSel);
	selWidget->setX(0);
	selWidget->setY(0);

	SceneTreeItem* newItem = new SceneTreeItem(NULL, this);
	setTreeItem(newItem);
}

MScene::MScene(QObject* parent, const QString& id)
	: QGraphicsScene(parent)
	, dataCount(0)
	, m_minZValue(0)
	, m_maxZValue(0)
	, m_treeItem(NULL)
	  ,m_overviewWidget(NULL)
{
	m_id = id;
    this->dataScene = new MItem();
    this->addItem(this->dataScene);

    this->dataScene->setPos(0, 0);
    this->dataScene->setWidth(0);
    this->dataScene->setHeight(0);

	SceneTreeItem* newItem = new SceneTreeItem(NULL, this);
	setTreeItem(newItem);
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
			delete pItem->getScene();
		}
	}
	// return;
	
	//call child.deletChildScene
	
	//delete childScene;
	delete m_treeItem;

	//
    delete dataScene;
	delete selWidget;
	delete m_overviewWidget;

	//delete items
	for (int i = 0; i < dataCount; i++)
	{
		delete dataItem[i];
	}
}

int MScene::addItemEx(MItem *item)
{
	if (item == NULL)
		return -1;
	
	dataItem[dataCount] = item;
	dataCount++;

    this->addItem(item);
	item->setScene(this);

	return dataCount-1;
}

void MScene::deletItemEx(int n)
{
	if ((n < 0) || (n > dataCount))
		return;

	if (dataItem[n] != NULL)
	{
		this->removeItem(dataItem[n]);
		delete dataItem[n];
	}

	for (int i = n; i < dataCount; i++)
	{
		dataItem[i] = dataItem[i+1];
		dataItem[i+1] = NULL;
	}

	dataCount--;
}

// Get the only selected item
MItem* MScene::selectedItem() const
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
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;
    QXmlStreamReader reader(&file);
    MItem* p = this->dataScene;

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            QString name = reader.name().toString();
            dataItem[dataCount++] = new MItem();
            dataItem[dataCount - 1]->setParentItem(p);

            if (reader.attributes().hasAttribute("id"))
                dataItem[dataCount - 1]->setId(reader.attributes().value("id").toString());

            if (reader.attributes().hasAttribute("name"))
                dataItem[dataCount - 1]->setName(reader.attributes().value("name").toString());
            else
                dataItem[dataCount - 1]->setText(name);

            if (reader.attributes().hasAttribute("category"))
                dataItem[dataCount - 1]->setCategory(reader.attributes().value("category").toString());

            if (reader.attributes().hasAttribute("x"))
                dataItem[dataCount - 1]->setX(reader.attributes().value("x").toString().toDouble());
            else
                dataItem[dataCount - 1]->setX(200);

            if (reader.attributes().hasAttribute("y"))
                dataItem[dataCount - 1]->setY(reader.attributes().value("y").toString().toDouble());
            else
                dataItem[dataCount - 1]->setY(50);

            if (reader.attributes().hasAttribute("zValue"))
                dataItem[dataCount - 1]->setZValue(reader.attributes().value("zValue").toString().toDouble());

            if (reader.attributes().hasAttribute("toolTip"))
                dataItem[dataCount - 1]->setToolTip(reader.attributes().value("toolTip").toString());

            if (reader.attributes().hasAttribute("isVisible"))
                dataItem[dataCount - 1]->setVisible(reader.attributes().value("isVisible").toString().toInt());

            if (reader.attributes().hasAttribute("color"))
                dataItem[dataCount - 1]->setColor(QColor(reader.attributes().value("color").toString()));

            if (reader.attributes().hasAttribute("width"))
                dataItem[dataCount - 1]->setWidth(reader.attributes().value("width").toString().toDouble());
            else
                dataItem[dataCount - 1]->setWidth(100);

            if (reader.attributes().hasAttribute("height"))
                dataItem[dataCount - 1]->setHeight(reader.attributes().value("height").toString().toDouble());
            else
                dataItem[dataCount - 1]->setHeight(50);

            if (reader.attributes().hasAttribute("isSelectable"))
                dataItem[dataCount - 1]->setSelectable(reader.attributes().value("isSelectable").toString().toInt());
            else
                dataItem[dataCount - 1]->setSelectable(true);

            if (reader.attributes().hasAttribute("isMouseOverSelectable"))
                dataItem[dataCount - 1]->setMouseOverSelectable(reader.attributes().value("isMouseOverSelectable").toString().toInt());
            else
                dataItem[dataCount - 1]->setMouseOverSelectable(false);

            if (reader.attributes().hasAttribute("isMovable"))
                dataItem[dataCount - 1]->setMovable(reader.attributes().value("isMovable").toString().toInt());
            else
                dataItem[dataCount - 1]->setMovable(true);

            if (reader.attributes().hasAttribute("isOutlineAvailable"))
                dataItem[dataCount - 1]->setOutlineAvailable(reader.attributes().value("isOutlineAvailable").toString().toInt());

            if (reader.attributes().hasAttribute("outlineColor"))
                dataItem[dataCount - 1]->setOutlineColor(QColor(reader.attributes().value("outlineColor").toString()));

            if (reader.attributes().hasAttribute("outlineWidth"))
                dataItem[dataCount - 1]->setOutlineWidth(reader.attributes().value("outlineWidth").toString().toDouble());

            if (reader.attributes().hasAttribute("isFigureVisible"))
                dataItem[dataCount - 1]->setFigureVisible(reader.attributes().value("isFigureVisible").toString().toInt());

            if (reader.attributes().hasAttribute("figure"))
                dataItem[dataCount - 1]->setFigure(reader.attributes().value("figure").toString());

            if (reader.attributes().hasAttribute("figureColor"))
                dataItem[dataCount - 1]->setFigureColor(QColor(reader.attributes().value("figureColor").toString()));

            if (reader.attributes().hasAttribute("isAlternativeFigureAvailable"))
                dataItem[dataCount - 1]->setAlternativeFigureAvailable(reader.attributes().value("isAlternativeFigureAvailable").toString().toInt());

            if (reader.attributes().hasAttribute("alternativeFigure"))
                dataItem[dataCount - 1]->setAlternativeFigure(reader.attributes().value("alternativeFigure").toString());

            if (reader.attributes().hasAttribute("alternativeFigureColor"))
                dataItem[dataCount - 1]->setAlternativeFigureColor(QColor(reader.attributes().value("alternativeFigureColor").toString()));

            if (reader.attributes().hasAttribute("isTextVisible"))
                dataItem[dataCount - 1]->setTextVisible(reader.attributes().value("isTextVisible").toString().toInt());

            if (reader.attributes().hasAttribute("text"))
                dataItem[dataCount - 1]->setText(reader.attributes().value("text").toString());
            else
                dataItem[dataCount - 1]->setText(name);

            if (reader.attributes().hasAttribute("textColor"))
                dataItem[dataCount - 1]->setTextColor(QColor(reader.attributes().value("textColor").toString()));

            if (reader.attributes().hasAttribute("isAlternativeTextAvailable"))
                dataItem[dataCount - 1]->setAlternativeTextAvailable(reader.attributes().value("isAlternativeTextAvailable").toString().toInt());

            if (reader.attributes().hasAttribute("alternativeText"))
                dataItem[dataCount - 1]->setAlternativeText(reader.attributes().value("alternativeText").toString());

            if (reader.attributes().hasAttribute("alternativeTextColor"))
                dataItem[dataCount - 1]->setAlternativeTextColor(QColor(reader.attributes().value("alternativeTextColor").toString()));

            if (reader.attributes().hasAttribute("pixmap"))
                dataItem[dataCount - 1]->setPixmap(reader.attributes().value("pixmap").toString());

            if (reader.attributes().hasAttribute("isPixmapVisible"))
                dataItem[dataCount - 1]->setPixmapVisible(reader.attributes().value("isPixmapVisible").toString().toInt());

            if (reader.attributes().hasAttribute("alternativePixmap"))
                dataItem[dataCount - 1]->setAlternativePixmap(reader.attributes().value("alternativePixmap").toString());

            if (reader.attributes().hasAttribute("isAlternativePixmapAvailable"))
                dataItem[dataCount - 1]->setAlternativePixmapAvailable(reader.attributes().value("isAlternativePixmapAvailable").toString().toInt());

            if (reader.attributes().hasAttribute("image"))
                dataItem[dataCount - 1]->setImage(reader.attributes().value("image").toString());

            if (reader.attributes().hasAttribute("isImageVisible"))
                dataItem[dataCount - 1]->setImageVisible(reader.attributes().value("isImageVisible").toString().toInt());

            if (reader.attributes().hasAttribute("alternativeImage"))
                dataItem[dataCount - 1]->setAlternativeImage(reader.attributes().value("alternativeImage").toString());

            if (reader.attributes().hasAttribute("isAlternativeImageAvailable"))
                dataItem[dataCount - 1]->setAlternativeImageAvailable(reader.attributes().value("isAlternativeImageAvailable").toString().toInt());

            p = dataItem[dataCount - 1];

        } else if (reader.isEndElement())
            p = (MItem*) (p->parentItem());
        else if (reader.isCharacters()) {
            QString characters = reader.text().toString();

            if (characters != "" && characters != "\n" && characters != "\r" && characters !="\r\n")
                dataItem[dataCount - 1]->setData(0, characters);
        }

        reader.readNext();
    }

    return;
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
//        SceneTreeItem* newItem = new SceneTreeItem((QTreeWidgetItem*)m_treeItem, child);
		m_treeItem->addChild(newItem);
//        child->setTreeItem(newItem);
	}
}

void MScene::deleteChildScene(int id)
{
}

void MScene::setParent(MScene* parent)
{
	m_parent = parent;
}

QVector<MScene*>& MScene::getChildScene()
{
	return m_childern;
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

/** 
 * @breif  put tree data to m_overviewWidgetto show
 * 
 * @Param item
 */
void MScene::showTreeWidget(SceneTreeItem *item)
{
	if (item != NULL)
		m_overviewWidget->setTreeRootItem(item);
}

/** 
 * @breif 
 * Put list data to QCombox widget to select 
 * 
 * @Param item
 */
void MScene::showSelWidget(QStringList* list)
{
}
