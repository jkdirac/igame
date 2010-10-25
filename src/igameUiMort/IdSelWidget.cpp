#include "IdSelWidget.h"
#include <QDebug>

using namespace std;

IdSelWidget::IdSelWidget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);

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
		qDebug() <<"id " << i << " " << res[i].c_str() << endl;
		QString qstr(res[i].c_str());
		comList << qstr;
	}

	setCompartments(comList);
}


void IdSelWidget::setCompartments(QStringList &list)
{
	m_compList = list;
	ui.com_combx->addItems(m_compList);
}
