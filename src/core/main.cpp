#include "driver.h"

int main ()
{
  Driver driver;

  try
  {
	bool SIMok = driver.beginSimulation ();
  }
  catch (...)
  {
	cerr << "HELLO!" << endl;
  }

  return 0;
}
