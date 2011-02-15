#ifndef CONFIGUREPARSER_H
#define CONFIGUREPARSER_H
/////////////////////////////////////////////////////////////////////
//  ConfigureParser.h - builds and configures parsers              //
//  ver 1.1                                                        //
//                                                                 //
//  Lanaguage:     Visual C++ 2005                                 //
//  Platform:      Dell Dimension 9150, Windows XP SP2             //
//  Application:   Prototype for CSE687 Pr1, Sp06                  //
//  Author:        Jim Fawcett, CST 2-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module builds and configures parsers.  It builds the parser
  parts and configures them with application specific rules and actions.
  It currently defines two builders, one that parses to the console
  and one used by a form.
  

  Public Interface:
  =================
  ConfigParseToConsole conConfig;
  conConfig.Build();
  conConfig.Attach(someFileName);

  Build Process:
  ==============
  Required files
    - ConfigureParser.h, ConfigureParser.cpp, Parser.h, Parser.cpp,
      ActionsAndRules.h, ActionsAndRules.cpp,
      SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
  Build commands (either one)
    - devenv Project1HelpS06.sln
    - cl /EHsc /DTEST_PARSER ConfigureParser.cpp parser.cpp \
         ActionsAndRules.cpp \
         semiexpression.cpp tokenizer.cpp /link setargv.obj

  Maintenance History:
  ====================
  ver 1.1 : 01 Feb 06
  - cosmetic changes to ConfigureParser.cpp
  ver 1.0 : 12 Jan 06
  - first release

*/

//
#include "Parser.h"
#include "SemiExpression.h"
#include "Tokenizer.h"
#include "ActionsAndRules.h"
#include "iderRulesAndActions.h"

///////////////////////////////////////////////////////////////
// build parser that writes its output to console

class ConfigParseToConsole : IBuilder
{
public:
  ConfigParseToConsole();
  ~ConfigParseToConsole();
  bool Attach(const std::string& name, bool isFile=true);
  Parser* Build();

private:
  // Builder must hold onto all the pieces

  Toker* pToker;
  SemiExp* pSemi;
  Parser* pParser;
  
  // and the the Rules and Actions as well

  PreprocStatement* pPreprocStatement;
  PrintPreproc* pPrintPreproc;
  FunctionDefinition* pFunctionDefinition;
  PrintFunction* pPrintFunction;
  PrettyPrintFunction* pPrettyPrintFunction;

  // prohibit copies and assignments

  ConfigParseToConsole(const ConfigParseToConsole&);
  ConfigParseToConsole& operator=(const ConfigParseToConsole&);
};

//
///////////////////////////////////////////////////////////////
// build parser that stores its output in queue

class ConfigParseToQueue : IBuilder
{
public:
  ConfigParseToQueue();
  ~ConfigParseToQueue();
  bool Attach(const std::string& name, bool isFile=true);
  Parser* Build();
  std::queue<std::string>* GetQueue();

private:

  // Builder must hold onto all the pieces

  Toker* pToker;
  SemiExp* pSemi;
  Parser* pParser;
  std::queue<std::string>* pQueue;
  
  // and the the Rules and Actions as well

  PreprocStatement* pPreprocStatement;
  PreprocToQ* pPreprocToQ;
  FunctionDefinition* pFunctionDefinition;
  PrettyPrintToQ* pPrettyPrintToQ;

  // prohibit copies and assignments

  ConfigParseToQueue(const ConfigParseToQueue&);
  ConfigParseToQueue& operator=(const ConfigParseToQueue&);
};

inline std::queue<std::string>* ConfigParseToQueue::GetQueue() 
{ 
  return pQueue; 
}



///////////////////////////////////////////////////////////////
// build parser that writes its output to console
// used by student Ider Zheng
class IderConfigParseToConsole : IBuilder
{
public:
	IderConfigParseToConsole();
	IderConfigParseToConsole(parserHelper* h);
	~IderConfigParseToConsole();
	bool Attach(const std::string& name, bool isFile=true);
	bool Attach(const std::string& name, packageInfo* pack);
	Parser* Build();

private:
	// Builder must hold onto all the pieces
	parserHelper* helper;

	Toker* pToker;
	SemiExp* pSemi;
	Parser* pParser;

	// and the the Rules and Actions as well
	ClassBeginRule* cbr;
	ClassBeginAction* cba;
	ClassEndRule* cer;
	ClassEndAction* cea;

	FunctionBeginRule* fbr;
	FunctionBeginAction* fba;
	FuntionEndRule* fer;
	FuntionEndAction* fea;

	FunctionCyclomaticRule* fcr;
	FunctionCyclomaticAction* fca;

	CtrlSpanBeginRule* sbr;
	CtrlSpanBeginAction* sba;
	CtrlSpanEndRule* ser;
	CtrlSpanEndAction* sea;

	// prohibit copies and assignments

	IderConfigParseToConsole(const IderConfigParseToConsole&);
	IderConfigParseToConsole& operator=(const IderConfigParseToConsole&);
};

#endif
