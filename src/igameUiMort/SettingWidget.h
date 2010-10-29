#ifndef _SETTING_WIDGET_H_
#define _SETTING_WIDGET_H_

#include <QWidget>

#include "ui_ItemDataSetting.h"

class MItem;
class SettingWidget : public QWidget
{
	public:
		SettingWidget(MItem* item):QWidget(NULL) { m_item = item; };
		virtual void set() = 0;

		void focusOutEvent(QFocusEvent * event);
		void leaveEvent ( QEvent * event ); 

	private:
		MItem* m_item;
};

class ItemDataSetting : public SettingWidget
{
	Q_OBJECT
	public:
		ItemDataSetting(MItem *);
		void set();

	private:
		Ui::ItemDataSetting ui;
};	

#endif
