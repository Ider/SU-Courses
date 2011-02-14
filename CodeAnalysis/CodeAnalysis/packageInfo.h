#ifndef PACKAGE_INFO_H
#define PACKAGE_INFO_H

#include <vector>
#include <string>
#include "functionInfo.h"


class packageInfo
{
public:
	//std::map<std::string,funcInfo*>& getFunctions();
	void addFunction(funcInfo* func)
	{functions.push_back(func);}
	friend class display;
	
private:
	std::vector<funcInfo*> functions;

};

//inline std::map<std::string,funcInfo*>& packageInfo::getFunctions()
//{ return functions; }


class parserHelper
{
public:
	void setCurrentClass(const std::string& className){curClass = className;}
	std::string& getCurrentClass(){return curClass;}
	void setCurrentFunction(funcInfo* func){curFunc = func;}
	funcInfo* getCurrentFunction(){return curFunc;}
	int getClassBeginBrace(){return classBeginBrace;}
	void setClassBeginBrace(int bBrace){ classBeginBrace = bBrace;}
	void resetHelper();
private:
	std::string curClass;
	int  classBeginBrace;
	funcInfo* curFunc;
};

inline void parserHelper::resetHelper()
{
	classBeginBrace = -1;
	curClass = "";
	curFunc = NULL;
}

#endif 