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
	SceneTreeItem* rootItem = mgr->getRootItem();

}

void SceneViewWidget::setTreeRootItem(QTreeWidgetItem* rootItem)
{
	qDebug() << "--view widget start: rootItem: " << (int)rootItem;
	QList<QTreeWidgetItem*> rootList; 
	rootList << (QTreeWidgetItem*)rootItem; 
//    SceneTreeItem* leafItem = new SceneTreeItem("test");
//    rootItem->addChild(leafItem);
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
	ui.overViewWidget->insertTopLevelItems(0, rootList); 
}
