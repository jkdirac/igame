#ifndef _SPEIES_DATA_MANAGER_H_
#define _SPEIES_DATA_MANAGER_H_

#include <QVector>
#include "SpeciesData.h"

class SpeciesDataManager
{
	public:
		static SpeciesData* newSpeciesData(); 
		static void removeData(SpeciesData *data); 
		static void removeAllData(); 
		static void dumpSpeciesData();
		static inline int getDataCount() { return m_dataPool.size(); };
		static SpeciesData* getSpeciesData(int n);

	private:
		static QVector<SpeciesData*> m_dataPool;
		static int m_num;
		SpeciesDataManager() {};
};

#endif
