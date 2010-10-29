#include "SettingWidget.h"
#include "MItem.h"

ItemDataSetting::ItemDataSetting(MItem *item) : SettingWidget(item)
{
	ui.setupUi(this);
}

void ItemDataSetting::set()
{
}

void SettingWidget::focusOutEvent(QFocusEvent * event)
{
	close();
}

void SettingWidget::leaveEvent ( QEvent * event )
{
//    close();
}
