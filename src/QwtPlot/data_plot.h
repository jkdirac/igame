#ifndef _DATA_PLOT_H
#define _DATA_PLOT_H 1

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QVector>
#include "plotInputData.h"
#include "qwt_array.h"

const int PLOT_SIZE = 500;      // 0 to 200

class DataPlot : public QwtPlot
{
    Q_OBJECT

public:
//    DataPlot(QWidget*, double**data, int row, int column);
//    DataPlot(QWidget*, QwtArray< QwtArray<double> > &matrix, QwtArray< double >& x);
    DataPlot(QWidget*, PlotInputData &input);
    void plot(QwtArray< QwtArray<double> > &matrix, QwtArray< double >& x);
    ~DataPlot();

private:
    void alignScales();
    void setupUI();
    void setupCurve(QwtArray< QwtArray<double> > &matrix, QwtArray< double >& x);

    int color_R, color_G, color_B;
    QwtPlotCurve *mPcurve;
};

#endif
