#include "iderRulesandActions.h"
#include <iostream>
////////////////// FunctionAnalysisAction/////////////////////////////////

bool FunctionAnalysisAction::isSpecialKeyWord(const std::string& tok)
{
	const static std::string keys[]
	= { "for", "while", "switch", "if", "catch" };
	for(int i=0; i<5; ++i)
		if(tok == keys[i])
			return true;
	return false;
}

std::string FunctionAnalysisAction::getFunctionName(ITokCollection* pTc)
{
	int len = pTc->find("(");
	if(len < pTc->length())
	{
		std::string& funcName =(*pTc)[len-1];
		if (!isSpecialKeyWord(funcName))
			return funcName;
	}

	return "";
}

void FunctionAnalysisAction::doAction(ITokCollection* pTc)
{
	if (pTc == NULL)
	{
		showAnalysisResult();
		return;
	}

	std::string& endWith = (*pTc)[pTc->length()-1];
	if (endWith == "{")
		braceBeginAction(pTc);
	else if (endWith == "}")
		braceEndAction(pTc);
}

void FunctionAnalysisAction::braceBeginAction(ITokCollection* pTc)
{
	std::string funcName = getFunctionName(pTc);
	int lineNo=pTc->getCurrentLine();
	int braceNo=pTc->getCurrentBrace();

	//when "{" is found, and collection get a function name
	//create a funcInfo object to record this function informations
	if (funcName != "")
	{
		curFuncInfo = new funcInfo(funcName,lineNo,braceNo);
		funcInfos.push_back(curFuncInfo);
	} 
	else
	{
		//if curFuncInfo is not NULL, it means the tokens are still inside of function;
		//if current brace No. is bigger than current function deepest brace No.,
		//increase it.
		if (curFuncInfo != NULL 
			&& braceNo > curFuncInfo->getDeepestBrace())
			++(*curFuncInfo);
	}
}

void FunctionAnalysisAction::braceEndAction(ITokCollection* pTc)
{
	if (curFuncInfo == NULL )return;
	//When current brace No. is less than function begin brace No.,
	//it means token is out of function,
	//so information collection for this function is done
	if (pTc->getCurrentBrace() < curFuncInfo->getBeginBrace())
	{
		curFuncInfo->setEndLine(pTc->getCurrentLine());
		curFuncInfo=NULL;
	}
}

void FunctionAnalysisAction::showAnalysisResult()
{
	std::vector<funcInfo*>::iterator it;
	for (it=funcInfos.begin();it!=funcInfos.end();++it)
	{
		std::string info = "Func Name:";
		info.append((*it)->getName());
		info.append("\n");
		info.append("\t\t");
		info.append("size:"+(*it)->getFunctionSize());
	//	info.append("scope nesting:"+(*it)->getFunctionScopeNesting());

		std::cout << info << std::endl;		
	}
}

//////////////////End FunctionAnalysisAction/////////////////////////////////




//
//----< test stub >--------------------------------------------