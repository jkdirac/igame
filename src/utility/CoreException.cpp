#include "CoreException.h"
#include <string>

CoreException::CoreException(const string &msg) throw()
{
	n_msg = msg;
}

CoreException::CoreException(const CoreException& other) throw()
{
	n_msg = other.get_msg();
}

CoreException::~CoreException() throw()
{
}

CoreException& CoreException::operator = (const CoreException& other) throw()
{
	n_msg = other.get_msg();
	return *this;
}

const char* CoreException::what() const throw()
{
	return n_msg.c_str();
}

const string& CoreException::get_msg() const throw()
{
	return n_msg;
}
