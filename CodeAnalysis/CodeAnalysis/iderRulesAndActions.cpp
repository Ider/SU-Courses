#include "iderRulesandActions.h"
// #include "iderActions.h"
// 
// iderIRule::endWith iderIRule::collectionEndWith(ITokCollection* pTc)
// {
// 	std::string& last = (*pTc)[pTc->length()-1];
// 	//std::string& last = pTc->operator[](pTc->length()-1);
// 	if (last == ";")return semicolon;
// 	if (last == "{")return leftBrace;
// 	if (last == "}")return rightBrace;
// 	if (last == "\n")return newline;
// }
// 
// bool iderIRule::isFunctionBegin(ITokCollection* pTc)
// {
// 	if (collectionEndWith(pTc) == leftBrace)
// 	{
// 		int len = pTc->find("(");
// 		if(len < pTc->length() && !isSpecialKeyWord((*pTc)[len-1]))
// 		{
// 			doActions(pTc);
// 			return true;
// 		}
// 	}
// }
// 
// bool iderIRule::isSpecialKeyWord(const std::string& tok)
// {
// 	const static std::string keys[]
// 	= { "for", "while", "switch", "if", "catch" };
// 	for(int i=0; i<5; ++i)
// 		if(tok == keys[i])
// 			return true;
// 	return false;
// }
// 
// 
// 
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
	if (pTc->getCurrentBrace()<curFuncInfo->getBeginBrace())
	{
		curFuncInfo->setEndLine(pTc->getCurrentLine());
		curFuncInfo=NULL;
	}
}
