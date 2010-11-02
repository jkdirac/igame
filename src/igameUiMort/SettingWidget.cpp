#include "SettingWidget.h"
#include "MItem.h"
#include <QDoubleValidator>
#include <QCursor>

SettingWidget::SettingWidget(MItem* item, SettingWidget* impl):QWidget(NULL) 
{ 
	m_item = item; 
	m_impl = impl;
}

//void SettingWidget::focusOutEvent(QFocusEvent * event)
//{
//    close();
//    QWidget::fout
//}

void SettingWidget::leaveEvent ( QEvent * event )
{
	qDebug() << "leave widget";

	QPoint point = QCursor::pos();
	int mos_x = point.x();
	int mos_y = point.y();
	int rec_x = x();
	int rec_y = y();
	int rec_width = width();
	int rec_height = height();

	if ( ((mos_x - rec_x) * (mos_x - rec_x - rec_width) <= 0 )
			&& ((mos_y - rec_y) * (mos_y - rec_y - rec_height) <= 0) )
	{
		qDebug() << "widget under mouse!";
		return;
	}

	m_impl->set();
	close();
}

CompartDataSet::CompartDataSet(MItem *item) : SettingWidget(item, this)
{
	ui.setupUi(this);

	QDoubleValidator* validator = new QDoubleValidator(NULL);
	validator->setNotation(QDoubleValidator::ScientificNotation);
	ui.lineEdit_size->setValidator(validator);

	showSetting();
}

void CompartDataSet::showSetting()
{
	qDebug() << "showSetting id";
	MItem* item = getItem();
	if (item != NULL)
	{
		SpeciesData* data = item->getSpeciesData();

		if (data == NULL)
			return;

		ui.m_compartmentId->setText(data->id());
		ui.lineEdit_size->setText(data->size());
	}
}

void CompartDataSet::set()
{
	MItem* item = getItem();
	if (item != NULL)
	{
		SpeciesData* data = item->getSpeciesData();
		
		if (data == NULL)
			return;
		QString size = ui.lineEdit_size->text();
		data->setSize(size);
	}
}

BiobrickDataSet::BiobrickDataSet(MItem *item) : SettingWidget(item, this)
{
	ui.setupUi(this);
	if (getItem() != NULL)
	{
		showSetting();
	}
}

void BiobrickDataSet::showSetting()
{
	qDebug() << "showSetting id";
	MItem* item = getItem();
	if (item != NULL)
	{
		SpeciesData* data = item->getSpeciesData();

		if (data == NULL)
			return;

		ui.tx_bbId->setText(data->id());
	}
}

void BiobrickDataSet::set()
{
	MItem* item = getItem();
	if (item != NULL)
	{
		SpeciesData* data = item->getSpeciesData();
		
		if (data == NULL)
			return;
		QString type = ui.comb_partType->currentText();
		data->setPartType(type);
	}
}

SpeciesDataSet::SpeciesDataSet(MItem *item) : SettingWidget(item, this)
{
	ui.setupUi(this);
	QDoubleValidator* validator = new QDoubleValidator(NULL);
	validator->setNotation(QDoubleValidator::ScientificNotation);
	ui.tx_SpecInitCon->setValidator(validator);

	if (getItem() != NULL)
	{
		showSetting();
	}
}

void SpeciesDataSet::set()
{
	MItem* item = getItem();
	if (item != NULL)
	{
		SpeciesData* data = item->getSpeciesData();
		
		if (data == NULL)
			return;
		QString initCon = ui.tx_SpecInitCon->text();
		data->setInitConcentration(initCon);
	}
}

void SpeciesDataSet::showSetting()
{
	qDebug() << "showSetting id";
	MItem* item = getItem();
	if (item != NULL)
	{
		SpeciesData* data = item->getSpeciesData();

		if (data == NULL)
			return;

		ui.tx_SpeId->setText(data->id());
		ui.tx_SpecInitCon->setText(data->initConcentration());
	}
}

RuleDataSet::RuleDataSet(MItem *item) : SettingWidget(item, this)
{
	ui.setupUi(this);
	if (getItem() != NULL)
	{
		showSetting();
	}
}

void RuleDataSet::set()
{
}

void RuleDataSet::showSetting()
{
}
