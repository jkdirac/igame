#include "SettingWidget.h"
#include "MItem.h"

SettingWidget::SettingWidget(MItem* item):QWidget(NULL) 
{ 
	m_item = item; 
}

//void SettingWidget::focusOutEvent(QFocusEvent * event)
//{
//    close();
//    QWidget::fout
//}

//void SettingWidget::leaveEvent ( QEvent * event )
//{
//}

CompartDataSet::CompartDataSet(MItem *item) : SettingWidget(item)
{
	ui.setupUi(this);

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
//    close();
}

BiobrickDataSet::BiobrickDataSet(MItem *item) : SettingWidget(item)
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
//    close();
}

SpeciesDataSet::SpeciesDataSet(MItem *item) : SettingWidget(item)
{
	ui.setupUi(this);
	if (getItem() != NULL)
	{
		showSetting();
	}
}

void SpeciesDataSet::set()
{
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

RuleDataSet::RuleDataSet(MItem *item) : SettingWidget(item)
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
