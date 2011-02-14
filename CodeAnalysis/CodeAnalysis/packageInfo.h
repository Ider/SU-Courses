#ifndef PACKAGE_INFO_H
#define PACKAGE_INFO_H

#include <map>
#include <string>
#include "functionInfo.h"


class packageInfo
{
public:
	funcInfo* getFunction(const std::string& funcName);
	funcInfo* getFunction(const std::string& cName,const std::string& fName);
	//std::map<std::string,funcInfo*>& getFunctions();
	bool addFunction(funcInfo* func);
	friend class display;
	
private:
	std::map<std::string,funcInfo*> functions;

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