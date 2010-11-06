#include "SpeciesDataManager.h"
#include <QDebug>

QVector<SpeciesData*> SpeciesDataManager::m_dataPool;
int SpeciesDataManager::m_num = 1;

SpeciesData* SpeciesDataManager::newSpeciesData()
{
	qDebug() << "---new species data";
	SpeciesData* p = new SpeciesData();
	if (p != NULL)
		m_dataPool.push_back(p);

	p -> setInputNo(m_num);
	m_num += 2 ;

	return p;
}

void SpeciesDataManager::removeAllData()
{
	for (int i=0; i < m_dataPool.size(); i++)
	{
		if (m_dataPool[i] != NULL)
			delete m_dataPool[i];
	}

	m_dataPool.clear();
}

void SpeciesDataManager::removeData(SpeciesData *data)
{
	if (data == NULL)
		return;

	int n = 0;

	while (n < m_dataPool.size())
	{
		if (data == m_dataPool[n])
			break;
		n++;
	}

	if (n < m_dataPool.size())
	{
		m_dataPool.remove(n);
		delete data;
	}

	return;
}

void SpeciesDataManager::dumpSpeciesData()
{
	QString itType;

	qDebug() << "-----------------------------dump: data";

	for (int i=0; i < m_dataPool.size(); i++)
	{
		if (m_dataPool[i]->type() == SPEC_COMPARTMENT)
			itType = "Cmpartment";
		if (m_dataPool[i]->type() == SPEC_BACKBONE)
			itType = "BackBone";
		if (m_dataPool[i]->type() == SPEC_BIOBRICK)
			itType = "Biobrick";
		if (m_dataPool[i]->type() == SPEC_COMPOUNDS)
			itType = "Compounds";

		qDebug() << " " << i << " " << m_dataPool[i]->type()
			<< " " << m_dataPool[i]->id()
			<< " " << m_dataPool[i]->fileComId()
			<< " " << m_dataPool[i]->parent()
			<< " " << m_dataPool[i]->size()
			<< " " << m_dataPool[i]->initConcentration()
			<< " " << m_dataPool[i]->constant()
			<< " " << m_dataPool[i]->partType();
		for (int j=0; j<m_dataPool[i]->ruleNum(); j++)
		{
			RuleData* ruleData = (m_dataPool[i]->getRuleList())[j];
			qDebug() << "	rule: " << j << " " << ruleData->rule();
			for (int k=0; k<ruleData->parameters().size(); k++)
			{
				ParameterData* data = (ruleData->parameters())[k];
				qDebug() << "		par: " << k << " " << data->id() << " " << data->units() << " "
					<< data->value() << " " << data->constant();
			}
		}
	}

	qDebug() << "-----------------------------dump: data end";
}

SpeciesData* SpeciesDataManager::getSpeciesData(int n)
{
	if ((n < 0) 
			|| (n > getDataCount()))
	{
		return NULL;
	}
	return m_dataPool[n];
}
