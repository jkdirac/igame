#ifndef _TRCACU_EXCEPTION_H_
#define _TRCACU_EXCEPTION_H_

#include <string>
//#include <typeinfo>

using namespace std;

class StrCacuException : public exception
{
	public:
		StrCacuException(const string &msg) throw();
		StrCacuException(const StrCacuException&) throw();

		StrCacuException& operator= (const StrCacuException& other) throw();

		~StrCacuException() throw();
		const char* what() const throw();

	private:
		string n_msg;
		const string& get_msg() const throw();
};

#endif
