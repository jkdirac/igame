/********************************************************************
*
*            Author: jkdirac- jiangkun1@gmail.com
*
*
*
*            Last modified: 2010-08-03 20:31
*
*            Filename: mainWindow.cpp
*
*            Description: .
*
*******************************************************************/
#include <QtGui>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream> 
#include <QFile> 
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QVector>

#include "mainWindow.h"
#include "bdbInterface.h"

#include "driver.h"
#include "CopsiInterface.h"

MainWindow::MainWindow( QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi( this );
	connect( ui.actionAnaly_sbml, SIGNAL(triggered()), this, SLOT(analySBML()) );
	connect( ui.actionOpen, SIGNAL(triggered()), this, SLOT(open()) );
	connect( ui.actionImport_SBML, SIGNAL(triggered()), this, SLOT(openSBML()) );
	connect( ui.actionImport_data, SIGNAL(triggered()), this, SLOT(import_data2db()) );
}

void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty())
		loadFile(fileName);
}

void MainWindow::analySBML()
{
	QString fileName = QFileDialog::getOpenFileName(this);

	if (fileName.isNull())
		return;
}

void MainWindow::import_data2db()
{
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

	Driver driver;
	try
	{
		bool errno = driver.beginSimulation ();
		copsi_entry("network.xml", m_app);
	}
	catch (StrCacuException &se)
	{
		cout << "exceptions" << endl;
	}
}

void MainWindow::setQApp(QApplication* app)
{
	m_app = app;
}

void MainWindow::openSBML()
{
}

void MainWindow::loadFile(const QString &fileName)
{
}

void MainWindow::setCurrentFile(const QString &fileName)
{
}

void MainWindow::odeAnalysis() //no used
{
}
