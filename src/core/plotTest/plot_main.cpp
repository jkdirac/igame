#include <qapplication.h>
#include <qmainwindow.h>
#include <qwt_counter.h>
#include <qtoolbar.h>
#include <qlabel.h>
#include <qlayout.h>
#include <QString>
#include <iostream>
#include "data_plot.h"
#include "integrate.h"
#include "plotToolWidget.h"

class MainWindow: public QMainWindow
{
public:
    MainWindow()
    {
	    /*
        QToolBar *toolBar = new QToolBar(this);
        toolBar->setFixedHeight(80);

#if QT_VERSION < 0x040000
        setDockEnabled(TornOff, true);
        setRightJustification(true);
#else
        toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
#endif
        QWidget *hBox = new QWidget(toolBar);
        QLabel *label = new QLabel("Timer Interval", hBox);
        QwtCounter *counter = new QwtCounter(hBox);
        counter->setRange(-1.0, 100.0, 1.0);

        QHBoxLayout *layout = new QHBoxLayout(hBox);
        layout->addWidget(label);
        layout->addWidget(counter);
        layout->addWidget(new QWidget(hBox), 10); // spacer);

#if QT_VERSION >= 0x040000
        toolBar->addWidget(hBox);
#endif
        addToolBar(toolBar);


        DataPlot *plot = new DataPlot(this);
        setCentralWidget(plot);

        connect(counter, SIGNAL(valueChanged(double)),
            plot, SLOT(setTimerInterval(double)) );

        counter->setValue(20.0);
	*/
    }
};

bool analys(QString fileName, intgrtOutData ode_res)
{
	if (fileName.isNull())
		return false;

	//获取结果
	bool bRes = integrate(fileName.toAscii().data(), 1000, 10000, ode_res);

	if (bRes == EXIT_FAILURE)
	{
		cout << "integrate error" << endl;
		return false;
	}
	else
			return true;
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

	QString fileName = "network.xml";
	intgrtOutData ode_res;

	bool res = analys(fileName, ode_res);
	cout << "analys succ: " << res << endl;

	PlotInputData plotInputData(ode_res.test_y, ode_res.test_x, ode_res.get_labels());

	QRectF& plotBound = ode_res.getDataBounds();
	plotInputData.setDataBounds(plotBound);

	PlotToolWidget plotWindow(NULL, plotInputData);
	return plotWindow.exec();
}
