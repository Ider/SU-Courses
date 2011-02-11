#ifndef IDER_RULES_AND_ACTIONS_H
#define IDER_RULES_AND_ACTIONS_H

#include "Parser.h"
#include "functionInfo.h"



//////////////////////////////////////////////////////////////////////////
// Rule for function analysis
//
// whenever the last token in collection is "{" or "}",do actions,
// as they are scope separator.
class FunctionAnalysisRule:public IRule
{
public:
	bool doTest(ITokCollection* pTc)
	{
		std::string& endWith = (*pTc)[pTc->length()-1];
		if (endWith == "{" || endWith == "}")
		{
			doActions(pTc);
			return true;
		}

		return false;
	}
};

//////////////////////////////////////////////////////////////////////////
// Action for function analysis
//
class FunctionAnalysisAction:public IAction
{
public:
	FunctionAnalysisAction(){ curFuncInfo=NULL;}
	void doAction(ITokCollection* pTc);
	//void printAnalysisResult();
private:
	bool isSpecialKeyWord(const std::string& tok);
    std::string getFunctionName(ITokCollection* pTc);
	void braceBeginAction(ITokCollection* pTc);
	void braceEndAction(ITokCollection* pTc);
	std::vector<funcInfo*> funcInfos;
	funcInfo* curFuncInfo;
};


#endif