#ifndef IDER_CONFIGUREPARSER_H
#define IDER_CONFIGUREPARSER_H

#include "Parser.h"
#include "SemiExpression.h"
#include "Tokenizer.h"
#include "ActionsAndRules.h"
#include "iderRulesAndActions.h"

/*
///////////////////////////////////////////////////////////////
// build parser that writes its output to console
// used by student Ider Zheng
class IderConfigParseToConsole : IBuilder
{
public:
	IderConfigParseToConsole();
	~IderConfigParseToConsole();
	bool Attach(const std::string& name, bool isFile=true);
	Parser* Build();

private:
	// Builder must hold onto all the pieces

	Toker* pToker;
	SemiExp* pSemi;
	Parser* pParser;

	// and the the Rules and Actions as well

	PreprocStatement* pPreprocStatement;
	PrintPreproc* pPrintPreproc;
	FunctionDefinition* pFunctionDefinition;
	PrintFunction* pPrintFunction;
	PrettyPrintFunction* pPrettyPrintFunction;

	// prohibit copies and assignments

	IderConfigParseToConsole(const IderConfigParseToConsole&);
	IderConfigParseToConsole& operator=(const IderConfigParseToConsole&);
};
*/


#endif
