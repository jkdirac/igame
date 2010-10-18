/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/mathematics.h,v $
   $Revision: 1.7 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2006/04/27 01:34:21 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_mathematics
#define COPASI_mathematics

#include <math.h>
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif
#ifndef M_E
#define M_E            2.7182818284590452354   /* e */
#endif

#ifdef WIN32 // These are not part of ANSI C and Visual C++ 6.0 misses them.
static inline double asinh(double value)
{return log(value + sqrt(value * value + 1.0));}

static inline double acosh(double value)
{return log(value + sqrt(value * value - 1.0));}

static inline double atanh(double value)
{return (.5 * log((1.0 + value) / (1.0 - value)));}
#endif // WIN32

#endif // COPASI_mathematics
