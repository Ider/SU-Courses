#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "ConfigureParser.h"
#include "Parser.h"
#include "display.h"
#include "FileSystem.h"
#include <map>

typedef std::pair<std::string, packageInfo*> packPair;
typedef std::map<std::string, packageInfo*> packMap;
typedef std::map<std::string, packageInfo*>::iterator  mapIterator;
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
	~fileHandler();

	void attach(std::string path);
	void attach(int argc, char* argv[]);
	void parse();
	void printResult();

private:
	void clearResult()
	{
		if (results.size()==0)return;
		packMap::iterator it;
		for ( it=results.begin() ; it != results.end(); it++ )
			delete (it->second);
		results.clear();
	}

	std::string getFileKeyName(std::string fileName);

	bool getCommands(int argc, char* argv[]);
	void getFiles();
	void getFiles(std::string path, std::string& pattern);
	void getSubFiles(std::string path, std::string& pattern);
	IderConfigParseToConsole* config;
	Parser* pParser;
	parserHelper* helper;
	display* dispayer;

	std::vector<std::string> pattens;
	std::string rPath;
	bool needRecursion;
	packMap results;

	WinTools_Extracts::FileHandler fh;
};

inline fileHandler::~fileHandler()
{
	//delete pParser; //it has been deleted in config
	delete config;
	delete helper;
	delete dispayer;

	clearResult();
}


#endif