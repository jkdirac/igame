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

		ui.combx_constant->setVisible(false);
		ui.label_constant->setVisible(false);
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

		QString constant = ui.combx_constant->currentText();
		data->setConstant(constant);
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

	connect(ui.button_editRule, SIGNAL(pressed()), 
			                     this, SLOT(showRuleDataSet()));
}

void SpeciesDataSet::showRuleDataSet()
{
	m_dataSet = new RuleDataSet();
	m_dataSet->show();
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

		QString constant = ui.combx_constant->currentText();
		data->setConstant(constant);
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

		ui.combx_constant->setVisible(false);
		ui.lable_constant->setVisible(false);
	}
}

RuleDataSet::RuleDataSet(MItem* item) : QWidget(NULL), m_item(item)
{
	ui.setupUi(this);
	m_item = item;


}
