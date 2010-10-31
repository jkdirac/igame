#include "OrderedScene.h"
#include "MItem.h"
#include <QtAlgorithms>
#include <QDebug>

OrderedScene::OrderedScene(const QString &id, SPECIESTYPE type, MItem *root) : MScene(NULL,id ,type, root)
{
//    m_rootItem = new MItem(":xml/scene-backm_bone.ui.xml", m_type);
//    m_rootItem->setId(m_id);
	m_margin = 0;

	m_height = 70;
	m_x = m_rootItem->x();
	m_y = m_rootItem->y();

	m_bone = new MItem(":xml/biobrick.ui.xml");
	m_bone->setY(m_y);
	m_bone->setX(m_x+2);
	m_bone->setMovable(false);
	m_bioWidth = m_bone->width();

	m_head = new MItem(":xml/biobrick.ui.xml");
	m_head->setX(m_x+2);
	m_head->setY(m_y);
	m_head->setId("TEX_100_head");
	m_head->setMovable(false);

	m_tail = new MItem(":xml/biobrick.ui.xml");
	m_tail->setX(m_x+1);
	m_tail->setY(m_y);
	m_tail->setId("TEX_100_tail");
	m_tail->setMovable(false);

	addSpeciesItem(m_bone);
	addSpeciesItem(m_head);
	addSpeciesItem(m_tail);

	m_validItem.push_back(m_bone);
	m_validItem.push_back(m_head);
	m_validItem.push_back(m_tail);

	rearrangeItem();
	adjustItemPos();
}

bool OrderedScene::itemDropped(MItem *item)
{
	MScene::itemDropped(item);

	if (item == NULL)
		return false;

	qDebug() << "item dropped in OrderedScene" << item->x() <<" " << item->y();

	bool bInValid = false;
	QList<MItem*>::iterator itr;
	for (itr = m_validItem.begin(); 
			itr != m_validItem.end();
			itr++)
	{
		if (*itr == item)
		{
			bInValid = true;
			break;
		}
	}

	//
	if ( itemInCompartment(item) &&
			((item->x() > m_head->x())
			 || (item->x() < m_tail->x())))
	{
		qDebug() << "invalid input in " << item->x() << " head: " << m_head->x() << " tail: " << m_tail->x();
		item->setY(m_y - 100);
	}

	if (!itemInCompartment(item))
	{
		if (bInValid)
			m_validItem.erase(itr);
	}
	else
	{
		if (!bInValid)
			m_validItem.push_back(item);

		insertItem(item);
	}
	rearrangeItem();
	adjustItemPos();
	update();
}

void OrderedScene::insertItem(MItem *item)
{
}

bool OrderedScene::posxGreatethan(MItem* it1, MItem* it2)
{
	return it1->x() < it2->x();
}

void OrderedScene::rearrangeItem()
{
	QList<MItem*>::iterator itr;
	for (itr = m_validItem.begin(); 
			itr != m_validItem.end();
			itr++)
	{
		if (!itemInCompartment(*itr))
		{
			m_validItem.erase(itr);
		}
	}

	qSort(m_validItem.begin(), m_validItem.end(), OrderedScene::posxGreatethan);
	for (itr = m_validItem.begin(); 
			itr != m_validItem.end();
			itr++)
	{
		qDebug() <<"x: " << (*itr)->x();
	}
}

void OrderedScene::adjustItemPos()
{
	//ignore those biobrick not on the line
	int nNum = m_validItem.size();
	int startX;

	m_width = nNum * m_bioWidth + (nNum-1) * m_margin + 50;
	m_height = 70;

	startX = m_x - (m_width - 10) / 2 + m_bioWidth/2;
	for (int i=0; i < nNum; i++)
	{
		int item_x = startX + i * m_bioWidth;
		m_validItem[i]->setX(item_x);
		m_validItem[i]->setY(m_y);
		qDebug() << "item " << i << " " << item_x ;
	}

	m_rootItem->setX(m_x);
	m_rootItem->setY(m_y);
	m_rootItem->setWidth(m_width);
	m_rootItem->setHeight(m_height);
	qDebug() << "root item " << m_x << " " << m_y << " " << m_width << " " << m_height;
}
