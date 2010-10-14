// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/utilities/CCopasiMessage.h,v $
//   $Revision: 1.62 $
//   $Name: Build-31 $
//   $Author: shoops $
//   $Date: 2010/02/03 17:18:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiMessage class.
 *  New Class for COPASI message handling. (C) Stefan Hoops 2001.
 */

#ifndef COPASI_CCopasiMessage
#define COPASI_CCopasiMessage

#include <string>
#include <deque>

typedef struct MESSAGES {unsigned C_INT32 No; const char * Text;}
Message;

#define MCopasiBase              5000
#define MCReadConfig             MCopasiBase + 100
#define MCWriteConfig            MCopasiBase + 200
#define MCRange                  MCopasiBase + 300
#define MCKinFunction            MCopasiBase + 400
#define MCCopasiVector           MCopasiBase + 500
#define MCFunctionParameters     MCopasiBase + 600
#define MCMassAction             MCopasiBase + 700
#define MCCopasiMethod           MCopasiBase + 800
#define MCReaction               MCopasiBase + 900
#define MCParameter              MCopasiBase + 1000
#define MCChemEq                 MCopasiBase + 1100
#define MCTrajectoryMethod       MCopasiBase + 1200
#define MCXML                    MCopasiBase + 1300
#define MCCopasiMessage          MCopasiBase + 1400
#define MCConfiguration          MCopasiBase + 1500
#define MCOptimization           MCopasiBase + 1600
#define MCSBML                   MCopasiBase + 1700
#define MCTrajectoryProblem      MCopasiBase + 1800
#define MCDirEntry               MCopasiBase + 1900
#define MCFunction               MCopasiBase + 2000
#define MCMathML                 MCopasiBase + 2100
#define MCEvaluationNodeObject   MCopasiBase + 2200
#define MCCopasiTask             MCopasiBase + 2300
#define MCSteadyState            MCopasiBase + 2400
#define MCFitting                MCopasiBase + 2500
#define MCObject                 MCopasiBase + 2600
#define MCLyap                   MCopasiBase + 2700
#define MCODEExporter            MCopasiBase + 2800
#define MCRegistration           MCopasiBase + 2900
#define MCTSSAMethod             MCopasiBase + 3000
#define MCTSSAProblem            MCopasiBase + 3100
#define MCEigen                  MCopasiBase + 3200
#define MCMiriam                 MCopasiBase + 3300
#define MCMathModel              MCopasiBase + 3400
#define MCModelMerging           MCopasiBase + 3500
#define MCModelExpansion         MCopasiBase + 3600
#define MCEFMAnalysis            MCopasiBase + 3700

/**
 *  This throws an exception with information where the error occurred.
 */
#define fatalError() {CCopasiMessage(CCopasiMessage::EXCEPTION, \
                                       "%s (%d) compiled: %s %s", \
                                       __FILE__, __LINE__, __DATE__, __TIME__);}

class CCopasiMessage
{
public:
  enum Type
  {
    RAW = 0,
    TRACE = 1,
    COMMANDLINE = 2,
    WARNING = 3,
    // In the case that ERROR is defined we have to remove its definition
    // temporarily.
#ifdef ERROR
# undef ERROR
#endif
    ERROR = 4,
    EXCEPTION = 5,
    RAW_FILTERED = 128,
    TRACE_FILTERED = 129,
    COMMANDLINE_FILTERED = 130,
    WARNING_FILTERED = 131,
    ERROR_FILTERED = 132,
    EXCEPTION_FILTERED = 133
  };

  // Attributes

private:
  /**
   * Message text.
   */
  std::string mText;

  /**
   * Message type.
   */
  CCopasiMessage::Type mType;

  /**
   * Message Number
   */
  unsigned C_INT32 mNumber;

#ifndef WIN32
  /**
   * The stack of messages. Each message created with one of
   * the specific constructors is automatically added to the stack.
   */
  static std::deque< CCopasiMessage > mMessageDeque;
#endif // not WIN32

  // Operations

public:
  /**
   * This function peeks at the first message created in COPASI.
   * If no more messages are in the dequeue the message
   * (MCCopasiMessage + 1, "Message (1): No more messages." is returned.
   * @return const CCopasiMessage & message
   */
  static const CCopasiMessage & peekFirstMessage();

  /**
   * This function peeks at the last message created in COPASI.
   * If no more messages are in the dequeue the message
   * (MCCopasiMessage + 1, "Message (1): No more messages." is returned.
   * @return const CCopasiMessage & message
   */
  static const CCopasiMessage & peekLastMessage();

  /**
   * This function retrieves the first message created in COPASI.
   * Consecutive calls allow for the retrieval of all generated
   * messages in chronological order. If no more messages are in
   * the dequeue the message (MCCopasiMessage + 1, "Message (1):
   * No more messages." is returned.
   * @return CCopasiMessage  message
   */
  static CCopasiMessage getFirstMessage();

  /**
   * This function retrieves the last message created in COPASI.
   * Consecutive calls allow for the retrieval of all generated
   * messages in reverse chronological order. If no more messages
   * are in the dequeue the message (MCCopasiMessage + 1, "Message
   * (1): No more messages." is returned.
   * @return CCopasiMessage message
   */
  static CCopasiMessage getLastMessage();

  /**
   * Retrieve the text of all messages in the dequeue in chronological
   * or reverse chronological order. If more than on message is in
   * the dequeue the messages are separated by an empty line.
   * @return std::string messageTexts
   */
  static std::string getAllMessageText(const bool & chronological = true);

  /**
   * This function clears the message stack.
   */
  static void clearDeque();

  /**
   * Retrieve the size of the dequeue
   * @return unsigned C_INT32 size
   */
  static unsigned C_INT32 size();

  /**
   * Retrieve highest severity of the messages in the dequeue.
   * @return const CCopasiMessage::Type & highestSeverity
   */
  static CCopasiMessage::Type getHighestSeverity();

  /**
   * Check whether a message with the given number is in the dequeue
   * @param const unsigned C_INT32 & number
   * @return bool found
   */
  static bool checkForMessage(const unsigned C_INT32 & number);

  /**
   *  Default constructor.
   *  This creates a default error messages, which actually does nothing.
   */
  CCopasiMessage();

  /**
   *  Copy constructor.
   *  @param const CCopasiMessage & src
   */
  CCopasiMessage(const CCopasiMessage & src);

  /**
   *  Specified constructor.
   *  This creates a formated message.
   *  @param CCopasiMessage::Type type (RAW|TRACE|WARNING|ERROR)
   *  @param const char * format (printf like format string)
   *  @param ... arguments like in printf
   */
  CCopasiMessage(Type type, const char *format, ...);

  /**
   *  Specified constructor.
   *  This creates a formated message.
   *  @param CCopasiMessage::Type type (RAW|TRACE|WARNING|ERROR)
   *  @param unsigned C_INT32 number (message number see message.h)
   *  @param ... arguments like in printf
   */
  CCopasiMessage(Type type, unsigned C_INT32 number, ...);

  /**
   *  Destructor.
   */
  ~CCopasiMessage();

  /**
   *  Assignment operator.
   */
  CCopasiMessage &operator=(const CCopasiMessage & RHS);

  /**
   *  Retrieves the text of the message.
   *  @return "const string &" mMessage
   */
  const std::string & getText() const;

  /**
   *  Retrieves the type of the message.
   *  @return "const CCopasiMessage::Type &" mType
   */
  const CCopasiMessage::Type & getType() const;

  /**
   *  Retrieves the number of the message.
   *  @return "const unsigned C_INT32 &" mNumber
   */
  const unsigned C_INT32 & getNumber() const;

private:
  /**
   *  The actual constructor of a message.
   *  @param const bool & throw (default: false)
   *  @param text message text
   */
  void handler(const bool & _throw = false);

  /**
   *  Inserts line breaks in the message text.
   */
  void lineBreak();
};

#endif // COPASI_CCopasiMessage
