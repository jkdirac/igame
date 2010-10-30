#ifndef _SETTING_WIDGET_H_
#define _SETTING_WIDGET_H_

#include <QWidget>
#include "MWidget.h"

#include <QDebug>
#include "ui_ItemDataSetting.h"

class MItem;
class SettingWidget : public QWidget
{
	public:
		SettingWidget(MItem* item); 
		virtual void set() = 0;
		virtual void showSetting (const QString &id) 
		{
			qDebug() << "showSetting id";
		} ;

		void focusOutEvent(QFocusEvent * event);
		void leaveEvent ( QEvent * event ); 
		MItem* getItem() { return m_item; }

	private:
		MItem* m_item;
};

class ItemDataSetting : public SettingWidget
{
	Q_OBJECT
	public:
		ItemDataSetting(MItem *);
		void set();
		void showSetting(const QString& id);

	private:
		Ui::ItemDataSetting ui;
};	

#endif
