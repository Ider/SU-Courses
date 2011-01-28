#ifndef ACTIONSANDRULES_H
#define ACTIONSANDRULES_H
/////////////////////////////////////////////////////////////////////
//  ActionsAndRules.h - declares new parsing rules and actions     //
//  ver 1.1                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module defines several action classes.  Its classes provide 
  specialized services needed for specific applications.  The modules
  Parser, SemiExpression, and Tokenizer, are intended to be reusable
  without change.  This module provides a place to put extensions of
  these facilities and is not expected to be reusable.
  

  Public Interface:
  =================
  Toker t(someFile);              // create tokenizer instance
  SemiExp se(&t);                 // create a SemiExp attached to tokenizer
  Parser parser(se);              // now we have a parser
  Rule1 r1;                       // create instance of a derived Rule class
  Action1 a1;                     // create a derived action
  r1.addAction(&a1);              // register action with the rule
  parser.addRule(&r1);            // register rule with parser
  while(se.getSemiExp())          // get semi-expression
    parser.parse();               //   and parse it

  Build Process:
  ==============
  Required files
    - Parser.h, Parser.cpp, ActionsAndRules.h, ActionsAndRules.cpp,
      SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
  Build commands (either one)
    - devenv Project1HelpS06.sln
    - cl /EHsc /DTEST_PARSER parser.cpp ActionsAndRules.cpp \
         semiexpression.cpp tokenizer.cpp /link setargv.obj

  Maintenance History:
  ====================
  ver 1.1 : 17 Jan 09
  - changed to accept a pointer to interfaced ITokCollection instead
    of a SemiExpression
  ver 1.0 : 12 Jan 06
  - first release

*/
//
#include <queue>
#include <string>
#include "Parser.h"
#include "ITokCollection.h"

///////////////////////////////////////////////////////////////
// rule to detect preprocessor statements

class PreprocStatement : public IRule
{
public:
  bool doTest(ITokCollection* pTc)
  {
    if(pTc->find("#") < pTc->length())
    {
      doActions(pTc);
      return true;
    }
    return false;
  }
};

///////////////////////////////////////////////////////////////
// rule to detect function definitions

class FunctionDefinition : public IRule
{
public:
  bool isSpecialKeyWord(const std::string& tok)
  {
    const static std::string keys[]
      = { "for", "while", "switch", "if", "catch" };
    for(int i=0; i<5; ++i)
      if(tok == keys[i])
        return true;
    return false;
  }
  bool doTest(ITokCollection* pTc)
  {
    ITokCollection& tc = *pTc;
    if(tc[tc.length()-1] == "{")
    {
      int len = tc.find("(");
      if(len < tc.length() && !isSpecialKeyWord(tc[len-1]))
      {
        doActions(pTc);
        return true;
      }
    }
    return false;
  }
};

//
///////////////////////////////////////////////////////////////
// action to print preprocessor statement to console

class PrintPreproc : public IAction
{
public:
  void doAction(ITokCollection* pTc)
  {
    std::cout << "\n\n  Preproc Stmt: " << pTc->show().c_str();
  }
};

///////////////////////////////////////////////////////////////
// action to send semi-expression that starts a function def
//        to console

class PrintFunction : public IAction
{
public:
  void doAction(ITokCollection* pTc)
  {
    std::cout << "\n\n  FuncDef Stmt: " << pTc->show().c_str();
  }
};

///////////////////////////////////////////////////////////////
// action to send signature of a function def to console

class PrettyPrintFunction : public IAction
{
public:
  void doAction(ITokCollection* pTc)
  {
    pTc->remove("public");
    pTc->remove(":");
    pTc->trimFront();
    int len = pTc->find(")");
    std::cout << "\n\n  Pretty Stmt:    ";
    for(int i=0; i<len+1; ++i)
      std::cout << (*pTc)[i] << " ";
  }
};

//
///////////////////////////////////////////////////////////////
// action to store a preprocessor statement in queue

class PreprocToQ : public IAction
{
  std::queue<std::string>* pQ;

public:
  PreprocToQ(std::queue<std::string>& resultQ) : pQ(&resultQ)
  {
  }
  void doAction(ITokCollection* pTc)
  {
    pQ->push("Preproc Stmt: " + pTc->show());
  }
};

///////////////////////////////////////////////////////////////
// action to store function signature in queue

class PrettyPrintToQ : public IAction
{
  std::queue<std::string>* pQ;

public:
  PrettyPrintToQ(std::queue<std::string>& resultQ) : pQ(&resultQ)
  {
  }
  void doAction(ITokCollection* pTc)
  {
    pTc->remove("public");
    pTc->remove(":");
    pTc->trimFront();
    int len = pTc->find(")");
    std::string tempStr = "Pretty Stmt:      ";
    for(int i=0; i<len+1; ++i)
      tempStr += (*pTc)[i] + " ";
    pQ->push(tempStr);
  }
};

#endif
