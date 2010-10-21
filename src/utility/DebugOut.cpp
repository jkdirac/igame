#include "DebugOut.h"

DebugOut* DebugOut::g_single = NULL;
bool DebugOut::b_print = true;

DebugOut::DebugOut()
{
//    cout = cout;
}

void DebugOut::setPrintable(bool printable)
{
	b_print = printable;
}

void DebugOut::initDebugOutPut(bool printable)
{
	b_print = printable;
}

void DebugOut::finalizeDebugOutPut()
{
	if (g_single != NULL)
	{
		delete g_single;
		g_single = NULL;
	}
}

DebugOut& debugOut()
{
	return *(DebugOut::get_instance());
}

DebugOut& DebugOut::operator << (basic_ostream<char, char_traits<char> >&(*_Pfn)(basic_ostream<char, 
			char_traits<char> >&))
{
	if (b_print)
		cout << _Pfn;
	return *this;
}
