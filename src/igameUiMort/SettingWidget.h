#ifndef _SETTING_WIDGET_H_
#define _SETTING_WIDGET_H_

#include <QWidget>
#include "MWidget.h"

#include <QDebug>
#include "ui_CompartDataSet.h"
#include "ui_RuleDataSet.h"
#include "ui_SpeciesDataSet.h"
#include "ui_BiobrickDataSet.h"

class MItem;
class SettingWidget : public QWidget
{
	public:
		SettingWidget(MItem* item, SettingWidget* impl); 
		~SettingWidget() {};

		virtual void set() = 0;
		void showSetting () 
		{
			qDebug() << "showSetting id";
		} ;

//        void focusOutEvent(QFocusEvent * event);
		void leaveEvent ( QEvent * event ); 
		MItem* getItem() { return m_item; }

	private:
		SettingWidget* m_impl;
		MItem* m_item;
};

class CompartDataSet : public SettingWidget
{
	Q_OBJECT
	public:
		CompartDataSet(MItem *item);
		void set();
		void showSetting();

	private:
		Ui::CompartDataSet ui;
};	

class SpeciesDataSet : public SettingWidget
{
	Q_OBJECT
	public:
		SpeciesDataSet(MItem *item);
		void set();
		void showSetting();

	private:
		Ui::SpeciesDataSet ui;
};	

class BiobrickDataSet : public SettingWidget
{
	Q_OBJECT
	public:
		BiobrickDataSet(MItem *item);
		void set();
		void showSetting();

	private:
		Ui::BiobrickDataSet ui;
};	

class RuleDataSet : public SettingWidget
{
	Q_OBJECT
	public:
		RuleDataSet(MItem *item);
		void set();
		void showSetting();

	private:
		Ui::RuleDataSet ui;
};	
#endif
