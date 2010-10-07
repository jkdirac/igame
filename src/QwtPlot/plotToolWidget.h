#ifndef _PLOT_TOOL_WIDGET_H_
#define _PLOT_TOOL_WIDGET_H_

#include <qmainwindow.h>
#include "plotInputData.h"
#include <QDialog>
#include <QVector>
#include "data_plot.h"

class PlotToolWidget: public QDialog
{
	public:
		PlotToolWidget(QWidget*, PlotInputData& input);
		~PlotToolWidget();
		void plot(const double **data, int row, int column);
		void refresh();

	private:
		DataPlot *mPlot;
};

#endif
