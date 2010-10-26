#include "SceneViewWidget.h"
#include "SceneTreeItem.h"
#include "SceneManager.h"
#include <QStringList>
#include <QList>
#include <QTreeWidgetItem>
#include <QDebug>

SceneViewWidget::SceneViewWidget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);

	ui.overViewWidget->setColumnCount(1);
	SceneManager* mgr = SceneManager::getSceneManger();
}

void SceneViewWidget::setTreeRootItem(SceneTreeItem* rootItem)
{
	qDebug() << "--view widget start: rootItem: " << (int)rootItem;
	if (rootItem->getScene())
	{
		qDebug() << rootItem->getScene()->getId();
		qDebug() << rootItem->childCount();
	}

	/**/
//    SceneTreeItem* leafItem = new SceneTreeItem("test");
//    rootItem->addChild(leafItem);
//    QTreeWidget* tree = ui.overViewWidget;

//    tree->setColumnCount(2); 
//    QTreeWidgetItem *root = new QTreeWidgetItem(tree, QStringList(QString("Root"))); 
//    QTreeWidgetItem *leaf = new QTreeWidgetItem(root, QStringList(QString("Leaf 1"))); 
//    root->addChild(leaf); 
//    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2"))); 
//    root->addChild(leaf2); 

//    QTreeWidgetItem *leaf3 = new QTreeWidgetItem(leaf, QStringList(QString("Leaf 3"))); 
//    leaf->addChild(leaf3); 

//    QTreeWidgetItem *root1 = new QTreeWidgetItem(tree, QStringList(QString("Root1"))); 
//    QList<QTreeWidgetItem *> rootList; 
//    rootList << root; 
	/**/

	QList<QTreeWidgetItem*> rootList; 
	rootList << (QTreeWidgetItem*)rootItem; 
	ui.overViewWidget->insertTopLevelItems(0, rootList); 

	SceneTreeItem* test1 = new SceneTreeItem("test1");
	rootItem->addChild(test1);
}
