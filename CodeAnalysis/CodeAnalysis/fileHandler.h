#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
//////////////////////////////////////////////////////////////////////
//  fileHandler.h - handle files that need to be analysised			//
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
  This module get files from given directories and generate packageInfo
  to obtain all analysis informations. Configure a parser and analysis
  all files. Finally, print these results.
  

  Public Interface:
  =================
  fileHandler hanlder
  void attach(std::string path);
  void attach(int argc, char* argv[]);
  void parse();
  void printResult();

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
#include "ConfigureParser.h"
#include "Parser.h"
#include "display.h"
#include "FileSystem.h"
#include <map>

typedef std::pair<std::string, packageInfo*> packPair;
typedef std::map<std::string, packageInfo*> packMap;
typedef std::map<std::string, packageInfo*>::iterator  mapIterator;
class fileHandler
{
public:
	fileHandler()
	{
		helper = new parserHelper();
		config = new IderConfigParseToConsole(helper);
		pParser = config->Build();

		dispayer = new display();
	}
	~fileHandler();

	void attach(std::string path);
	void attach(int argc, char* argv[]);
	void parse();
	void printResult();

private:
	void clearResult()
	{
		if (results.size()==0)return;
		packMap::iterator it;
		for ( it=results.begin() ; it != results.end(); it++ )
			delete (it->second);
		results.clear();
	}

	std::string getFileKeyName(std::string fileName);

	bool getCommands(int argc, char* argv[]);
	void getFiles();
	void getFiles(std::string path, std::string& pattern);
	void getSubFiles(std::string path, std::string& pattern);
	IderConfigParseToConsole* config;
	Parser* pParser;
	parserHelper* helper;
	display* dispayer;

	std::vector<std::string> pattens;
	std::string rPath;
	bool needRecursion;
	packMap results;

	WinTools_Extracts::FileHandler fh;
};

inline fileHandler::~fileHandler()
{
	//delete pParser; //it has been deleted in config
	delete config;
	delete helper;
	delete dispayer;

	clearResult();
}


#endif