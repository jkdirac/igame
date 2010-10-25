#include "SceneViewWidget.h"
#include <QStringList>
#include <QList>
#include <QTreeWidgetItem>

SceneViewWidget::SceneViewWidget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
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
//    tree->insertTopLevelItems(0, rootList); 
}
