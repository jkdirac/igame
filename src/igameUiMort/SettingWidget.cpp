#include "SettingWidget.h"
#include "MItem.h"

SettingWidget::SettingWidget(MItem* item):QWidget(NULL) 
{ 
	m_item = item; 
	
}

void SettingWidget::focusOutEvent(QFocusEvent * event)
{
	close();
}

void SettingWidget::leaveEvent ( QEvent * event )
{
}

ItemDataSetting::ItemDataSetting(MItem *item) : SettingWidget(item)
{
	ui.setupUi(this);

	if (getItem() != NULL)
	{
		this->showSetting(getItem()->id());
	}
}

void ItemDataSetting::showSetting(const QString& id)
{
	qDebug() << "showSetting id";
	ui.m_compartmentId->setText(id);
}

void ItemDataSetting::set()
{
//    close();
}
