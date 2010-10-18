#include <QApplication>
#include <QDir>
#include "mainWindow.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(mainWindow);

	QApplication app(argc, argv);
	app.setOrganizationName("HELLO JIANGKUN");
	app.setApplicationName("Hello SBML");

	MainWindow mainWin(NULL);
	mainWin.show();

	return app.exec();
}
