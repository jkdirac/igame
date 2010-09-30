#include "StrCacuException.h"
#include <string>

StrCacuException::StrCacuException(const string &msg) throw()
{
	n_msg = msg;
}

StrCacuException::StrCacuException(const StrCacuException& other) throw()
{
	n_msg = other.get_msg();
}

StrCacuException::~StrCacuException() throw()
{
}

StrCacuException& StrCacuException::operator = (const StrCacuException& other) throw()
{
	n_msg = other.get_msg();
	return *this;
}

const char* StrCacuException::what() const throw()
{
	return n_msg.c_str();
}

const string& StrCacuException::get_msg() const throw()
{
	return n_msg;
}
