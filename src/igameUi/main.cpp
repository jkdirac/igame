#include <QApplication>
#include <QDir>
#include <QString>
#include "mainWindow.h"
#include "globalSetting.h"
#include "CoreException.h"

bool init_global_dir_setting()
{
	QDir dir = QDir::home();

	QString igame_home_path = "igame";

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

	return b_succ;
}

int main(int argc, char *argv[])
{
	bool bSucc;
	bSucc = init_global_dir_setting();
	if (!bSucc)
		return 0;

	Q_INIT_RESOURCE(mainWindow);

	QApplication app(argc, argv);
	app.setOrganizationName("HELLO JIANGKUN");
	app.setApplicationName("Hello SBML");

	MainWindow mainWin(NULL);
	mainWin.setQApp(&app);
	mainWin.show();

	return app.exec();
}
