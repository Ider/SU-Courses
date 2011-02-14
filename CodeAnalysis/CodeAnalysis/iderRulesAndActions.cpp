#include "iderRulesAndActions.h"
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
	std::cout << std::endl;		
	for (it=funcInfos.begin();it!=funcInfos.end();++it)
	{
		std::string info = "Func Name:  ";
		info.append((*it)->getName());
		info.append("\n\t");
		std::cout << info;
		std::cout << "size:  " <<(*it)->getFunctionSize()<<"\n\t";
		std::cout <<"scope nesting:  " << (*it)->getFunctionScopeNesting();

		std::cout << std::endl;		
	}
}

//////////////////End FunctionAnalysisAction/////////////////////////////////


////////////////////ClassBeginAction///////////////////////////

std::string& ClassBeginAction::getClassName(ITokCollection* pTc)
{
	 ITokCollection& tc = *pTc;
	int len = tc.find("class");
	if (len >= tc.length())len = tc.find("struct");
	return tc[len+1];
}

void ClassBeginAction::doAction(ITokCollection* pTc)
{
	std::string& name = getClassName(pTc);
	helper->setCurrentClass(name);
	helper->setClassBeginBrace(pTc->getCurrentBrace());
}


////////////////////End ClassBeginAction///////////////////////////



std::string FunctionBeginAction::getFuctionName(ITokCollection* pTc)
{
	ITokCollection& tc = *pTc;
	int len = tc.find("(") - 1;
	if (tc[len-1] == "::~")
		return "~" + tc[len];
	return tc[len];
}

std::string FunctionBeginAction::getClassName(ITokCollection* pTc)
{
	std::string& name = helper->getCurrentClass();	
	if (name.length()>0)return name;

	ITokCollection& tc = *pTc;
	int len = tc.find("(") - 2;
	if (tc[len] == "::" || tc[len] == "::~")
		return tc[len-1];

	return "";
}

void FunctionBeginAction::doAction(ITokCollection* pTc)
{
	std::string fName = getFuctionName(pTc);
	std::string cName = getClassName(pTc);
	funcInfo* func = new funcInfo(cName,fName
			,pTc->getCurrentLine()
			,pTc->getCurrentBrace());
	pack->addFunction(func);
	helper->setCurrentFunction(func);
}

//
//----< test stub >--------------------------------------------



#ifdef TEST_PARSER2

#include <queue>
#include <string>
#include "ConfigureParser.h"


int main(int argc, char* argv[])
{
	std::cout << "\n  Testing Parser class\n "
		<< std::string(22,'=') << std::endl;

	// collecting tokens from files, named on the command line

	if(argc < 2)
	{
		std::cout 
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}

	for(int i=1; i<argc; ++i)
	{
		std::cout << "\n  Processing file " << argv[i];
		std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-');

		IderConfigParseToConsole configure;
		Parser* pParser = configure.Build();
		try
		{
			if(pParser)
			{
				if(!configure.Attach(argv[i]))
				{
					std::cout << "\n  could not open file " << argv[i] << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return 1;
			}
			// now that parser is built, use it

			while(pParser->next())
				pParser->parse();
			pParser->showParseResult();
			std::cout << "\n\n";
		}
		catch(std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}

		//
		std::cout << "\n  Processing file for Queued Outputs " << argv[i];
		std::cout << "\n  " << std::string(35 + strlen(argv[i]),'-');

		ConfigParseToQueue Qconfigure;
		pParser = Qconfigure.Build();
		try
		{
			if(pParser)
			{
				if(!Qconfigure.Attach(argv[i]))
				{
					std::cout << "\n  could not open file " << argv[i] << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return 1;
			}
			// now that parser is built, use it

			while(pParser->next())
				pParser->parse();
			std::cout << "\n\n";
		}
		catch(std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}
		std::queue<std::string>* pQueue = Qconfigure.GetQueue();
		size_t len = pQueue->size();
		for(size_t i=0; i<len; ++i)
		{
			std::cout << "\n  " << pQueue->front();
			pQueue->pop();
		}
		std::cout << "\n\n";
	}
}

#endif