/**********************************************************************
oberror.h - Handle error messages.
Details at end of error.cpp
 
Copyright (C) 2007 by Chris Morley
Based on original code from OpenBabel 
Copyright (C) 2002 by Stefan Kebekus, 2002-2006 by Geoffrey R. Hutchison
***********************************************************************/
#ifndef OB_ERROR_H
#define OB_ERROR_H

#include <iostream>
#include <iosfwd>
#include <sstream>
#include <string>

namespace mesmer
{

  //! \brief Levels of error and audit messages to allow filtering
  enum obMessageLevel {
    obNone,
    obError,     //!< for critical errors (e.g., cannot read a file)
    obWarning,   //!< for non-critical problems (e.g., molecule appears empty)
    obInfo,      //!< for informative messages (e.g., file is a non-standard format)
    obAuditMsg,  //!< for messages auditing methods which destroy or perceive molecular data (e.g., kekulization, atom typing, etc.)
    obDebug      //!< for messages only useful for debugging purposes
  };

  //******************************************************************
  //Global output streams which by default go to clog
  //They are redirected in a MessageHandler constructor
  extern std::ostream cwarn;
  extern std::ostream cinfo;
  extern std::ostream ctest;

//******************************************************************************
  //! \brief Handle error messages, warnings, debugging information and the like
  class MessageHandler
    {
    public:
      MessageHandler(std::ostream* logstream=NULL);

      //! Send ALL the messages to the specified stream
      void SetLogStream(std::ostream* logstream){_logStream = logstream; }

      //! Throw an error in the specified method with an appropriate level
      //! If context is empty, the default text is used 
      void ThrowError(const std::string &context, const std::string &errorMsg,
                      obMessageLevel level = obDebug) const;

      //! Start logging messages (default)
      void StartLogging() { _logging = true; }
      //! Stop logging messages completely
      void StopLogging()  { _logging = false; }

      //! \brief Set the level of messages to output
      //! (i.e., messages with at least this priority will be output)
      void SetOutputLevel(const obMessageLevel level) { _outputLevel = level; }

      //! \return the current output level
      obMessageLevel GetOutputLevel()const { return _outputLevel; }

      //! Set extra information to be output when using output streams, cerr, etc
      void SetContext(const std::string& txt){ _defaultContext = txt; }

    private:
      const std::string& GetLevelText(obMessageLevel level)const
      {
        static const std::string txt[6] =
          {"", "  ***Error ","  **Warning ",  " *Info ", "  Audit msg ", "  Debug msg "};
        return txt[level];
      }

    private:
      //! Filtering level for messages and logging (messages of lower priority will be ignored
      obMessageLevel         _outputLevel;
      //! The stream to which ALL messages are sent
      std::ostream*          _logStream;
      //! Whether messages will be passed to _logstream
      bool                   _logging;
      //! The default context used when messages sent via cerr, etc
      std::string _defaultContext;
    };

  //*******************************************************************************
  //! \brief A replacement buffer for output streams which passes messages to the message handler
  class obLogBuf : public std::stringbuf
  {
  public:
    //! The constructor sets the destination and level of the messages that are sent.
    obLogBuf(obMessageLevel level, MessageHandler* dest)
      : _messageLevel(level), _handler(dest) {}

    virtual ~obLogBuf() { sync(); } //flush at the end

  protected:
    //! Call MessageHandler::ThrowError() and flush the buffer
    int sync();

  private:
    obMessageLevel _messageLevel;
    MessageHandler* _handler;
  };

//********************************************************************************
  //! RAII class for redirecting output streams to a MessageHandler.
  /// Make an instance, specifying the message handler and, optionally,
  /// a stream (probably a file stream) to which ctest is redirected,
  /// independent of the message handler.
  /// The old behaviour of the streams is restored when the instance 
  /// goes out of scope.
  class OStreamRedirector
  {
  public:
    OStreamRedirector(MessageHandler* handler, std::ostream* Newctest=NULL);
    ~OStreamRedirector();
  private:
    //New buffers for output streams, cerr, etc
    obLogBuf _cerrbuf, _cwarnbuf, _cinfobuf;
    //Store for old buffers, which are restored in destructor
    std::streambuf *_oldcerrbuf, *_oldcwarnbuf, *_oldcinfobuf, *_oldctestbuf;
  };

//Global message handler (I would not to have this here)
extern MessageHandler meErrorLog;

} // end namespace

#endif
//! \file oberror.h
//! \brief Handle error messages, warnings, notices, etc.
