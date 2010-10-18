#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainWindow.h"

class QAction;
class QMenu;
class QPlainTextEdit;

class MainWindow: public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow( QWidget* parent );
		void setQApp(QApplication* app);

		private slots:
			void open();
		void openSBML();
		void import_data2db();
		void analySBML();
		void odeAnalysis(); //no used

	private:
		Ui::MainWindow ui;
		void setCurrentFile(const QString &fileName);
		void loadFile(const QString &fileName);
		QApplication* m_app;
};

#endif
