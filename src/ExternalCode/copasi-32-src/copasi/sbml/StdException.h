/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/sbml/StdException.h,v $
   $Revision: 1.2 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2006/04/27 01:31:21 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STDEXCEPTION_H__
#define STDEXCEPTION_H__

#include <string>
#include <exception>

/**
 * Simple exception class that implements the what() function of std::exception
 * to specify an error message.
 */
class StdException: public std::exception
  {
  public:
    /**
     * Constructor that sets the error message object to "Error."
     */
    StdException() throw();

    /**
     * Constructor that sets the error message object to the string given.
     */
    explicit StdException(const std::string what) throw();

    /**
     * Destructor that does nothing.
     */
    virtual ~StdException() throw();

    /**
     * Returns the error message object as a character array.
     */
    virtual const char* what() const throw();

  protected:
    std::string message;
  };

#endif
