#include "GenModelThread.h"
#include "driver.h"

GenModelThread::GenModelThread() : QThread()
{
	m_stop = false;
	m_succ = false;
}

void GenModelThread::stop()
{
	m_stop = true;
}

void GenModelThread::run()
{
	bool errno;
	Driver driver;
	try
	{
		errno = driver.beginSimulation ();
		if (errno == 0)
			m_succ = true;
		else
			m_succ = false;
	}
	catch (CoreException &se)
	{
		cout << "GenModel Thread exceptions" << endl;
		m_succ = false;
	}
}

bool GenModelThread::succ() const
{
	return m_succ;
}
