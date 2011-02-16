#ifndef FUNCTION_INFO_H
#define FUNCTION_INFO_H

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

inline funcInfo::funcInfo(const std::string& funcName, int bLine,int bBrace)
	:name(funcName),beginLine(bLine),beginBrace(bBrace)
{
	endLine = -1;
	deepestBrace = bBrace;
	cyclometer = 1;
}

inline funcInfo::funcInfo(const std::string& cName, const std::string& fName, int bLine,int bBrace)
	:className(cName),name(fName),beginLine(bLine),beginBrace(bBrace)
{
	endLine = -1;
	deepestBrace = bBrace;
	cyclometer = 1;
}

inline funcInfo::~funcInfo()
{
	std::vector<controlInfo*>::iterator cit;
	for (cit = controls.begin();cit!=controls.end();++cit)
		delete (*cit);
	controls.clear();

	std::vector<variableInfo*>::iterator vit;
	for (vit = variables.begin(); vit != variables.end();++vit)
		delete (*vit);
	variables.clear();
}
inline int funcInfo::getFunctionSize() const
{
	if (endLine<0)
		throw std::exception(("Unable to find end of function "+name).c_str());

	if (endLine < beginLine)
		throw std::exception(("Begin line is bigger than end line in function " + name).c_str());

	return (endLine - beginLine);
}

inline int funcInfo::getFunctionScopeNesting() const
{	return (deepestBrace - beginBrace + 1); }

inline void funcInfo::setEndLine(int lineNo){endLine = lineNo;}

//////////////////////////////////////////////////////////////////////////
//increase deepest brace
//
inline void funcInfo::operator++(){++deepestBrace;}

inline void funcInfo:: increaseCyclometer(){++cyclometer;}

inline std::string funcInfo::getName() const {return name;}

inline std::string funcInfo::getFullName() const 
{
	if (className.length()>0)
		return className + "::" + name;
	
	return name;
}

inline int funcInfo::getBeginLine() const {return beginLine;}

inline int funcInfo::getBeginBrace() const {return beginBrace;}

inline int funcInfo::getDeepestBrace() const {return deepestBrace;}

inline int funcInfo::getCyclometer()const {return cyclometer;}

inline void funcInfo::addControl(controlInfo* c)
{ controls.push_back(c);}
 
inline std::vector<variableInfo*>& funcInfo::getVariableInfos()
{ return variables;}


////////////////control information//////////////////////////////

class controlInfo
{
public:
	controlInfo(const std::string& n,funcInfo* f, int bLine, int bBrace)
		:name(n), func(f), beginLine(bLine), beginBrace(bBrace)
	{	endLine = bLine;}
	~controlInfo(){}
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

////////////////variable information//////////////////////////////

class variableInfo
{
public:
	variableInfo(const std::string& n,const std::string& t,const std::string& f, int bLine)
		:name(n),type(t), beginFile(f), beginLine(bLine)
	{	referencedCount=0;}
	~variableInfo(){}
	int getControlSize() {return (endLine - beginLine);}
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