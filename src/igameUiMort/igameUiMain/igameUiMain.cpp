#include <MosQt>
#include "IdSelWidget.h"
#include "SceneViewWidget.h"
#include "SceneManager.h"
#include "ClickableWidget.h"
#include "GlobalSetting.h"
#include "CoreException.h"
#include "MainGraphicsView.h"

#include <QMessageBox>
#include <QObject>

namespace uiObjects {

MView * mainView;
MScene * mainScene;
MWidget * w;
};

using namespace uiObjects;

bool init_global_dir_setting()
{
	QDir dir = QDir::home();

	QString igame_home_path = ".igame";

	bool b_succ = true;

	if (dir.exists())
	{
		if (!dir.exists(igame_home_path))
		{
			b_succ = dir.mkdir(igame_home_path);
		}
	}

	if (!b_succ)
	{
		dir = QDir::current();
		if (!dir.exists(igame_home_path))
		{
			b_succ = dir.mkdir(igame_home_path);
		}
	}

	if (b_succ)
	{
		QString dir_path = dir.path() + "/" +  igame_home_path;
		set_igame_home(dir_path.toLatin1().constData());
	}
	else
	{
		//set current file
		set_igame_home(QDir::currentPath().toLatin1().constData());
		// notify the user check the file system full 
		// or have not the write permission of path %HOME and "./" 
	}

	qDebug() << "home dir: " << get_igame_home_dir();
	return b_succ;
}

BEGIN(demoUiXml)
{
	bool bSucc;
	bSucc = init_global_dir_setting();
	if (!bSucc)
	{
		QMessageBox::warning(NULL, QObject::tr("Application"),
				QObject::tr("iGame Cannot create file in home directory,\nplease check the file system available space or get the permission.")
				);
		return 0;
	}

	SceneManager* sceneMgr = SceneManager::getSceneManger();

	int deskWidth = QApplication::desktop()->width();
	int deskheight = QApplication::desktop()->height();

//    MView* mainview = new MView();

//    mainview->setWindowTitle("demoUiXml");
//    mainview->showMaximized();
//    mainview->setSceneRect(0, 0, deskWidth, deskheight);
//    mainview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    mainview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	MainGraphicsView* mainWindow = new MainGraphicsView(NULL);

//    mainScene = new MScene();
//    mainScene->loadXml(":demoUiXml.ui.xml");
//    mainScene->setBackgroundBrush(QPixmap(":/images/demobg.png"));

//    MItem* Item = new MItem(":xml/compartment.ui.xml");
//    ClickableWidget* cItem = new ClickableWidget(":demoUiXml.ui.xml");
//    int Item_id = mainScene->addItemEx(Item);

//    ClickableWidget* cItem = new ClickableWidget(":xml/compartment.ui.xml");
//    ClickableWidget* cItem = new ClickableWidget(":demoUiXml.ui.xml");
//    int Item_clickable_id = mainScene->addItemEx(cItem);
	sceneMgr->setMainView(mainWindow->ui.m_mainGraph);
//    sceneMgr->startShow();
	mainWindow->show();
}
END(demoUiXml)

BEGIN_EVENTS(demoUiXml)
{
    ;
    
}
END_EVENTS(demoUiXml)
