#include "driver.h"
#include "CopsiInterface.h"

int main ()
{
	time_t start, end;
	time (&start);

	Driver driver;
	bool errno = driver.beginSimulation ();

	time (&end);
	double dif = difftime (end, start);
	cout << "\nIt tooks " <<  dif << " seconds.\n";

	if (!errno) copsi_entry("network.xml");
	return 0;
}
