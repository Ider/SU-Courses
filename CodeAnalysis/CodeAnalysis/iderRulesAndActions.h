#ifndef IDER_RULES_AND_ACTIONS_H
#define IDER_RULES_AND_ACTIONS_H

#include "Parser.h"
#include "packageInfo.h"
#include <vector>
#include <list>


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


////////////////Class Rules And Actions///////////////////////////////

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


////////////////Function Rules And Actions///////////////////////////////


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


////////////////Function Cyclomatic Rules And Actions///////////////////////////////


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


////////////////Control Span Rules And Actions///////////////////////////////

//////////////////////////////////////////////////////////////////////////
//the control span rule and action for "for"
//is not 100% correct, when it has no braces

class CtrlSpanBeginRule:public IRule
{
public:
	CtrlSpanBeginRule(parserHelper* h):helper(h){}
	bool doTest(ITokCollection* pTc)
	{
		ITokCollection& tc = *pTc;
		int i = -1;
		while (++i < tc.length() && tc[i]=="\n");
		if (i >=tc.length()) return false;

		std::string& str = tc[i]; 
		if (isControl(str))
		{
			//ignore the controls that have no braces
			if (str != "for" && tc[tc.length()-1]==";")
				return false;

			doActions(pTc);
			return true;
		}
		return false;
	}
private:
	bool isControl(const std::string& str)
	{
		const static std::string ctrls[]
		= { "if", "while", "for", "switch", "do", "else"};
		for(int i=0; i<6; ++i)
			if(str == ctrls[i])
				return true;
		return false;
	}
	parserHelper* helper;
};

class CtrlSpanBeginAction: public IAction
{
public:
	CtrlSpanBeginAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc)
	{
		ITokCollection& tc = *pTc;
		funcInfo* func=helper->getCurrentFunction();
		int i = -1;
		while (++i < tc.length() && tc[i]=="\n");
		std::string& name = tc[i];

		if (name=="else")
		{
			doElseCtrlAction();
			return;
		}
		int brace = pTc->getCurrentBrace();
		if (name=="for")++brace;
		controlInfo* ctrl = new controlInfo(name,func
			,pTc->getCurrentLine()
			,brace);
		func->addControl(ctrl);
		helper->pushControl(ctrl);
	}
private: 
	void doElseCtrlAction()
	{
		controlInfo* pre = helper->getPrePopedControl();
		if (pre != NULL && pre->getName() =="if")
			helper->pushControl(pre);
	}
	parserHelper* helper;
};




class CtrlSpanEndRule:public IRule
{
public:
	CtrlSpanEndRule(parserHelper* h):helper(h){}
	bool doTest(ITokCollection* pTc)
	{
		ITokCollection& tc = *pTc;
		if (tc[tc.length()-1] != "}")return false;

		controlInfo* ctrl=helper->topControl();
		if (ctrl == NULL)return false;

		int brace =  ctrl->getBeginBrace();
		if (brace >pTc->getCurrentBrace())
		{
			doActions(pTc);
			return true;
		}
		return false;
	}

private:
	parserHelper* helper;
};


class CtrlSpanEndAction:public IAction
{
public:
	CtrlSpanEndAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc)
	{
		controlInfo* ctrl = helper->popControl();
		ctrl->setEndLine(pTc->getCurrentLine());
	}
private:
	parserHelper* helper;
};

//////////////Variable Rules and Actions///////////////////////////////////////////////////

class VariableRuleBase:public IRule
{
public:
	VariableRuleBase(parserHelper* h):helper(h){}

	virtual bool doTest(ITokCollection* pTc)=0;
protected:
	std::list<std::string> toks;
	parserHelper* helper;

	void copyTokens(ITokCollection* pTc)
	{
		toks.clear();
		for (int i = 0; i<pTc->length(); ++i)
			if ((*pTc)[i]!="\n")
				toks.push_back((*pTc)[i]);
	}

	//find first position that match tok
	int find(std::string tok)
	{
		int i=0;
		std::list<std::string>::iterator sit;

		for(sit = toks.begin(); sit!= toks.end(); ++i, ++sit)
			if(tok == *sit)
				return i;

		return toks.size();
	}

	//find last position that match tok
	int rfind(std::string tok)
	{
		int i=toks.size(); 
		std::list<std::string>::iterator sit = toks.end();
		while(i>0)
		{
			--i, --sit;
			if(tok == (*sit))return i;
		}

		return toks.size();
	}

	void erase(int position){erase(position,position+1);}

	//erase elements [from, to) in container
	void erase(int from, int to)
	{
		if (from > to) to^=from^=to^=from;
		std::list<std::string>::iterator fit;
		std::list<std::string>::iterator tit;
		fit = tit = toks.begin();
		advance(fit,from);
		advance(tit,to);
		toks.erase(fit,tit);
	}
};


//////////////////////////////////////////////////////////////////////////
//this rule only catch function scope variables
//all globe/class variables will be ignored
class VariableDeclarationRule:public VariableRuleBase
{
public:
	VariableDeclarationRule(parserHelper* h):VariableRuleBase(h){}
	bool doTest(ITokCollection* pTc)
	{
		if (pTc->getCurrentLine()==28)
		{
			pTc=pTc;
		}
		if (helper->getCurrentFunction()==NULL)
			return false;
		if (hasDeclaration(pTc))
		{
			helper->setVariable(toks.back(),toks.front());
			doActions(pTc);
			return true;
		}
		return false;
	}
private:
	bool hasDeclaration(ITokCollection* pTc)
	{
		if ((*pTc)[pTc->length()-1] != ";")
			return false;

		copyTokens(pTc);
		eraseUselessInfo();
		if (toks.size()== 2 && !isSpecialKey())
			return true;

		return false;
	}
	void eraseUselessInfo()
	{
		toks.pop_back();//erase ";"
		if (toks.size() <= 2) return;
		int index = find("=");
		if (index != toks.size())
			erase(index,toks.size());

		toks.remove("*");
		toks.remove("&");

		if (toks.size() <= 2) return;
		index = rfind("::");
		if (index != toks.size())
		{
			erase(0,index+1);
		}
		else eraseModifier();
	}
	void eraseModifier()
	{
		const std::string mods[]=
		{"volatile", "auto", "const", "static"};
		for (int i = 0; i<4; ++i)
			toks.remove(mods[i]);
	}
	bool isSpecialKey()
	{
		std::string& type =	toks.front();
		if (type == "return" || type == "delete" || type =="new")
			return true;
		return false;
	}
};

class VariableDeclarationAction:public IAction
{
public:
	VariableDeclarationAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc)
	{
		variableInfo* v=new variableInfo(helper->getVariableName()
			,helper->getVariableType()
			,helper->getFileName()
			,pTc->getCurrentLine());
		helper->getCurrentFunction()->getVariableInfos().push_back(v);
		helper->setVariable("","");
	}
private:
	parserHelper* helper;
};




class VariableReferenceRule:public VariableRuleBase
{
public:
	VariableReferenceRule(parserHelper* h):VariableRuleBase(h){}

	bool doTest(ITokCollection* pTc)
	{
		funcInfo* func = helper->getCurrentFunction();
		if (func == NULL 
			|| func->getVariableInfos().size() ==0)
			return false;

		copyTokens(pTc);
		return checkVariable(pTc);
	}
private:
	bool checkVariable(ITokCollection* pTc)
	{
		bool referenced = false;
		std::vector<variableInfo*>& vInfos 
			= helper->getCurrentFunction()->getVariableInfos();
		std::list<std::string>::iterator it = toks.begin();

		while (it != toks.end())
		{
			size_t i;
			for (i=0; i< vInfos.size(); ++i)
			{
				if ((*it)==vInfos[i]->getName())
				{
					helper->setReferecedVariable(vInfos[i]);
					doActions(pTc);
					referenced = true;
					break;
				}
			}
			if (i<vInfos.size())
				it=toks.erase(it);
			else ++it;
		}
		return referenced;
	}
};

class VariableReferenceAction: public IAction
{
public:
	VariableReferenceAction(parserHelper* h):helper(h){}
	void doAction(ITokCollection* pTc)
	{
		variableInfo* vInfo = helper->getReferecedVariable();
		vInfo->setEndLine(pTc->getCurrentLine(),helper->getFileName());
		++(*vInfo);
	}
private:
	parserHelper* helper;
};


#endif