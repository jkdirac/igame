#include "SettingWidget.h"
#include <QDoubleValidator>
#include <QCursor>
#include <QListWidgetItem> 

#include "MItem.h"
#include "MScene.h"

SettingWidget::SettingWidget(MItem* item, SettingWidget* impl):QWidget(NULL) 
{ 
	m_item = item; 
	m_impl = impl;
}

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
	,m_dataSet(NULL)
{
	ui.setupUi(this);
	QDoubleValidator* validator = new QDoubleValidator(NULL);
	validator->setNotation(QDoubleValidator::ScientificNotation);
	ui.tx_SpecInitCon->setValidator(validator);

	if (getItem() != NULL)
	{
		showSetting();
	}

	m_ruleSett = NULL;
	connect(ui.button_editRule, SIGNAL(pressed()), 
			                     this, SLOT(showRuleDataSet()));
}

void SpeciesDataSet::showRuleDataSet()
{
	MItem* item = getItem();
	if (item == NULL)
		return;

	MScene* m_scene = item->getScene();
	if (m_dataSet == NULL)
		m_dataSet = new RuleDataSet(getItem(), this);

	if (m_ruleSett == NULL)
		m_ruleSett = (MWidget*)m_scene->addWidget(m_dataSet); 

	qDebug() << "x: " << ui.m_speciesSet->x() << "y: " << ui.m_speciesSet->y()
		<< "width: " << ui.m_speciesSet->width();

	m_ruleSett->setX(x() + width());
	m_ruleSett->setY(y());
	m_dataSet->show();

//    connect(m_dataSet, SIGNAL(pressed()), 
//                                 this, SLOT(showRuleDataSet()));
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

		//show constant setting
		ui.combx_constant->setVisible(false);
		ui.lable_constant->setVisible(false);
	}
}

RuleDataSet::RuleDataSet(MItem* item, SettingWidget *parent) 
: QWidget(NULL), m_item(item) ,m_parentWidget(NULL)
{
	ui.setupUi(this);
	m_item = item;
	m_parentWidget = parent;

	if (m_item == NULL)
		return;

	SpeciesData* data = m_item->getSpeciesData();
	if (data == NULL)
		return;

	ui.m_rulelist->addItem("New");
	QList<RuleData*>& rule = data->getRuleList();
	for (int i=0; i<rule.size(); i++)
	{
		int ntail = ui.m_rulelist->count() - 1;
		QListWidgetItem* newItem = new QListWidgetItem(rule[i]->rule());
		ui.m_rulelist->insertItem(ntail, newItem);
	}

	if (ui.m_rulelist->count() == 1)
	{
		ui.m_paraEditor->setVisible(false);
		ui.m_paralist->setVisible(false);
		ui.m_labelParameter->setVisible(false);
	}

	connect(ui.m_rulelist, SIGNAL(itemDoubleClicked(QListWidgetItem *)), 
			                     this, SLOT(createRuleInfo(QListWidgetItem *)));
	connect(ui.m_rulelist, SIGNAL(itemClicked(QListWidgetItem *)), 
			                     this, SLOT(showRuleInfo(QListWidgetItem *)));
	connect(ui.m_paralist, SIGNAL(itemDoubleClicked(QListWidgetItem *)), 
			                     this, SLOT(showParaInfo(QListWidgetItem *)));
	connect(ui.button_confirm, SIGNAL(pressed()), 
			                     this, SLOT(setPara()));
}

void RuleDataSet::leaveEvent ( QEvent * event )
{
	close();
}

void RuleDataSet::createRuleInfo(QListWidgetItem *item)
{
	if (item == NULL)
		return;

	if (m_item == NULL)
		return;

	SpeciesData* data = m_item->getSpeciesData();
	if (data == NULL)
		return;

	qDebug() << "current idx " << ui.m_rulelist->currentRow();
	if (item->text() == "New")
	{
		// new a item
		QListWidgetItem* newItem = new QListWidgetItem();
//        QListWidgetItem* newItem = new EditListWidgetItem();
		newItem->setFlags(Qt::ItemIsEditable |
				item->flags());
		int row = ui.m_rulelist->count()-1;
		ui.m_rulelist->insertItem(row, newItem);
		ui.m_rulelist->setCurrentRow(row);
		ui.m_rulelist->editItem(newItem);

		RuleData* ruleData = new RuleData();
		data->insertFun(ruleData);
		ruleData->setItem(newItem);
	}
}

void RuleDataSet::showRuleInfo(QListWidgetItem *item)
{
	if (item == NULL)
		return;

	if (m_item == NULL)
		return;

	qDebug() << "rule clicked";
	if (item->text() == "New")
	{
		qDebug() << "rule clicked new";
		ui.m_paraEditor->setVisible(false);
		ui.m_paralist->setVisible(false);
	ui.m_labelParameter->setVisible(false);
		return;
	}

	SpeciesData* data = m_item->getSpeciesData();
	if (data == NULL)
		return;
	ui.m_paraEditor->setVisible(false);
	ui.m_paralist->setVisible(true);
	ui.m_labelParameter->setVisible(true);

	qDebug() << "para list item count " << ui.m_paralist->count();
	ui.m_paralist->clear();
	ui.m_paralist->addItem("New");
	int row = ui.m_rulelist->currentRow();
	RuleData* ruleData = (data->getRuleList())[row];

	if (ruleData == NULL)
		return;

	QList<ParameterData*>& parameter = ruleData->parameters();
	for (int i=0; i<parameter.size(); i++)
	{
		int row = ui.m_paralist->count() - 1;
		QListWidgetItem* newItem = new QListWidgetItem(parameter[i]->id());
		ui.m_paralist->insertItem(row, newItem);
	}
}

void RuleDataSet::showParaInfo(QListWidgetItem *item)
{
	if (item == NULL)
		return;

	if (m_item == NULL)
		return;

	SpeciesData* data = m_item->getSpeciesData();
	if (data == NULL)
		return;

	int curRow = ui.m_paralist->currentRow();
	if (item->text() == "New")
	{
		ui.lineEdit_id->setText("");
		ui.lineEdit_units->setText("");
		ui.lineEdit_value->setText("");
		ui.combx_constant->setEditText("");
	}
	else
	{
		int curRuleRow = ui.m_rulelist->currentRow();
		RuleData* curRuleData = (data->getRuleList())[curRuleRow];
		if (curRuleData == NULL)
			return;
		ParameterData* curData = NULL;	
		QList<ParameterData*>& parameter = curRuleData->parameters();
		curData = parameter[curRow];
		ui.m_paraEditor->setVisible(true);
		ui.lineEdit_id->setText(curData->id());
		ui.lineEdit_units->setText(curData->units());
		ui.lineEdit_value->setText(curData->value());
		ui.combx_constant->setEditText(curData->constant());
	}

	ui.m_paraEditor->setVisible(true);
#if 0
	if (item->text() == "New")
	{
		// new a item
		QListWidgetItem* newItem = new QListWidgetItem();
//        QListWidgetItem* newItem = new EditListWidgetItem();
		newItem->setFlags(Qt::ItemIsEditable |
				item->flags());
		int row = ui.m_paralist->count()-1;
		qDebug() << "para list row: " << row;
		ui.m_paralist->insertItem(row, newItem);
		ui.m_paralist->setCurrentRow(row);
		ui.m_paralist->editItem(newItem);

		int funrow = ui.m_rulelist->currentRow();
		RuleData* ruleData = (data->getRuleList())[funrow];
		ParameterData* newPara = new ParameterData();
		ruleData->addParamer(newPara);
//        ParameterData* listData = new ParameterData();
//        listData->setId(newItem->text());
		data->insertFun(ruleData);
	}
	else
	{
	}
#endif
}

void RuleDataSet::setPara()
{
	int row = ui.m_paralist->count();
	int curRow = ui.m_paralist->currentRow();
	int curRuleRow = ui.m_rulelist->currentRow();

	SpeciesData* data = m_item->getSpeciesData();

	if (data == NULL)
		return;
	RuleData* curRuleData = (data->getRuleList())[curRuleRow];

	if (curRuleData == NULL)
		return;

	ParameterData* curData = NULL;	

	QList<ParameterData*>& parameter = curRuleData->parameters();
	qDebug() << "set para: " << curRow << " " << parameter.size();
	if (curRow < parameter.size())
	{
		curData = parameter[curRow];
	}
	else
	{
		qDebug() << "new para";
		curData = new ParameterData();
		curRuleData->addParamer(curData);
	}

	curData->setId(ui.lineEdit_id->text());
	curData->setUnits(ui.lineEdit_units->text());
	curData->setValue(ui.lineEdit_value->text());
	curData->setConstant(ui.combx_constant->currentText());

	showRuleInfo(ui.m_rulelist->item(curRuleRow));
}
