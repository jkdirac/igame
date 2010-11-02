#include "GenModelThread.h"
#include "driver.h"

GenModelThread::GenModelThread() : QThread()
{
	m_stop = false;
}

void GenModelThread::stop()
{
	m_stop = true;
}

void GenModelThread::run()
{
	Driver driver;
	try
	{
		bool errno = driver.beginSimulation ();
	}
	catch (CoreException &se)
	{
		cout << "GenModel Thread exceptions" << endl;
	}
}
