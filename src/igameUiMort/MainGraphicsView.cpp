#include "MainGraphicsView.h"
#include <QDebug>
#include "MItem.h"
#include "ClickableWidget.h"
#include "SceneViewWidget.h"
#include "SceneTreeItem.h"
#include "SceneManager.h"
#include <QStringList>
#include <QList>
#include <QTreeWidgetItem>

MainGraphicsView::MainGraphicsView(QWidget* parent)
{
	ui.setupUi(this);

	connect(ui.com_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightCombx(const QString &)));
	m_scenemgr = SceneManager::getSceneManger();
	m_scenemgr->setMainWindow(this);

	//get datas from bdinterface
	/*
	bdbXMLInterface inter;
	vector<string> res;
	try
	{
		inter.get_ids_bycontainer(COMPARTMENT, res);
	}
	catch (XmlException &se)
	{
		qDebug() << "read ids error " << se.what() << endl;
	}

	QStringList comList;
	for (int i=0; i < res.size(); i++)
	{
		qDebug() <<"id " << i << " " << res[i].c_str();
		QString qstr(res[i].c_str());
		comList << qstr;
	}
	*/
	/*cheat*/

	QStringList comList;
	comList << "abc" << "def" << "hij";
	setCompartments(comList);

//    setTreeView();
}

void MainGraphicsView::setTreeView()
{
	SceneTreeItem* rootItem = m_scenemgr->getRootItem();
	QList<QTreeWidgetItem*> rootList; 
	rootList << (QTreeWidgetItem*)rootItem; 
//    QTreeWidget* tree = ui.overViewWidget;

//    tree->setColumnCount(1); 
//    QTreeWidgetItem *root = new QTreeWidgetItem(tree, QStringList(QString("Root"))); 
//    QTreeWidgetItem *leaf = new QTreeWidgetItem(root, QStringList(QString("Leaf 1"))); 
//    root->addChild(leaf); 
//    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2"))); 
//    root->addChild(leaf2); 

//    QTreeWidgetItem *leaf3 = new QTreeWidgetItem(leaf, QStringList(QString("Leaf 3"))); 
//    leaf->addChild(leaf3); 

//    QList<QTreeWidgetItem *> rootList; 
//    rootList << root; 
	ui.m_overViewWidget->insertTopLevelItems(0, rootList); 
}

void MainGraphicsView::setCompartments(QStringList &list)
{
	m_compList = list;
	ui.com_combx->addItems(m_compList);
}

void MainGraphicsView::createNewCompartment(const QString& partname)
{
	qDebug() << "idx change partName: " << partname;
}

void MainGraphicsView::activateCombx(const QString& partname)
{
	qDebug() << "activate partName: " << partname;
}

void MainGraphicsView::highlightCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new ClickableWidget(":xml/new-compartment.ui.xml");
	item->setId(name);
	
	m_scenemgr->browserItem(item);
}
