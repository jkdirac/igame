#include "MainGraphicsView.h"
#include <QDebug>
#include "MItem.h"
#include "ClickableWidget.h"
#include "SceneViewWidget.h"
#include "SceneTreeItem.h"
#include "SceneManager.h"
#include "Species.h"
#include <QStringList>
#include <QList>
#include <QTreeWidgetItem>

#include <QFileDialog>
#include <QTextStream> 
#include <QFile> 
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QVector>

MainGraphicsView::MainGraphicsView(QWidget* parent)
{
	ui.setupUi(this);
	m_mainRect = QRect(300, 0, 700, 600);
			
	setState(START);
	connect(ui.com_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightComCombx(const QString &)));
	connect(ui.backbone_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightbackboneCombx(const QString &)));
	connect(ui.bio_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightBioCombx(const QString &)));
	connect(ui.compound_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightCompoundCombx(const QString &)));

//    connect(ui.const, highlightCompoundCombx(const QString &name)

	connect(ui.m_getStart, SIGNAL(pressed()), 
			                     this, SLOT(getStart()));
	connect(ui.m_loadbase, SIGNAL(pressed()), 
			                     this, SLOT(loadDb()));
	connect(ui.m_runDemo, SIGNAL(pressed()), 
			                     this, SLOT(runDemo()));
	connect(ui.m_scenNext, SIGNAL(pressed()), 
			                     this, SLOT(sceneNext()));

	connect(ui.m_scenBack, SIGNAL(pressed()), 
			                     this, SLOT(backToMainMenu()));

	m_scenemgr = SceneManager::getSceneManger();
	m_scenemgr->setMainWindow(this);

	connect(ui.m_overViewWidget, SIGNAL(itemClicked(QTreeWidgetItem* , int)),
		m_scenemgr, SLOT(broswerScene(QTreeWidgetItem* , int)));

	getCompartFromDb();
	getBackboneFromDb();
	getBiobricksFromDb();
	getCompoundFromDb();
//    setTreeView();
}

void MainGraphicsView::setState(STATE curState)
{
	setUi(curState);
	m_state = curState;

	if (m_state == GAMESCENE)
	{
		m_scenemgr->startShow();
	}
}

void MainGraphicsView::setUi(STATE curState)
{
	if (curState == START)
	{
		ui.m_overViewWidget->setVisible(false);

		ui.m_frame->setVisible(false);

		ui.m_getStart->setVisible(true);
		ui.m_loadbase->setVisible(true);
		ui.m_runDemo->setVisible(true);

		ui.m_scenNext->setVisible(false);
		ui.m_scenBack->setVisible(false);

		ui.m_fileBrowser->setVisible(false);
		ui.m_fileBrowser->setGeometry(QRect(0, 0, 0, 0));
		ui.m_mainGraph->setVisible(false);
		ui.m_mainGraph->setGeometry(QRect(0, 0, 0, 0));
		ui.m_logo->setVisible(true);
		ui.m_logo->setGeometry(rect());

		update();
	}

	if (curState == GAMESCENE)
	{
		qDebug() << "enter gamescene";
		ui.m_overViewWidget->setVisible(true);
		ui.m_frame->setVisible(true);

		ui.m_getStart->setVisible(false);
		ui.m_loadbase->setVisible(false);
		ui.m_runDemo->setVisible(false);

		ui.m_scenNext->setVisible(true);
        ui.m_scenNext->setStyleSheet(QString::fromUtf8("background-image: url(:/iGaME.images/button-review.png);"));
		ui.m_scenBack->setVisible(true);

		ui.m_fileBrowser->setVisible(false);
		ui.m_fileBrowser->setGeometry(QRect(0, 0, 0, 0));
		ui.m_mainGraph->setVisible(true);
		ui.m_mainGraph->setGeometry(m_mainRect);
		ui.m_logo->setVisible(false);
		ui.m_logo->setGeometry(QRect(0, 0, 0, 0));

		update();
	}

	if (curState == REVIEW)
	{
		qDebug() << "enter Review";
		ui.m_overViewWidget->setVisible(true);
		ui.m_frame->setVisible(false);

		ui.m_getStart->setVisible(false);
		ui.m_loadbase->setVisible(false);
		ui.m_runDemo->setVisible(false);

		ui.m_scenNext->setVisible(true);
        ui.m_scenNext->setStyleSheet(QString::fromUtf8("background-image: url(:/iGaME.images/button-simulate.png);"));
		ui.m_scenBack->setVisible(true);

		ui.m_fileBrowser->setVisible(true);
		ui.m_fileBrowser->setGeometry(m_mainRect);
		ui.m_mainGraph->setVisible(false);
		ui.m_mainGraph->setGeometry(QRect(0,0,0,0));
		ui.m_logo->setVisible(false);
		ui.m_logo->setGeometry(QRect(0, 0, 0, 0));

		update();
	}

	if (curState == SIMULATE)
	{
	}
}

void MainGraphicsView::setTreeView()
{
	SceneTreeItem* rootItem = m_scenemgr->getRootItem();
	QList<QTreeWidgetItem*> rootList; 
	rootList << (QTreeWidgetItem*)rootItem; 

	ui.m_overViewWidget->insertTopLevelItems(0, rootList); 
}

void MainGraphicsView::setBiobricks(QStringList &list)
{
	m_bioList = list;
	ui.bio_combx->addItems(m_bioList);
}

void MainGraphicsView::setBackbone(QStringList &list)
{
	m_backboneList = list;
	ui.backbone_combx->addItems(m_backboneList);
}

void MainGraphicsView::setCompartments(QStringList &list)
{
	m_compList = list;
	ui.com_combx->addItems(m_compList);
}

void MainGraphicsView::setCompounds(QStringList &list)
{
	m_compList = list;
	ui.compound_combx->addItems(m_compList);
}

void MainGraphicsView::createNewCompartment(const QString& partname)
{
	qDebug() << "idx change partName: " << partname;
}

void MainGraphicsView::activateCombx(const QString& partname)
{
	qDebug() << "activate partName: " << partname;
}

void MainGraphicsView::highlightComCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new ClickableWidget(":/xml/compartment.xml", SPEC_COMPARTMENT);
	item->setId(name);
	
	m_scenemgr->browserItem(item);
}

void MainGraphicsView::highlightbackboneCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new ClickableWidget(":xml/backbone.ui.xml", SPEC_BACKBONE);
	item->setId(name);
	
	m_scenemgr->browserItem(item);
}

void MainGraphicsView::highlightBioCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new MItem(":xml/biobrick.ui.xml", SPEC_BIOBRICK);
	item->setId(name);
	
	m_scenemgr->browserItem(item);
}

void MainGraphicsView::highlightCompoundCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new MItem(":xml/compound.ui.xml", SPEC_COMPOUNDS);
	item->setId(name);
	
	m_scenemgr->browserItem(item);
}

void MainGraphicsView::getStart()
{
	qDebug() << "HaHa get start pressed";
	if (m_state == START)
		setState(GAMESCENE);
}
	
void MainGraphicsView::sceneNext()
{
	qDebug() << "HaHa get start pressed";
	setState(REVIEW);
}

void MainGraphicsView::loadDb()
{
	qDebug() << "HaHa get start pressed";
	int bRes;
	QString path_name = QFileDialog::getExistingDirectory(this);

	if (path_name.isNull())
		return;

	QDirIterator dir_itr(path_name, QDir::Files, QDirIterator::Subdirectories);
	bdbXMLInterface db_interface;
	while (dir_itr.hasNext())
	{
		QString cur_pathname = dir_itr.next();

		QFileInfo cur_file(cur_pathname);
		if (!cur_file.isFile())
			continue;

		QString cur_filename = cur_file.fileName();

		//file name is ended with .xml?
		QString xml_ext(".xml");
		if (!cur_filename.endsWith(xml_ext, Qt::CaseInsensitive))
		{
			continue;
		}
		else 
		{
			int str_len = cur_filename.size();
			cur_filename.remove(str_len - 4, 4);
		}

		BdRetVal bsucc = db_interface.add_files(cur_pathname.toStdString(), cur_filename.toStdString());
		//add to directory
	}

	getCompartFromDb();
	getBackboneFromDb();
	getBiobricksFromDb();
	getCompoundFromDb();
}

void MainGraphicsView::runDemo()
{
}

void MainGraphicsView::getBiobricksFromDb()
{
	//get datas from bdinterface
	bdbXMLInterface inter;
	vector<string> res;
	try
	{
//        inter.get_ids_bycontainer(PART, res);
		inter.get_ids_byNodePath(PART, "//biobrick/@id", res);
	}
	catch (XmlException &se)
	{
		qDebug() << "read ids error " << se.what() << endl;
	}

	QStringList comList;
	comList.clear();
	for (int i=0; i < res.size(); i++)
	{
		if (res[i].empty())
			continue;

		qDebug() <<"id " << i << " " << res[i].c_str();
		QString qstr(res[i].c_str());
		comList << qstr;
	}
	/*cheat*/

	//        QStringList comList;
	//        comList << "abc" << "def" << "hij";
	setBiobricks(comList);
}

void MainGraphicsView::getBackboneFromDb()
{
	//get datas from bdinterface
	bdbXMLInterface inter;
	vector<string> res;
	try
	{
		inter.get_ids_byNodePath(PART, "//plasmidBackbone/@id", res);
	}
	catch (XmlException &se)
	{
		qDebug() << "read ids error " << se.what() << endl;
	}

	QStringList comList;
	comList.clear();
	for (int i=0; i < res.size(); i++)
	{
		if (res[i].empty())
			continue;
		qDebug() <<"id " << i << " " << res[i].c_str();
		QString qstr(res[i].c_str());
		comList << qstr;
	}
	/*cheat*/

	//        QStringList comList;
	//        comList << "abc" << "def" << "hij";
	setBackbone(comList);
}

void MainGraphicsView::getCompartFromDb()
{
	//get datas from bdinterface
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
	comList.clear();
	for (int i=0; i < res.size(); i++)
	{
		if (res[i].empty())
			continue;
		qDebug() <<"id " << i << " " << res[i].c_str();
		QString qstr(res[i].c_str());
		comList << qstr;
	}
	/*cheat*/

	//        QStringList comList;
	//        comList << "abc" << "def" << "hij";
	setCompartments(comList);
}

void MainGraphicsView::getCompoundFromDb()
{
	//get datas from bdinterface
	bdbXMLInterface inter;
	vector<string> res;
	try
	{
		inter.get_ids_byNodePath(PART, "//compound/@id", res);
	}
	catch (XmlException &se)
	{
		qDebug() << "read ids error " << se.what() << endl;
	}

	QStringList comList;
	comList.clear();
	for (int i=0; i < res.size(); i++)
	{
		if (res[i].empty())
			continue;
		qDebug() <<"id " << i << " " << res[i].c_str();
		QString qstr(res[i].c_str());
		comList << qstr;
	}
	/*cheat*/

	//        QStringList comList;
	//        comList << "abc" << "def" << "hij";
	setCompounds(comList);
}

void MainGraphicsView::backToMainMenu()
{
	m_scenemgr->deleteAllScene();
	setState(START);
	return;
}

void MainGraphicsView::compartmentScene()
{
	ui.com_combx->setEnabled(true);
	ui.backbone_combx->setEnabled(true);
	ui.bio_combx->setEnabled(false);
	ui.compound_combx->setEnabled(false);
}

void MainGraphicsView::plasmidScene()
{
	ui.com_combx->setEnabled(false);
	ui.backbone_combx->setEnabled(false);
	ui.bio_combx->setEnabled(true);
	ui.compound_combx->setEnabled(true);
}
