#ifndef FUNCTION_INFO_H
#define FUNCTION_INFO_H

#include <string>

class funcInfo
{
public:
	funcInfo(std::string funcName, int bLine,int bBrace);
	funcInfo(std::string cName, std::string fName, int bLine,int bBrace);
	int getFunctionSize() const;
	int getFunctionScopeNesting() const;
	void setEndLine(int lineNo);
	void operator++();
	std::string getName() const;
	int getBeginLine() const;
	int getBeginBrace() const;
	int getDeepestBrace() const;
private:
	const std::string className;
	const std::string name;
	const int beginLine;
	int endLine;
	const int beginBrace;
	int deepestBrace;
};

inline funcInfo::funcInfo(std::string funcName, int bLine,int bBrace)
	:name(funcName),beginLine(bLine),beginBrace(bBrace)
{
	endLine = -1;
	deepestBrace = bBrace;
}

inline funcInfo::funcInfo(std::string cName, std::string fName, int bLine,int bBrace)
	:className(cName),name(fName),beginLine(bLine),beginBrace(bBrace)
{
	endLine = -1;
	deepestBrace = bBrace;
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

inline void funcInfo::operator++(){++deepestBrace;}

inline std::string funcInfo::getName() const {return name;}

inline int funcInfo::getBeginLine() const {return beginLine;}

inline int funcInfo::getBeginBrace() const {return beginBrace;}

inline int funcInfo::getDeepestBrace() const {return deepestBrace;}

#endif