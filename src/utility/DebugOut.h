#ifndef _DEBUG_OUTPUT_H_
#define _DEBUG_OUTPUT_H_

#include <string>
#include <iostream>

using namespace std;

class DebugOut
{
	public:

		static DebugOut* get_instance()
		{
			if (g_single == NULL)
			{
				g_single = new DebugOut();
			}
			return g_single;
		}

		template <typename T>
			DebugOut& operator << (const T& value)
			{
				if (b_print)
					cout << value;
				return *this;
			}

		DebugOut& operator << (basic_ostream<char, char_traits<char> >& 
				(*_Pfn) (basic_ostream<char, char_traits<char> >&));

		static void initDebugOutPut(bool printable);
		static void setPrintable(bool printable);
		static void finalizeDebugOutPut();

	protected:
		DebugOut();
		~DebugOut() {}

		static DebugOut *g_single;
		static bool b_print;
};

DebugOut& debugOut();

#endif
