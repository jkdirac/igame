#include "IdSelWidget.h"
#include <QDebug>
#include "MItem.h"
#include "ClickableWidget.h"

using namespace std;

IdSelWidget::IdSelWidget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);

	scenemgr = SceneManager::getSceneManger();
	connect(ui.com_combx, SIGNAL(currentIndexChanged(const QString &)), 
			                     this, SLOT(createNewCompartment(const QString &)));
	connect(ui.com_combx, SIGNAL(activated(const QString &)), 
			                     this, SLOT(activateCombx(const QString &)));
	connect(ui.com_combx, SIGNAL(highlighted(const QString &)), 
			                     this, SLOT(highlightCombx(const QString &)));

	//get datas from bdinterface
	/*
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
		qDebug() <<"id " << i << " " << res[i].c_str();
		QString qstr(res[i].c_str());
		comList << qstr;
	}
	*/
	/*cheat*/
	QStringList comList;
	comList << "abc" << "bcd" << "def";

	setCompartments(comList);
}


void IdSelWidget::setCompartments(QStringList &list)
{
	m_compList = list;
	ui.com_combx->addItems(m_compList);
}

void IdSelWidget::createNewCompartment(const QString& partname)
{
	qDebug() << "idx change partName: " << partname;
}

void IdSelWidget::activateCombx(const QString& partname)
{
	qDebug() << "activate partName: " << partname;
}

void IdSelWidget::highlightCombx(const QString &name)
{
	qDebug() << "highligth partName: " << name;

	MItem* item = new ClickableWidget(":xml/compartment.ui.xml");
	item->setId(name);
	
	scenemgr->browserItem(item);
}
