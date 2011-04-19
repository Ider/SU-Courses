#ifndef TOKENIZER_H
#define TOKENIZER_H
/////////////////////////////////////////////////////////////////////
//  Tokenizer.h - Reads words from a file                          //
//  ver 1.9                                                        //
//                                                                 //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module defines a tokenizer class.  Its instances read words from 
  an attached file or string.  Word boundaries occur when a character sequence
  read from the file or string:
  - changes between any of the character types: alphanumeric, punctuator,
    or white space.
  - certain characters are treated as single character tokens, e.g., 
    "(", ")", "{", "}", "[". "]", ";", ".", and "\n".
    You can change the selection with Toker::setMode(Toker::code) or
    Toker::setMode(Toker::xml), or Toker::setSingleCharTokens(somestring);
  - Toker::code is the default tokenizing mode.
  A tokenizer is an important part of a scanner, used to read and interpret
  source code or XML.

  Public Interface:
  =================
  Toker t;                        // create tokenizer instance
  returnComments();               // request comments return as tokens
  if(t.attach(someFileName))      // select file for tokenizing
    string tok = t.getTok();      // extract first token
  int numLines = t.lines();       // return number of lines encountered
  t.lines() = 0;                  // reset line count

  Build Process:
  ==============
  Required files
    - tokenizer.h, tokenizer.cpp
  Build commands (either one)
    - devenv Project1HelpS06.sln
    - cl /EHsc /DTEST_TOKENIZER tokenizer.cpp /link setargv.obj

  Maintenance History:
  ====================
  ver 1.9 : 18 Mar 10
  - added thrown exception if get to end of file in eatQuote()
  ver 1.8 : 02 Mar 10
  - fixed leak of allocated stream.  That required changes to ~Toker() and attach(...).
  ver 1.7 : 31 Jan 09
  - made putback(int) a public, rather than private, member function
  ver 1.6 : 22 Jan 09
  - added Toker::setSingleTokenChars(somestring)
  - added notes about setMode and setSingleTokenChars to Manual
    and Maintenance information.
  ver 1.5 : 17 Jan 09
  - added Toker::mode, either code or xml
  - changed container for single char token ids from vector<char>
    to string
  - added test for end of file in isTokEnd() to fix bug, found by
    Jim DelloStritto that sometimes caused Toker to fail returning
    last character if not a singleCharToken
  ver 1.4 : 10 Feb 07
  - fixed bug in braceCount to eliminate changing count when brace
    is in a quoted string or comment
  ver 1.3 : 24 Feb 06
  - fixed bug in eat comment that hung on ending comment with no
    newline, by testing for stream state good.
  ver 1.2 : 06 Feb 06
  - added stream closing to destructor and attach memeber functions
  ver 1.1 : 01 Feb 06
  - added if test at end of getTok() to avoid returning space after 
    C comment as a token
  ver 1.0 : 12 Jan 06
  - first release

  ToDo:
  =====
  - Richard Zuber, CSE687 Sp2010, reported a bug involving crashes on unicode chars
    in certain calls to the C-Library function isspace(), specifically in isTokEnd().
    He suggested switching to an overload that uses a locale.

    There are many calls to isspace() and other character handling library functions
    that should be checked for this failure, so I, regretably have to postpone that
    exploration to some later time.
*/
//
#include <string>
#include <iostream>
#include <vector>

class Toker
{
public:
  enum mode { code, xml, custom };
  Toker(const std::string& src = "", bool isFile = true);
  ~Toker();
  void setMode(mode md);
  void setSingleCharTokens(std::string tokChars);
  bool attach(const std::string& filename, bool isFile = true);
  std::string getTok();
  void returnComments(bool doReturn = true);
  int& lines();
  int  braceLevel();
  bool isFileEnd();
  int  peek();           // peek at next char (not token)
  void putback(int ch);  // put back char on stream (not token)
  enum state { default_state, comment_state, quote_state };

private:
  std::istream* pIn;
  char prevprevChar, prevChar, currChar, nextChar;
  std::string scTok;
  std::vector<char> putbacks;
  int numLines;
  int braceCount;
  bool doReturnComments;
  bool aCppComment;
  enum state _state;
  mode _mode;

  // private helper functions
  int  get();
  bool getChar();
  bool isSingleCharTok(char ch);
  bool isTokEnd();
  void stripWhiteSpace();
  bool isIdentifierChar(char ch);
  bool isBeginComment();
  bool isEndComment();
  std::string eatComment();
  bool aSingleQuote;
  bool isBeginQuote();
  bool isEndQuote();
  std::string eatQuote();

  // prohibit copying and assignment
  Toker(const Toker &tkr);
  Toker& operator=(const Toker&);
};

inline void Toker::returnComments(bool doReturn)
{
  doReturnComments = doReturn;
}

inline bool Toker::isFileEnd() { return (nextChar == -1); }

inline int& Toker::lines() { return numLines; }

inline int Toker::braceLevel() { return braceCount; }

#endif
