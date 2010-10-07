#ifndef _PLOT_INPUT_DATA_H_
#define _PLOT_INPUT_DATA_H_

#include <QVector>
#include <vector>
#include <qwt_array.h>
#include <qwt_data.h>

using namespace std;

class PlotInputData
{
	public:
		PlotInputData(const QVector <QVector <double> > &datay, 
				const QVector< double > &datax);
		PlotInputData(const QVector <QVector <double> > &datay, 
				const QVector< double > &datax,
				const QVector<QString> &label);
		virtual ~PlotInputData();
		const QRectF& getDataBounds() const;
		void setDataBounds(QRectF &rec);
		virtual vector< QwtArrayData>& getDatas();
		const QVector<QString>& getLabels() const;

	private:
		vector< QwtArrayData > mDatas;
		QRectF mPlotBound;
		QVector<QString> mLabels;
};

#endif
