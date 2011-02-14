#ifndef IDER_RULES_AND_ACTIONS_H
#define IDER_RULES_AND_ACTIONS_H

#include "Parser.h"
#include "packageInfo.h"
#include <vector>


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
	void showAnalysisResult();
private:
	bool isSpecialKeyWord(const std::string& tok);
	std::string getFunctionName(ITokCollection* pTc);
	void braceBeginAction(ITokCollection* pTc);
	void braceEndAction(ITokCollection* pTc);
	std::vector<funcInfo*> funcInfos;
	funcInfo* curFuncInfo;
};



class ClassBeginRule:public IRule
{
public:
	bool doTest(ITokCollection* pTc)
	{
		if(pTc->find("struct") < pTc->length()
			|| pTc->find("class") < pTc->length())
		{
			doActions(pTc);
			return true;
		}
		return false;
	}
};

class ClassBeginAction:public IAction
{
public:
	ClassBeginAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc);
private:
	std::string& getClassName(ITokCollection* pTc);
	parserHelper* helper;
};




class ClassEndRule:public IRule
{
public:
	ClassEndRule(parserHelper* h):helper(h){}
	bool doTest(ITokCollection* pTc)
	{
		int brace = helper->getClassBeginBrace();
		if (brace > pTc->getCurrentBrace())
		{
			doActions(pTc);
			return true;
		}
		return false;
	}
private:
	parserHelper* helper;

};

class ClassEndAction:public IAction
{
public:
	ClassEndAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc)
	{
		helper->setClassBeginBrace(-1);
		helper->setCurrentClass("");
	}
private:
	parserHelper* helper;
};




class FunctionBeginRule:public IRule
{
private:
	bool isSpecialKeyWord(const std::string& tok)
	{
		const static std::string keys[]
		= { "for", "while", "switch", "if", "catch" };
		for(int i=0; i<5; ++i)
			if(tok == keys[i])
				return true;
		return false;
	}
public:
	bool doTest(ITokCollection* pTc)
	{
		ITokCollection& tc = *pTc;
		if(tc[tc.length()-1] == "{")
		{
			int len = tc.find("(");
			if(len < tc.length() && !isSpecialKeyWord(tc[len-1]))
			{
				doActions(pTc);
				return true;
			}
		}
		return false;
	}
};

class FunctionBeginAction:public IAction
{
public:
	FunctionBeginAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc);
	void setPack(packageInfo* p){pack = p;}
private:
	std::string getFuctionName(ITokCollection* pTc);
	std::string getClassName(ITokCollection* pTc);
	packageInfo* pack;
	parserHelper* helper;
};


class FuntionEndRule:public IRule
{
public:
	FuntionEndRule(parserHelper* h):helper(h){}
	bool doTest(ITokCollection* pTc)
	{
		funcInfo* func = helper->getCurrentFunction();
		if (func !=NULL)
		{	
			if(func->getBeginBrace() > pTc->getCurrentBrace())
				doActions(pTc);

			//increase deepest brace
			if((*pTc)[pTc->length()-1] == "{"
				&& func->getBeginBrace() < pTc->getCurrentBrace())
				++(*func);

			return true;
		}
		return false;
	}

private:
	parserHelper* helper;
};


class FuntionEndAction:public IAction
{
public:
	FuntionEndAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc)
	{
		funcInfo* func = helper->getCurrentFunction();
		func->setEndLine(pTc->getCurrentLine());
	}
private:
	parserHelper* helper;
};


class FunctionCyclomaticRule: public IRule
{
public:
	FunctionCyclomaticRule(){}
	bool doTest(ITokCollection* pTc)
	{
		if (contanSpecialKey(pTc))
		{
			doActions(pTc);
			return true;
		}
		return false;
	}
private:
	bool contanSpecialKey(ITokCollection* pTc)
	{
		const static std::string keys[]
		= { "for", "while", "break", "continue", "if", "catch", "goto" };
		for(int i=0; i<7; ++i)
			if(pTc->find(keys[i]) < pTc->length())
				return true;

		return false;
	}
};

class FunctionCyclomaticAction:public IAction
{
public:
	FunctionCyclomaticAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc)
	{
		funcInfo* func = helper->getCurrentFunction();
		if (func)func->increaseCyclometer();
	}
private:
	parserHelper* helper;
};

#endif