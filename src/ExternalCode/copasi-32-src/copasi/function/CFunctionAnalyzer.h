// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/function/CFunctionAnalyzer.h,v $
//   $Revision: 1.10 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2008/12/18 17:33:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CFunctionAnalyzer
#define COPASI_CFunctionAnalyzer

#include <vector>
#include <iostream>
#include <string>

class CEvaluationNode;
class CModel;
class CReaction;
class CFunction;
class CFunctionParameters;

/**
 * This class performs an analysis of a kinetic function. The function
 * to analyze is passed to the constructor. The result can be retrieved
 * with the getResult() method. The Result class has methods for reporting.
 * The reporting methods may assume that the function (and possibly the reaction)
 * still exists, so don't delete the function between the analysis and the
 * reporting of the results!
 */
class CFunctionAnalyzer
  {
  public:
    /**
    * This is the base class of the arithmetics of the function analyzer. It describes possibilities for values.
    * It basically consists of some flags that tell whether the value can be positive, can be negative, can
    * be zero, or invalid, or if an actual exact numerical value is known.
    * The usual arithmetic operators are defined for this class, the most important functions need to be
    * implemented still. The missing functions are not critical since there is a save fallback: If you do not
    * know how to perform a specific operation on CValues, the result should be (unknown|invalid).
    */
    class CValue
      {
      public:
        enum Status
        {
          novalue = 0,
          negative = 1,
          zero = 2,
          positive = 4,
          invalid = 8,
          known = 16,
          unknown = 7
        };

        CValue()
            : mStatus(Status(novalue)), mDouble(0.0) {};

        CValue(Status status)
            : mStatus(status), mDouble(0.0) {};

        CValue(const double & d)
            : mStatus(known), mDouble(d) {};

        const double & getValue() const {return mDouble;};

        /**
         * set value to be the only possible value
         */
        void setValue(const double & value) {mDouble = value; mStatus = known;};

        const Status & getStatus() const {return mStatus;};

        void setStatus(const Status & status) {mStatus = status;};

        CValue operator*(const CValue & rhs) const;
        CValue operator/(const CValue & rhs) const;
        CValue operator+(const CValue & rhs) const;
        CValue operator-(const CValue & rhs) const;
        CValue operator^(const CValue & rhs) const;

        bool isPositive() const;
        bool containsPositive() const;
        bool isZero() const;
        bool containsZero() const;
        bool isNegative() const;
        bool containsNegative() const;
        bool isInvalid() const;
        bool containsInvalid() const;

        bool operator==(const CValue & rhs) const;
        CValue invert() const;

      protected:

        /**
         * convert a CValue with status "known" to a more general status.
         */
        //      CValue generalize() const;

        static CValue generalize(const double & d);

        void Or(int s) {mStatus = Status(mStatus | s);};
        void Or(const CValue & v); //  {mStatus = Status(mStatus | s);};

        /**
         * add the value to the set off possible values
         */
#ifdef WIN32 // To prevent a fatal compiler error in Visual Studio C++ 6.0
        void orValue(const double value) {Or(CValue(value)); /*  mDouble = value; Or(known);*/};
#else
        void orValue(const double & value) {Or(CValue(value)); /*  mDouble = value; Or(known);*/};
#endif

      private:
        Status mStatus;
        double mDouble;

        /**
          * insert operator
          */
        friend std::ostream & operator<<(std::ostream &os, const CValue & v);
      };

    /**
     * This class contains the result of the analysis of one function.
     */
    class Result
      {
      public:

        /**
         * This contains low level information about one function. The Result class contains
         * three instances of this structure: For the complete function and for the forward and
         * backwards part of a reversible function
         */
        struct FunctionInformation
          {
            std::vector<CValue> mUnchangedParameters;
            std::vector<std::pair<std::pair<int, std::string>, std::vector<CValue> > > mSubstrateZero;
            std::vector<std::pair<std::pair<int, std::string>, std::vector<CValue> > > mProductZero;

            void writeTable(std::ostream & os, bool rt) const;

            /**
             * This writes a (hopefully) user understandable interpretation of the results to os.
             * The return value indicates if a problem was reported.
             */
            bool writeAnalysis(std::ostream & os, bool rt, bool reversible) const;
          };

        Result();
        void clear() {*this = Result();};

        /**
         * writes a text report about the function to the stream. The return value
         * indicates if a problem was reported.
         */
        bool writeResult(std::ostream & os, bool rt, bool verbose) const;

        //void writeTable(std::ostream & os, bool rt) const;

        const CFunction * mpFunction;
        bool mIrreversibleKineticsWithProducts;

        /** low level information about the original function */
        FunctionInformation mOriginalFunction;

        bool mReversibleNonSplitable;

        /** low level information about the forward part of the function */
        FunctionInformation mFPart;

        /** low level information about the backwards part of the function */
        FunctionInformation mBPart;
      };

    void checkKineticFunction(const CFunction * f, const CReaction * reaction = NULL);

    CFunctionAnalyzer(const CFunction * f, const CReaction * reaction = NULL)
    {checkKineticFunction(f, reaction);};

    const Result & getResult() const {return mResult;};

    /**
     * Mode tells how to interpret an object in CValue arithmetics.
     * NOOBJECT means objects are invalid (e.g. for functions, where no object nodes should occur).
     * GENERAL means concentrations and volumes are positive, all other values positive, zero, or negative.
     * POSITIVE means all objects are positive. ACTUAL means the actual value is used for local parameters and constant values.
     */
    enum Mode {NOOBJECT, GENERAL, POSITIVE, ACTUAL };

    /**
     * Do the CValue arithmetics of a tree. The callParameters contain the CValues corresponding
     * to the CEvaluationNodeVariable nodes. The value of mode should not have an effect if this is called
     * for a function tree.
     */
    static CValue evaluateNode(const CEvaluationNode * node, const std::vector<CValue> & callParameters, Mode mode);

    /**
     * constructs call parameters for use with the evaluateNode() method
     */
    static void constructCallParameters(const CFunctionParameters & fp, std::vector<CValue> & callParameters, bool posi);

  protected:

    Result mResult;

    /**
     * constructs call parameters for use with the evaluateNode() method, using the actual values for
     * local parameters and fixed entities.
     */
    static void constructCallParametersActualValues(std::vector<CValue> & callParameters, /*const CModel* model,*/ const CReaction* reaction);

  public:
    //convenience function to help with writing the reports
    //static std::string write(int level, bool rt, const std::string & text);
    static std::string write(int level, bool rt, const std::string & text, const std::string & longText);
  };

#endif
