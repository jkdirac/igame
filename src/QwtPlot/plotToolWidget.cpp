#include <QWidget>
#include <QVector>
#include <qapplication.h>
#include <qmainwindow.h>
#include <qwt_counter.h>
#include <qtoolbar.h>
#include <qlabel.h>
#include <qlayout.h>
#include "data_plot.h"
#include "plotToolWidget.h"

PlotToolWidget::~PlotToolWidget()
{
	if (mPlot != NULL)
	{
		delete mPlot;
		mPlot = NULL;
	}
}

PlotToolWidget::PlotToolWidget(QWidget*, PlotInputData& input)
{
	mPlot = NULL;
	QToolBar *toolBar = new QToolBar(this);
	toolBar->setFixedHeight(80);

#if QT_VERSION < 0x040000
	setDockEnabled(TornOff, true);
	setRightJustification(true);
#else
	toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
#endif
	QWidget *hBox = new QWidget(toolBar);

	QHBoxLayout *layout = new QHBoxLayout(hBox);
//        layout->addWidget(label);
	layout->addWidget(new QWidget(hBox), 10); // spacer);

	QVBoxLayout *mainlayout = new QVBoxLayout;
	mainlayout->addWidget(hBox);

#if QT_VERSION >= 0x040000
	toolBar->addWidget(hBox);
#endif
//        addToolBar(toolBar);


	mPlot = new DataPlot(this, input);
	mainlayout->addWidget(mPlot);

	setLayout(mainlayout);
}

void PlotToolWidget::plot(const double **data, int row, int column)
{
}

void PlotToolWidget::refresh()
{
}
