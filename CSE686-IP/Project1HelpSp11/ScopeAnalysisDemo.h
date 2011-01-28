#ifndef SCOPEANALYSISDEMO_H
#define SCOPEANALYSISDEMO_H
/////////////////////////////////////////////////////////////////////
//  ScopeAnalysisDemo.cpp - demo recursive descent scope analysis  //
//  ver 1.1                                                        //
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
  This module demonstrates how to implement recursive descent parsing.
  The demonstration does parsing of code scopes, not XML.  That is,
  of course, left as an exercise for the student.

  Build Process:
  ==============
  Required files
    - ScopeAnalysisDemo.h, ScopeAnalysisDemo.cpp,
      SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp
  Build commands (either one)
    - devenv Project1HelpS09.sln
    - cl /EHsc ScopeAnalysisDemo.cpp SemiExpression.cpp Tokenizer.cpp \
         /link setargv.obj

  Maintenance History:
  ====================
  ver 1.1 : 24 Jan 10
  - push token "function" instead of the function's name
  - added some comments
  ver 1.0 : 18 Jan 09
  - first release

*/
#include <stack>
#include "SemiExpression.h"

class scoper
{
public:
  scoper(SemiExp& semi) : se(semi) {}
  void showStack();
  void walkScopes();
private:
  std::stack<std::string> scopeStk;
  SemiExp& se;
};

#endif
