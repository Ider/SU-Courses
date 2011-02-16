#include "fileHandler.h"

void fileHandler::attach(std::string path)
{
	clearResult();
	packageInfo* pack = new packageInfo();
	pack->addFileName(path);
	results[path] = pack;
}

void fileHandler::attach(int argc, char* argv[])
{

	if (!getCommands(argc,argv))
	{
		std::cout<<"The command line is not formated.\n";
		std::cout<<"Please enter command line as:\n";
		std::cout<<"[path] [pattern](*.*){0,2} (/r)?:\n";
		return;
	}

	clearResult();
	getFiles();
	if (results.size() == 0)
	std::cout<<"\n\nNo file found!!!\n";
}


void fileHandler::parse()
{
	packMap::iterator it;
	for (it = results.begin(); it != results.end(); ++it)
	{
		packageInfo& p = *(it->second);
		for (int i = 0; i<p.fileCount(); ++i)
		{
			config->Attach(p[i], &p);
			while (pParser->next())
				pParser->parse();
		}
		
		
	}
}

void fileHandler::printResult()
{
	packMap::iterator it;
	for (it = results.begin(); it != results.end(); ++it)
	{
		dispayer->printAnalysis(it->second);
	}
}

bool fileHandler::getCommands(int argc, char* argv[])
{
	bool h = false;
	bool cpp = false;
	if (argc <2)return false;
	pattens.clear();

	rPath =fh.getFullPath(argv[1]);
	needRecursion = !strcmp(argv[argc-1],"/r");

	for (int i=2; i<argc; ++i)
	{
		if (!h && !strcmp(argv[i],"*.h"))h = true;
		if (!cpp&&  !strcmp(argv[i],"*.cpp"))cpp = true;
	}

	if (h)pattens.push_back("*.h");
	if (cpp)pattens.push_back("*.cpp");
	if (!pattens.size())
	{
		pattens.push_back("*.h");
		pattens.push_back("*.cpp");
	}
	return true;
}

void fileHandler::getFiles()
{
	for (int i = 0; i<pattens.size();++i)
		getFiles(rPath,pattens[i]);
}

void fileHandler::getFiles(std::string path, std::string& pattern)
{
 	std::vector<std::string> files = fh.getFileSpecs(path,pattern);
	std::string key;
	mapIterator it;
	packageInfo* pack;
	for (int i=0; i<files.size();i++)
	{
		key = getFileKeyName(files[i]);
		it = results.find(key);
		if (it == results.end())
		{
			pack = new packageInfo();
			pack->addFileName(files[i]);
			results[key] = pack;
		}
		else
		{
			it->second->addFileName(files[i]);
		}
	}

	if (needRecursion)getSubFiles(path,pattern);
}

void fileHandler::getSubFiles(std::string path, std::string& pattern)
{
	std::string temp = path;
	if (temp[temp.size()-1]!='\\'&&temp[temp.size()-1]!='/')
		temp+="\\";

	std::vector<std::string> currdirs = fh.getDirectories(temp+"*");
	for(size_t i=0; i<currdirs.size(); ++i)
	{
		if (currdirs[i][0] == '.')continue;
		getFiles(temp+currdirs[i],pattern);
	}

}


//////////////////////////////////////////////////////////////////////////
//remove file extension
std::string fileHandler::getFileKeyName(std::string fileName)
{
	int dot = fileName.size()-1;
	while (dot >=0 && fileName[dot]!='.' && fileName[dot]!='\\')--dot;
	if (dot >=0 && fileName[dot] == '.')
		fileName.erase(dot,fileName.size());
	return fileName;
}




#ifdef TEST_FILEHANDLER

#include <queue>
#include <string>

int main(int argc, char* argv[])
{
	std::cout << "\n  Testing ConfigureParser module\n "
		<< std::string(32,'=') << std::endl;

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

		//ConfigParseToConsole configure;
		//Parser* pParser = configure.Build();

		fileHandler handler;

		try
		{
// 			if(pParser)
// 			{
// 				if(!configure.Attach(argv[i]))
// 				{
// 					std::cout << "\n  could not open file " << argv[i] << std::endl;
// 					continue;
// 				}
// 			}
// 			else
// 			{
// 				std::cout << "\n\n  Parser not built\n\n";
// 				return 1;
// 			}
// 			// now that parser is built, use it
// 
// 			while(pParser->next())
// 				pParser->parse();
// 			std::cout << "\n\n";

			handler.attach(argv[i]);
			handler.parse();
			handler.printResult();
		}
		catch(std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}
	}
}

#endif