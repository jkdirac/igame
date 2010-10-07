#include "plotInputData.h"
#include <assert.h>
#include <QString>

PlotInputData::PlotInputData(const QVector< QVector <double> > &datay, 
		const QVector< double > &datax,
		const QVector<QString> &label)
{
	mLabels = label;
	for (int i=0; i<datay.size(); i++)
	{
		//
		assert( datax.size() == datay[i].size() );
		QwtArrayData a(datax, datay[i]);
		mDatas.push_back(a);
	}

	mPlotBound.setRect(0,1,10,2);
}

vector<QwtArrayData>& PlotInputData::getDatas()
{
	return mDatas;
}

PlotInputData::PlotInputData(const QVector < QVector <double> > &datay, const QVector< double > &datax)
{
	for (int i=0; i<datay.size(); i++)
	{
		//
		assert( datax.size() == datay[i].size() );
		QwtArrayData a(datax, datay[i]);
		mDatas.push_back(a);
	}

	mPlotBound.setRect(0,1,10,2);
}

void PlotInputData::setDataBounds(QRectF &rec)
{
	mPlotBound = rec;
}

const QRectF& PlotInputData::getDataBounds() const
{
	return mPlotBound;
}

const QVector<QString>& PlotInputData::getLabels() const
{
	return mLabels;
}

PlotInputData::~PlotInputData()
{
}
