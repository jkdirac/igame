/*
  Last changed Time-stamp: <2005-12-12 15:25:41 raim>
  $Id: integrate.c,v 1.12 2005/12/12 14:40:53 raimc Exp $
*/
/* 
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. The software and
 * documentation provided hereunder is on an "as is" basis, and the
 * authors have no obligations to provide maintenance, support,
 * updates, enhancements or modifications.  In no event shall the
 * authors be liable to any party for direct, indirect, special,
 * incidental or consequential damages, including lost profits, arising
 * out of the use of this software and its documentation, even if the
 * authors have been advised of the possibility of such damage.  See
 * the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * The original code contained here was initially developed by:
 *
 *     Rainer Machne
 *
 * Contributor(s):
 */
#include "integrate.h"
#include <stdio.h>
#include <stdlib.h>

#include <sbmlsolver/odeSolver.h>
#include <string>
#include <string.h>
#include "libsbml-401-wrapper.h"

using namespace std;

const QVector <QString>& intgrtOutData::get_labels() const
{
	return labels;
}

void intgrtOutData::push_label(QString &str)
{
	labels.push_back(str);
}

intgrtOutData::intgrtOutData()
{
	test_x.clear();
	test_y.clear();
	labels.clear();
}

const QVector < double > & intgrtOutData::get_time_point() const
{
	return test_x;
}
const QVector < QVector<double> >& intgrtOutData::get_data_point() const
{
	return test_y;
}

void intgrtOutData::push_time_point(double x)
{
	if (test_x.size() == 0)
	{
		mMaxDataX = x;
		mMinDataX = x;
	}

	if (x > mMaxDataX)
		mMaxDataX = x;
	if (x < mMinDataX)
		mMinDataX = x;

	test_x.push_back(x);
}

void intgrtOutData::push_data_point(int n, double y)
{
	if (test_y.size() == 0)
	{
		mMaxDataY = y;
		mMinDataY = y;
	}

	if (test_y.size() < n+1)
	{
		test_y.resize(n+1);
	}
	//如果小于n+1

	if (y > mMaxDataY)
		mMaxDataY = y;
	if (y < mMinDataY)
		mMinDataY = y;

	test_y[n].push_back(y);
}

void intgrtOutData::dump()
{
	for (int i=0; i<test_x.size(); i++)
	{
		cout << "time point " << test_x[i] << ":";
		for (int j=0; j<test_y.size(); j++)
		{
			cout << "(" << labels[j].toAscii().data() << ")" << test_y[j][i]; 
		}
		cout << endl;
	}
}

QRectF& intgrtOutData::getDataBounds()
{
	//截取边界坐标为整数
	double nLeft,nRight,nTop,nBottom;

	nLeft = (mMinDataX);
	nRight = (mMaxDataX);

	//使得y轴上下对称
	nTop = (mMaxDataY);
	nBottom = (mMinDataY);

	mPlotRegion.setLeft(nLeft);
	mPlotRegion.setRight(nRight);
	mPlotRegion.setTop(nTop);
	mPlotRegion.setBottom(nBottom);

	cout << "bounds: ["<< mPlotRegion.left() << ", " << mPlotRegion.right() << ", " << mPlotRegion.top() << ", " <<
		mPlotRegion.bottom() << "]" << endl;

	return mPlotRegion;
}

/*int*/
/*main (int argc, char *argv[]){*/
int integrate(char *model, double time, double printstep, intgrtOutData &res)
{
  int i, j;
  /* libSBML types */
  SBMLDocument_t *d;
  SBMLReader_t *sr;
  Model_t *m;
  /* SOSlib types */
  SBMLResults_t *results;
  timeCourse_t *tc;
  cvodeSettings_t *set;

  /* parsing command-line arguments */
/*  model = argv[1];*/
/*  time = atof(argv[2]);*/
/*  printstep = atoi(argv[3]); */

  /* parsing the SBML model with libSBML */
  sr = SBMLReader_create();
  d = SBMLReader_readSBML(sr, model);
  SBMLReader_free(sr);

  if (SBMLDocument_getNumErrors(d) != 0)
  {
	  fprintf(stderr, "get Document cotents error\n");
	  SBMLDocument_printErrors(d, stderr);
	  return EXIT_FAILURE;
  }
  //debug by jkdirac
  fprintf(stderr, "get Document cotents\n %s\n", SBMLDocument_tosbml(d));

  /* Setting SBML ODE Solver integration parameters  */
  set = CvodeSettings_create();
  CvodeSettings_setTime(set, time, printstep);
  CvodeSettings_setErrors(set, 1e-9, 1e-4, 1000);

  /* calling the SBML ODE Solver which returns SBMLResults */  
  results = SBML_odeSolver(d, set);
  
  if ( SolverError_getNum(FATAL_ERROR_TYPE) ) {
    printf("Integration not sucessful!\n");
    SolverError_dumpAndClearErrors();
    return(EXIT_FAILURE);
  }

  if (results == NULL)
	  return(EXIT_FAILURE);

  /* now we have the results and can free the inputs */
  CvodeSettings_free(set);
  SBMLDocument_free(d);

  /* print results */
//  printf("### RESULTS \n");  
//  SBMLResults_dump(results);

  //get time points
  for (int i=0; i<results->time->timepoints; i++)
  {
	  res.push_time_point(results->time->values[i]);
  }

  //get species data points
  for (int i=0; i<results->species->num_val; i++)
  {
	  QString tmp(results->species->tc[i]->name);
	  res.push_label(tmp);
	  for (int j=0; j<results->species->tc[i]->timepoints; j++)
	  {
		  res.push_data_point(i, results->species->tc[i]->values[j]);
	  }
  }

  //get comparments points
  for (int i=0; i<results->compartments->num_val; i++)
  {
	  QString tmp(results->compartments->tc[i]->name);
	  res.push_label(tmp);
	  for (int j=0; j<results->compartments->tc[i]->timepoints; j++)
	  {
		  res.push_data_point(i, results->compartments->tc[i]->values[j]);
	  }
  }
  SolverError_dumpAndClearErrors();
  /* now we can also free the result structure */
  SBMLResults_free(results);

  return (EXIT_SUCCESS);  
}

/* End of file */
