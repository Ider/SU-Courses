#ifndef FUNCTION_INFO_H
#define FUNCTION_INFO_H
//////////////////////////////////////////////////////////////////////
//  functionInfo.h - class that provide	to contain function data	//
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
  This module provide class to contain function, control span, variable
  data, and methods to operate this data
  

  Public Interface:
  =================
  std::vector<funcInfo*> functions;
  display.printAnalysis(packageInfo* package);
  std::cout<< getFunctionSize();
  std::cout<< getFunctionScopeNesting();
  void setEndLine( lineNo);
  void operator++();
  void increaseCyclometer();
  std::string getName();
  std::string getFullName();
  std::string getClassName();
  std::cout<< getBeginLine();
  std::cout<< getBeginBrace();
  std::cout<< getDeepestBrace();
  std::cout<< getCyclometer();
  void addControl(controlInfo* c);

  std::vector<controlInfo*> controls;
  int getControlSize()
  void setEndLine(int lineNo)
  std::string getName()
  int getBeginLine()
  int getBeginBrace()

  std::vector<variableInfo*> variables;
  int getLocality() 
  void setEndLine(int lineNo,std::string file) 
  std::string getName() 
  std::string getType() 
  int getBeginLine()
  bool isEndInTheSameFile()
  void operator++()
  int getReferencedCount()

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

#include <string>
#include <vector>

class controlInfo;
class variableInfo;

////////////////function information//////////////////////////////

class funcInfo
{
public:
	funcInfo(const std::string& funcName, int bLine,int bBrace);
	funcInfo(const std::string& cName, const std::string& fName, int bLine,int bBrace);
	~funcInfo();
	int getFunctionSize() const;
	int getFunctionScopeNesting() const;
	void setEndLine(int lineNo);
	void operator++();
	void increaseCyclometer();
	std::string getName() const;
	std::string getFullName() const;
	std::string getClassName() const;
	int getBeginLine() const;
	int getBeginBrace() const;
	int getDeepestBrace() const;
	int getCyclometer() const;
	void addControl(controlInfo* c);
	std::vector<variableInfo*>& getVariableInfos();

	friend class display;

private:
	const std::string className;
	const std::string name;
	const int beginLine;
	int endLine;
	const int beginBrace;
	int deepestBrace;
	int cyclometer;
	std::vector<controlInfo*> controls;
	std::vector<variableInfo*> variables;
};

//////////////////////////////////////////////////////////////////////////
//constructor
inline funcInfo::funcInfo(const std::string& funcName, int bLine,int bBrace)
	:name(funcName),beginLine(bLine),beginBrace(bBrace)
{
	endLine = -1;
	deepestBrace = bBrace;
	cyclometer = 1;
}

//////////////////////////////////////////////////////////////////////////
//constructor
inline funcInfo::funcInfo(const std::string& cName, const std::string& fName, int bLine,int bBrace)
	:className(cName),name(fName),beginLine(bLine),beginBrace(bBrace)
{
	endLine = -1;
	deepestBrace = bBrace;
	cyclometer = 1;
}
//////////////////////////////////////////////////////////////////////////
//destructor
inline funcInfo::~funcInfo()
{
// 	std::vector<controlInfo*>::iterator cit;
// 
// 	for (cit = controls.begin();cit!=controls.end();++cit)
// 		delete *cit;
// 	controls.clear();
// 
// 	std::vector<variableInfo*>::iterator vit;
// 	for (vit = variables.begin(); vit != variables.end();++vit)
// 		delete (*vit);
// 	variables.clear();
}

//////////////////////////////////////////////////////////////////////////
//return function size (beinLine#-endLine#)
inline int funcInfo::getFunctionSize() const
{
// 	if (endLine<0)
// 		throw std::exception(("Unable to find end of function "+name).c_str());
// 
// 	if (endLine < beginLine)
// 		throw std::exception(("Begin line is bigger than end line in function " + name).c_str());

	return (endLine - beginLine);
}

//////////////////////////////////////////////////////////////////////////
//return Function Scope Nesting (beinLine#-endLine#)
inline int funcInfo::getFunctionScopeNesting() const
{	return (deepestBrace - beginBrace + 1); }

//////////////////////////////////////////////////////////////////////////
//set EndLine
inline void funcInfo::setEndLine(int lineNo){endLine = lineNo;}

//////////////////////////////////////////////////////////////////////////
//increase deepest brace
//
inline void funcInfo::operator++(){++deepestBrace;}

//////////////////////////////////////////////////////////////////////////
//increase Cyclometer
inline void funcInfo:: increaseCyclometer(){++cyclometer;}

//////////////////////////////////////////////////////////////////////////
//get name of function
inline std::string funcInfo::getName() const {return name;}

//////////////////////////////////////////////////////////////////////////
//get name of class that function belong to
inline std::string funcInfo::getClassName() const{return className;}

//////////////////////////////////////////////////////////////////////////
//get name of function that include class name and "::" between them
inline std::string funcInfo::getFullName() const 
{
	if (className.length()>0)
		return className + " :: " + name;
	
	return name;
}

//////////////////////////////////////////////////////////////////////////
//get line # that function implement
inline int funcInfo::getBeginLine() const {return beginLine;}

//////////////////////////////////////////////////////////////////////////
//get brace # that function implement
inline int funcInfo::getBeginBrace() const {return beginBrace;}

//////////////////////////////////////////////////////////////////////////
//get deepest brace # that function contains
inline int funcInfo::getDeepestBrace() const {return deepestBrace;}

//////////////////////////////////////////////////////////////////////////
//get cyclomatic complexity of function
inline int funcInfo::getCyclometer()const {return cyclometer;}

//////////////////////////////////////////////////////////////////////////
//add control span information to function
inline void funcInfo::addControl(controlInfo* c)
{ controls.push_back(c);}
 
//////////////////////////////////////////////////////////////////////////
//return a reference to vector of variable information
inline std::vector<variableInfo*>& funcInfo::getVariableInfos()
{ return variables;}


////////////////control information//////////////////////////////

class controlInfo
{
public:
	controlInfo(const std::string& n,funcInfo* f, int bLine, int bBrace)
		:name(n), func(f), beginLine(bLine), beginBrace(bBrace)
	{	endLine = bLine;}
	~controlInfo();
	int getControlSize() {return (endLine - beginLine);}
	void setEndLine(int lineNo) {endLine = lineNo;}
	std::string getName() {return name;}
	int getBeginLine() {return beginLine;}
	int getBeginBrace(){return beginBrace;}

private:
	const std::string name;
	const funcInfo* func;
	const int beginLine;
	int endLine;
	const int beginBrace;
};

inline controlInfo::~controlInfo(){}
 
////////////////variable information//////////////////////////////

class variableInfo
{
public:
	variableInfo(const std::string& n,const std::string& t,const std::string& f, int bLine)
		:name(n),type(t), beginFile(f), beginLine(bLine)
	{	referencedCount=0;}
	~variableInfo(){}
	int getLocality() {return (endLine - beginLine);}
	void setEndLine(int lineNo,std::string file) 
	{endLine = lineNo;endFile=file;}
	std::string getName() {return name;}
	std::string getType() {return type;}
	int getBeginLine() {return beginLine;}
	bool isEndInTheSameFile(){return beginFile == endFile;}
	void operator++(){++referencedCount;}
	int getReferencedCount(){return referencedCount;}
private:
	const std::string type;
	const std::string name;
	const int beginLine;
	const std::string beginFile;
	std::string endFile;
	int endLine;
	int referencedCount;
};

#endif