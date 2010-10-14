// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/copasi.h,v $
//   $Revision: 1.71 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/02/11 12:59:30 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// copasi.h
//
// This file contains compatability issues
// (C) Stefan Hoops 2001
//

#ifndef COPASI_copasi
#define COPASI_copasi

/* #define AVOGADRO 6.0221367e23 */
#define AVOGADRO 6.0221415e23

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
# if  _MSC_VER >= 1400
#  define _CRT_SECURE_NO_DEPRECATE

// avoid the following warning:
// The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup. See online help for details.
#  pragma warning(disable : 4996)
# endif
#endif  // WIN32

#include <assert.h>
#include <fstream>

//YH: new defined parameters used by more than one classes
#define SS_FOUND 1             //steady state found
#define SS_NOT_FOUND 0         //steady state not found
#define SS_SINGULAR_JACOBIAN 2
#define SS_DAMPING_LIMIT 3
#define SS_ITERATION_LIMIT 4
#define MCA_OK 0
#define MCA_SINGULAR 1

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
#if (defined __SUNPRO_CC && defined Linux)
#ifndef LLONG_MAX
#define  LLONG_MAX _RWSTD_LLONG_MAX
#endif
#endif // Sun C++ Compiler under Linux

#if (defined SunOS || defined __CYGWIN__ || defined Darwin)
# define C_INT64 long long int
# ifndef LLONG_MAX
#  define  LLONG_MAX LONG_LONG_MAX
# endif
# define LLONG_CONST(n) n ## LL
# define C_INT32 long
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define abs64 abs
#else
#ifdef WIN32
# define C_INT64 __int64
# ifndef LLONG_MAX
#  define LLONG_MAX _I64_MAX
# endif
# define LLONG_CONST(n) n ## i64
# define C_INT32 int
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define vsnprintf _vsnprintf // they just have a different name for this guy
# define snprintf  _snprintf  // they just have a different name for this guy
# define strcasecmp _stricmp  // they just have a different name for this guy
# define strdup _strdup       // they just have a different name for this guy
# define isnan _isnan         // they just have a different name for this guy
# define finite _finite       // they just have a different name for this guy
# define min _cpp_min         // they just have a different name for this guy
# define max _cpp_max         // they just have a different name for this guy
# define abs64 _abs64
#else
# define C_INT64 long long int
# ifndef LLONG_MAX
#  define  LLONG_MAX LONG_LONG_MAX
# endif
# define LLONG_CONST(n) n ## LL
# define C_INT32 long
# define C_INT16 short
# define C_FLOAT64 double
# define C_FLOAT32 float
# define abs64 abs
#endif
#endif

#ifdef Darwin
# ifndef isnan
#  define isnan(__x) ((__x == __x) != true)
# endif
#endif

#if (defined __GNUC__ && __GNUC__ < 3)
# define ios_base ios
#endif

#if (defined USE_MKL || defined USE_SUNPERF || defined __x86_64)
# define C_INT int
#else
# if (defined USE_CLAPACK || defined USE_LAPACK || defined Darwin)
#  define C_INT long
# else
#  error Neither USE_CLAPACK, USE_LAPACK, USE_SUNPERF, or USE_MKL is defined!
# endif
#endif

enum TriLogic
{
  TriUnspecified = -1,
  TriFalse = 0,
  TriTrue = 1
};

/* This is necessary to link with Intel MKL 721 under Visual C++ 8 */
// #if defined COPASI_MAIN && defined USE_MKL && defined _MSC_VER && _MSC_VER > 1200 && defined _DLL
// extern "C" {FILE _iob[3] = {__iob_func()[0], __iob_func()[1], __iob_func()[2]};}
// #endif

#ifdef COPASI_MAIN
class CCopasiRootContainer;
CCopasiRootContainer * pRootContainer = NULL;
#endif

/* Define Constructor/Destructor Trace */
#ifdef COPASI_DEBUG
# include <time.h>
# include <sys/timeb.h>

# ifdef COPASI_MAIN
#  ifndef Darwin
struct timeb C_init_time;
unsigned C_INT32 C_last_time = 0;
unsigned C_INT32 C_this_time;
#  endif // !Darwin
std::ofstream DebugFile("trace");
# else // not COPASI_MAIN
#  include <fstream>
#  ifndef Darwin
extern struct timeb C_init_time;
extern unsigned C_INT32 C_last_time;
extern unsigned C_INT32 C_this_time;
#  endif // !Darwin
extern std::ofstream DebugFile;
# endif // COPASI_MAIN

# ifndef Darwin
#  include <iostream>
#  define TIME_TRACE(f, l) {\
    ftime(&C_init_time); \
    C_this_time = C_init_time.time * 1000 + C_init_time.millitm; \
    DebugFile << f <<"(" << l << "):\t" << C_this_time - C_last_time  << std::endl; \
    C_last_time = C_this_time;\
  }
# endif // !Darwin

# if (defined COPASI_TRACE_CONSTRUCTION)
#  include <typeinfo>
#  define CONSTRUCTOR_TRACE \
  {DebugFile << "Construct:\t" << typeid(*this).name() \
    << "\tAddress:\t" << (void *) this << std::endl;}
#  define DESTRUCTOR_TRACE \
  {DebugFile << "Destruct:\t" << typeid(*this).name() \
    << "\tAddress:\t" << (void *) this << std::endl;}
# endif // COPASI_TRACE_CONSTRUCTION

# define DEBUG_OUT(s) {DebugFile << (s) << std::endl;}
#else
# ifndef NDEBUG
#  define NDEBUG
# endif // not NDEBUG
# define DEBUG_OUT(s)
#endif // COPASI_DEBUG

#ifndef CONSTRUCTOR_TRACE
# define CONSTRUCTOR_TRACE
#endif

#ifndef DESTRUCTOR_TRACE
# define DESTRUCTOR_TRACE
#endif

#ifndef TIME_TRACE
# define TIME_TRACE(f, l)
#endif

// protected free
#define pfree(p) {if (p) {free(p); p = NULL;}}
#define pdelete(p) {if (p) {delete p; p = NULL;}}
#define pdeletev(p) {if (p) {delete[] p; p = NULL;}}
#define pcleanup(p) {if (p) {p->cleanup(); delete p; p = NULL;}}

// suppress unused parameter warnings
#define C_UNUSED(p)
#define COPASI_DEPRECATED
#define C_INVALID_INDEX ((unsigned C_INT32) -1)
#endif // COPASI_copasi
