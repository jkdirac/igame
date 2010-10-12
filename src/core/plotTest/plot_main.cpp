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

int max_step;
int final_time;

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

bool analys(char* fileName, intgrtOutData& ode_res)
{
		if (fileName == NULL)
				return false;
	//获取结果
	bool bRes = integrate(fileName, final_time, max_step, ode_res);

	if (bRes == EXIT_FAILURE)
	{
		cout << "integrate error" << endl;
		return false;
	}
	else
			return true;
}

void printOdes_fromFile(char* filename)
{
		if (filename == NULL)
				return;

    int i;
    char *formula;
    variableIndex_t *vi = NULL;

    odeModel_t *model =
      ODEModel_createFromFile(filename);

	if (model == NULL)
	{
			printf("create odemodel fails:\n");
			return;
	}

    /* Get some information from constructed odeModel */
    printf("\n\n");
    printf("ODE Model Statistics:\n");
    printf("Number of ODEs:               %d\n",
	   ODEModel_getNeq(model));
    printf("Number of Assignments:        %d\n",
	   ODEModel_getNumAssignments(model));
    printf("Number of Constants:          %d\n",
	   ODEModel_getNumConstants(model));
    printf("                            ____\n");
    printf("Total number of values:       %d\n",
	   ODEModel_getNumValues(model));
    
    printf("\n");
    printf("ODEs:\n");
    for ( i=0; i<ODEModel_getNeq(model); i++ ){
      vi = ODEModel_getOdeVariableIndex(model, i);
      formula = SBML_formulaToString(ODEModel_getOde(model, vi));
      printf("d[%s]/dt = %s \n", ODEModel_getVariableName(model, vi), formula);
      free(formula);
      VariableIndex_free(vi);
    }
//    printf("Assigned Variables:\n");
//    for ( i=0; i<ODEModel_getNumAssignments(model); i++ ){
//      vi = ODEModel_getAssignedVariableIndex(model, i);
//      formula = SBML_formulaToString(ODEModel_getOde(model, vi));
//      printf("%s = %s \n", ODEModel_getVariableName(model, vi), formula);
//      free(formula);
//      VariableIndex_free(vi);
//    }
    printf("Constants:\n");
    for ( i=0; i<ODEModel_getNumConstants(model); i++ ){
      vi = ODEModel_getConstantIndex(model, i);
      printf("%s\n", ODEModel_getVariableName(model, vi));
      VariableIndex_free(vi);
    }
    printf("\n\n");

    
    ODEModel_free(model);
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

	if (argc <= 1)
	{
			fprintf(stderr, "please input src file\n");
			return 0;
	}

	max_step = 1000;
	final_time = 10000;

	if (argc > 3)
	{
		final_time = atoi(argv[2]);
		max_step = atoi(argv[3]);
	}

	intgrtOutData ode_res;

	bool res = analys(argv[1], ode_res);
	cout << "analys succ: " << res << endl;
	printOdes_fromFile(argv[1]);

	PlotInputData plotInputData(ode_res.test_y, ode_res.test_x, ode_res.get_labels());

	QRectF& plotBound = ode_res.getDataBounds();
	plotInputData.setDataBounds(plotBound);

	PlotToolWidget plotWindow(NULL, plotInputData);
	return plotWindow.exec();
}
