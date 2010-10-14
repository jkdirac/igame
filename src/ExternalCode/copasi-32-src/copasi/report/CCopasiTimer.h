/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/report/CCopasiTimer.h,v $
   $Revision: 1.7 $
   $Name: Build-31 $
   $Author: gauges $
   $Date: 2006/10/15 08:00:56 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CCopasiTimer
#define COPASI_CCopasiTimer

#include "report/CCopasiObject.h"
#include "utilities/CopasiTime.h"

class CCopasiTimer: public CCopasiObject
  {
  public:
    /**
     * Enumeration of timer types
     */
    enum Type
    {
      WALL = 0,
      CPU
    };

    // Operations
    /**
     * Default constructor
     * @param const Type & type (default: WALL)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiTimer(const Type & type = WALL,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CCopasiTimer & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiTimer(const CCopasiTimer & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CCopasiTimer();

    /**
     * Start or restart the timer.
     * @return bool success
     */
    bool start();

    /**
     * Actualizes the timer.
     */
    void refresh();

    /**
     * Retrieve the elapsed time.
     * @return const CCopasiTimeVariable & elapsedTime
     */
    const CCopasiTimeVariable & getElapsedTime();

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    virtual void * getValuePointer() const;

  private:
    // Attributes
    /**
     * The timer type
     */
    Type mType;

    /**
     * The start time of the timer.
     */
    CCopasiTimeVariable mStartTime;

    /**
     * The elapsed time of the timer.
     */
    CCopasiTimeVariable mElapsedTime;

    /**
     * The elapsed time as a double used for reporting.
     */
    C_FLOAT64 mElapsedTimeSeconds;
  };

#endif // COPASI_CCopasiTimer
