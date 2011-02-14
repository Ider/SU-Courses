#include "fileHandler.h"



void fileHandler::attach(std::string path)
{
	packageInfo* pack = new packageInfo();
	results[path] = pack;
}

void fileHandler::parse()
{
	packMap::iterator it;
	for (it = results.begin(); it != results.end(); ++it)
	{
		config->Attach(it->first,it->second);
		while (pParser->next())
			pParser->parse();
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