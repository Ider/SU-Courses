#ifndef IDER_DISPLAY_H
#define IDER_DISPLAY_H
//////////////////////////////////////////////////////////////////////
//  display.h - print analysis result to console				//
//  ver 1.0															//
//																	//
//  Language:      Visual C++ 2010, SP1								//
//  Platform:      Mac Book Pro, Windows 7 Professional				//
//  Application:   Prototype for CSE687 Pr1, Sp09					//
//  Author:        Ider Zheng, Syracuse University					//
//                 (315) 560-4977, ider.zheng@gmail.com			    //
//////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module print all package informations to console.
  It will generate good format to present the results
  

  Public Interface:
  =================
  display displayer;
  display.printAnalysis(packageInfo* package);

  Build Process:
  ==============
  Required files
  -ActionsAndRules.h    ActionsAndRules.cpp
  ConfigureParser.h    ConfigureParser.cpp
  display.h    display.cpp
  fileHandler.h    fileHandler.cpp
  FileSystem.h    FileSystem.cpp
  functionInfo.h    iderRulesAndActions.cpp
  iderRulesAndActions.h    Parser.cpp
  infoCollection.h    ScopeStack.cpp
  itokcollection.h    SemiExpression.cpp
  packageInfo.h    Tokenizer.cpp
  Parser.h
  ScopeStack.h
  SemiExpression.h
  test.h

  Build commands (either one)
    - devenv CodeAnalysis.sln
    - cl /EHsc /DTEST_PARSER ConfigureParser.cpp parser.cpp \
         ActionsAndRules.cpp \
         semiexpression.cpp tokenizer.cpp /link setargv.obj

*/

#include "packageInfo.h"

class display
{
public:
	display():optimalFuncSize(50),optimalCtrlSpan(20)
		,optimalCyclom(10),optimalReference(10),optimalLocality(20){}
	void printAnalysis(packageInfo* package);

private:
	void printPackageInfo();
	void printFunctions();
	void printControls(std::vector<controlInfo*>& ctrls);
	void printVaraibels(std::vector<variableInfo*>& vInfos);
	packageInfo* pack;

	const int optimalFuncSize;
	const int optimalReference;
	const int optimalCyclom;
	const int optimalCtrlSpan;
	const int optimalLocality;
};


#endif

