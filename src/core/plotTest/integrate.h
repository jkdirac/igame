#ifndef _INTEGRATE_H_
#define _INTEGRATE_H_

#include <iostream>
#include <sbmlsolver/odeSolver.h>
#include <QVector>
#include <QRectF>
#include <QString>

using namespace std;

class intgrtOutData
{
	public:
		QVector < double > test_x;
		QVector < QVector<double> > test_y;
	private:
		QVector <QString> labels;
		QRectF mPlotRegion;
		double mMinDataX;
		double mMaxDataX;
		double mMinDataY;
	double mMaxDataY;

	public:
		intgrtOutData();
		const QVector < double > & get_time_point() const;
		const QVector < QVector<double> >& get_data_point() const;
		const QVector <QString>& get_labels() const;
		void push_label(QString &str);
		void push_time_point(double x);
		void push_data_point(int n, double x);
		void dump();
		QRectF& getDataBounds();
};

#ifdef __cplusplus
extern "C"
{
#endif 

int integrate(char *model, double time, 
		double printstep, 
		intgrtOutData &res);

#ifdef __cplusplus
}
#endif

#endif
