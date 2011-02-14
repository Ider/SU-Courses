#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "ConfigureParser.h"
#include "Parser.h"
#include "display.h"
#include <map>

typedef std::pair<std::string, packageInfo*> packPair;
typedef std::map<std::string, packageInfo*> packMap;
class fileHandler
{
public:
	fileHandler()
	{
		helper = new parserHelper();
		config = new IderConfigParseToConsole(helper);
		pParser = config->Build();

		dispayer = new display();
	}

	void attach(std::string path);
	void parse();
	void printResult();

private:
	IderConfigParseToConsole* config;
	Parser* pParser;
	parserHelper* helper;
	display* dispayer;

	packMap results;
};



#endif