#ifndef PACKAGE_INFO_H
#define PACKAGE_INFO_H
//////////////////////////////////////////////////////////////////////
//  packageInfo.h - class that contains all package informations	//
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
  This module provide a class that contains all package information
  and parser helper that used by parser to save temp data
  

  Public Interface:
  =================
  packageInfo pack;
  addFunction(funcInfo* func)
  parserHelper* helper = new parserHelper()

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

#include <vector>
#include <stack>
#include <string>
#include "functionInfo.h"


class packageInfo
{
public:
	void addFileName(const std::string& fName){fileNames.push_back(fName);}
	void addFunction(funcInfo* func)
	{functions.push_back(func);}
	std::string& operator[](int n) {return	fileNames[n];}
	int fileCount(){return fileNames.size();}
	friend class display;
	
private:
	std::vector<funcInfo*> functions;
	std::vector<std::string> fileNames;

};


class parserHelper
{
public:
	std::string& getFileName(){return fileName;}
	void setFileName(const std::string& fName){fileName = fName;}
	std::string& getCurrentClass(){return curClass;}
	void setCurrentClass(const std::string& className){curClass = className;}
	funcInfo* getCurrentFunction(){return curFunc;}
	void setCurrentFunction(funcInfo* func){curFunc = func;}
	int getClassBeginBrace(){return classBeginBrace;}
	void setClassBeginBrace(int bBrace){ classBeginBrace = bBrace;}
	//int getCtrlIndex(){ return ctrlIndex;}
	//void setCtrlIndex(int index){ctrlIndex = index;}
	void resetHelper();
	void pushControl(controlInfo* ctrl){ctrls.push(ctrl); prePopedCtrl = NULL;}
	controlInfo* topControl(){return ctrls.empty()? NULL : ctrls.top();}
	controlInfo* popControl()
	{
		if (ctrls.empty())return NULL;
		prePopedCtrl = ctrls.top();
		ctrls.pop();
		return prePopedCtrl;
	}
	controlInfo* getPrePopedControl(){return prePopedCtrl;}
	std::string& getVariableName(){return variableName;}
	std::string& getVariableType(){return variableType;}	
	void setVariable(const std::string& name,const std::string& type)
	{variableName = name; variableType =type;}

	variableInfo*  getReferecedVariable(){return referecedVariable;}
	void  setReferecedVariable(variableInfo* rv){referecedVariable = rv;}

private:
	std::string fileName;
	std::string curClass;
	int  classBeginBrace;
	funcInfo* curFunc;
	//int ctrlIndex;
	controlInfo* prePopedCtrl;
	std::stack<controlInfo*> ctrls;
	std::string variableName;
	std::string variableType;
	variableInfo* referecedVariable;
};

//////////////////////////////////////////////////////////////////////////
//reset all private data members of parser helper to default value
inline void parserHelper::resetHelper()
{
	classBeginBrace = -1;
	curClass = "";
	variableName="";
	variableType="";
	referecedVariable=NULL;
	prePopedCtrl=NULL;
	curFunc = NULL;
	//ctrlIndex = -1;
	while (!ctrls.empty())ctrls.pop();
}

#endif 