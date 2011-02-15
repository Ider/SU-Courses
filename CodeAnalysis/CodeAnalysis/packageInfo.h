#ifndef PACKAGE_INFO_H
#define PACKAGE_INFO_H

#include <vector>
#include <stack>
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
private:
	std::string curClass;
	int  classBeginBrace;
	funcInfo* curFunc;

	//int ctrlIndex;
	controlInfo* prePopedCtrl;
	std::stack<controlInfo*> ctrls;
};

inline void parserHelper::resetHelper()
{
	classBeginBrace = -1;
	curClass = "";
	curFunc = NULL;
	//ctrlIndex = -1;
	while (!ctrls.empty())ctrls.pop();
}

#endif 