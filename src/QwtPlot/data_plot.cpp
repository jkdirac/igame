#include <stdlib.h>
#include <vector>
#include <qwt_painter.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <qwt_math.h>
#include "data_plot.h"
#include <iostream>
#include <QString>

using namespace std;

//
//  Initialize main window
//
void DataPlot::setupUI()
{
    // Disable polygon clipping
    QwtPainter::setDeviceClipping(false);

    // We don't need the cache here
    canvas()->setPaintAttribute(QwtPlotCanvas::PaintCached, false);
    canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, false);

#if QT_VERSION >= 0x040000
#ifdef Q_WS_X11
    /*
       Qt::WA_PaintOnScreen is only supported for X11, but leads
       to substantial bugs with Qt 4.2.x/Windows
     */
    canvas()->setAttribute(Qt::WA_PaintOnScreen, true);
#endif
#endif

    alignScales();

    // Assign a title
    setTitle("ode");
    insertLegend(new QwtLegend(), QwtPlot::BottomLegend);

}

void DataPlot::alignScales()
{
    // The code below shows how to align the scales to
    // the canvas frame, but is also a good example demonstrating
    // why the spreaded API needs polishing.

    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    canvas()->setLineWidth(2);

    for ( int i = 0; i < QwtPlot::axisCnt; i++ )
    {
        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)axisWidget(i);
        if ( scaleWidget )
            scaleWidget->setMargin(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)axisScaleDraw(i);
        if ( scaleDraw )
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
}

void DataPlot::setupCurve(QwtArray< QwtArray<double> > &matrix, QwtArray< double >& x)
{
}

DataPlot::DataPlot(QWidget*parent, PlotInputData &input) :
    QwtPlot(parent),
	mPcurve(NULL)
{
    	color_R = 0;
       	color_G = 0;
	color_B = 0;
	setupUI();
	vector<QwtArrayData> &datas = input.getDatas();
	const QVector<QString>& labels = input.getLabels();
	mPcurve = new QwtPlotCurve[datas.size()];
	for (int i=0; i<datas.size(); i++)
	{
		mPcurve[i].setData(datas[i]);
		mPcurve[i].attach(this);
		mPcurve[i].setTitle(labels[i]);
		mPcurve[i].setPen(QPen(QColor(color_R, color_G, color_B)));
		color_R = (color_R + 211) % 255;
		color_G = (color_G + 83) % 255;
		color_B = (color_B + 31) % 255;
	}

	//调整尺度
	const QRectF& plotBound = input.getDataBounds();
//#ifdef DEBUG_OUTPUT
	cout << plotBound.left() << " " << plotBound.right() << " " << plotBound.top() << " " <<
		plotBound.bottom() << endl;
//#endif
	setAxisTitle(QwtPlot::xBottom, "Time/seconds");
	setAxisScale(QwtPlot::xBottom, plotBound.left(), plotBound.right());
	setAxisTitle(QwtPlot::yLeft, "Values");
	setAxisScale(QwtPlot::yLeft, plotBound.bottom(), plotBound.top());
	show();
}

DataPlot::~DataPlot()
{
	if (mPcurve != NULL)
	{
		delete []mPcurve;
		mPcurve = NULL;
	}
}

void DataPlot::plot(QwtArray< QwtArray<double> > &matrix, QwtArray< double >& x)
{
	setupCurve(matrix, x);
	show();
}
