#ifndef _TRCACU_EXCEPTION_H_
#define _TRCACU_EXCEPTION_H_

#include <string>
//#include <typeinfo>

using namespace std;

class CoreException : public exception
{
	public:
		CoreException(const string &msg) throw();
		CoreException(const CoreException&) throw();

		CoreException& operator= (const CoreException& other) throw();

		~CoreException() throw();
		const char* what() const throw();

	private:
		string n_msg;
		const string& get_msg() const throw();
};

#endif
