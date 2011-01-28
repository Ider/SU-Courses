#ifndef SEMIEXPRESSION_H
#define SEMIEXPRESSION_H
/////////////////////////////////////////////////////////////////////
//  SemiExpression.h - Collects tokens for code analysis           //
//  ver 1.3                                                        //
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
  This module defines a SemiExp class.  Its instances build a sequence 
  of tokens obtained from the Tokenizer module for analysis of code.
  SemiExpressions are lists of tokens that terminate on one of the tokens:
    '{', '}', ';', or '\n' when its line starts with '#'

  This structure is designed to collect just the right amount of inform-
  ation from a code file for analysis.  That is, it collects the smallest
  set of tokens that lead to the detection of grammatical constructs, 
  without having to save part of the sequence for later use or get more
  to complete the detection process.  This simplifies the design of code
  analysis tools.

  Note that assignment and copying of SemiExp instances is supported, using
  the default operations provided by the C++ language.  Copies and assignments
  result in both source and target SemiExp instances sharing the same toker.

  Public Interface:
  =================
  Toker t;                                  // create tokenizer instance
  SemiExp se(&t);                           // create instance and attach
  if(se.get())                              // collect a semiExpression
    std::cout << se.showSemiExp().c_str();  // show it
  int n = se.length();                      // number of tokens in se
  std::string tok = se[2] = "a change";     // indexed read and write
  if(se.find("aTok") < se.length())         // search for a token
    std::cout << "found aTok";  
  se.clear();                               // remove all tokens

  Build Process:
  ==============
  Required files
    - SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp
  Build commands (either one)
    - devenv Project1HelpS06.sln
    - cl /EHsc /DTEST_SEMIEXPRESSION SemiExpression.cpp Tokenizer.cpp \
         /link setargv.obj

  Maintenance History:
  ====================
  ver 1.3 : 17 Jan 09
  - changed SemiExp::getSemiExp() to SemiExp::get()
  - changed SemiExp::showSemiExp() to SemiExp::show()
  - added scope walker to test stub
  ver 1.2 : 10 Feb 06
  - fixed bug in SemiExp::getSemiExp() that caused failure to return
    last group of tokens as a semi-expression if the last character
    in source is not a newline.
  ver 1.1 : 01 Feb 06
  - added an option to return comments as semi-expressions
  - added test, isComment(const std::string& tok)
  ver 1.0 : 12 Jan 06
  - first release

*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ITokCollection.h"
#include "tokenizer.h"

class SemiExp : public ITokCollection
{
public:
  SemiExp(Toker* pTokr);
  ~SemiExp();
  bool get();
  int length();
  std::string& operator[](int n);
  int find(const std::string& tok);
  void push_back(const std::string& tok);
  bool remove(const std::string& tok);
  void toLower();
  void trimFront();
  void clear();
  std::string show();
  void verbose(bool v = true);
  void makeCommentSemiExp(bool commentIsSE = true);
  bool isComment(const std::string& tok);

private:
  Toker* pToker;
  std::vector<std::string> toks;
  bool isTerminator(std::string tok);
  bool Verbose;
  bool commentIsSemiExp;
};

inline int SemiExp::length() { return (int)toks.size(); }

inline void SemiExp::verbose(bool v) { Verbose = v; }

inline void SemiExp::makeCommentSemiExp(bool commentIsSE)
{
  commentIsSemiExp = commentIsSE;
}

inline void SemiExp::clear() { toks.clear(); }

inline void SemiExp::push_back(const std::string& tok)
{
  toks.push_back(tok);
}

#endif
