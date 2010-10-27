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
	m_mainRect = QRect(200, 100, 600, 600);
	setState(START);
	connect(ui.com_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightComCombx(const QString &)));
	connect(ui.spe_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightSpeCombx(const QString &)));
	connect(ui.bio_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightBioCombx(const QString &)));
	connect(ui.m_getStart, SIGNAL(pressed()), 
			                     this, SLOT(getStart()));
	connect(ui.m_loadbase, SIGNAL(pressed()), 
			                     this, SLOT(loadDb()));
	connect(ui.m_runDemo, SIGNAL(pressed()), 
			                     this, SLOT(runDemo()));
	connect(ui.m_scenNext, SIGNAL(pressed()), 
			                     this, SLOT(sceneNext()));
	m_scenemgr = SceneManager::getSceneManger();
	m_scenemgr->setMainWindow(this);

	getCompartFromDb();
	getSpeciesFromDb();
	getPartsFromDb();

//    setTreeView();
}

void MainGraphicsView::setState(STATE curState)
{
	setUi(curState);
	m_state = curState;
}

void MainGraphicsView::setUi(STATE curState)
{
	if (curState == START)
	{
		ui.m_overViewWidget->setVisible(false);
		ui.label->setVisible(false);
		ui.label_2->setVisible(false);
		ui.label_3->setVisible(false);
		ui.com_combx->setVisible(false);
		ui.bio_combx->setVisible(false);
		ui.spe_combx->setVisible(false);

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
		ui.m_logo->setGeometry(m_mainRect);

		update();
	}

	if (curState == GAMESCENE)
	{
		qDebug() << "enter gamescene";
		ui.m_overViewWidget->setVisible(true);
		ui.label->setVisible(true);
		ui.label_2->setVisible(true);
		ui.label_3->setVisible(true);
		ui.com_combx->setVisible(true);
		ui.bio_combx->setVisible(true);
		ui.spe_combx->setVisible(true);

		ui.m_getStart->setVisible(false);
		ui.m_loadbase->setVisible(false);
		ui.m_runDemo->setVisible(false);

		ui.m_scenNext->setVisible(true);
        ui.m_scenNext->setText(QApplication::translate("MainGraphicsView", "Review", 
					0, QApplication::UnicodeUTF8));
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
		ui.label->setVisible(false);
		ui.label_2->setVisible(false);
		ui.label_3->setVisible(false);
		ui.com_combx->setVisible(false);
		ui.bio_combx->setVisible(false);
		ui.spe_combx->setVisible(false);

		ui.m_getStart->setVisible(false);
		ui.m_loadbase->setVisible(false);
		ui.m_runDemo->setVisible(false);

		ui.m_scenNext->setVisible(true);
        ui.m_scenNext->setText(QApplication::translate("MainGraphicsView", "Simulate", 0, QApplication::UnicodeUTF8));
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

void MainGraphicsView::setSpecies(QStringList &list)
{
	m_speList = list;
	ui.spe_combx->addItems(m_speList);
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

void MainGraphicsView::highlightComCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new ClickableWidget(":xml/new-compartment.ui.xml");
	item->setId(name);
	
	m_scenemgr->browserItem(item);
}

void MainGraphicsView::highlightSpeCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new ClickableWidget(":xml/new-species.ui.xml");
	item->setId(name);
	
	m_scenemgr->browserItem(item);
}

void MainGraphicsView::highlightBioCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new ClickableWidget(":xml/biobrick.ui.xml");
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

	getPartsFromDb();
	getSpeciesFromDb();
	getPartsFromDb();
}

void MainGraphicsView::runDemo()
{
}

void MainGraphicsView::getPartsFromDb()
{
	//get datas from bdinterface
	bdbXMLInterface inter;
	vector<string> res;
	try
	{
		inter.get_ids_bycontainer(PART, res);
	}
	catch (XmlException &se)
	{
		qDebug() << "read ids error " << se.what() << endl;
	}

	QStringList comList;
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

void MainGraphicsView::getSpeciesFromDb()
{
	//get datas from bdinterface
	bdbXMLInterface inter;
	vector<string> res;
	try
	{
		inter.get_ids_bycontainer(SPECIES, res);
	}
	catch (XmlException &se)
	{
		qDebug() << "read ids error " << se.what() << endl;
	}

	QStringList comList;
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
	setSpecies(comList);
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
