#include <iostream>
#include "display.h"


void display::printAnalysis(packageInfo* packInfo)
{
	pack = packInfo;
	printPackageInfo();
	printFunctions();
}

void display::printPackageInfo()
{
	std::cout<<"Package: ";
	for (int i = 0; i< pack->fileCount(); ++i)
	{
		std::cout<<"\n"<< (*pack)[i];
	}
	std::cout<<std::endl;
}

void display::printFunctions()
{
	std::vector<funcInfo*>& funcs = pack->functions;
	std::vector<funcInfo*>::iterator it;
	std::cout << std::endl;	
	for (it=funcs.begin();it!=funcs.end();++it)
	{
		funcInfo* func = (*it);
		std::string info = "Func Name:  ";
		info.append(func->getFullName());
		info.append("\n\t");
		std::cout << info;
		std::cout << "size:  " <<func->getFunctionSize()<<"\n\t";
		std::cout <<"scope nesting:  " << func->getFunctionScopeNesting()<<"\n\t";
		std::cout <<"cyclomatic complexity:  "<<func->cyclometer<<"\n\t";

		std::cout << std::endl;	
		printControls(func->controls);
		printVaraibels(func->variables);
	}
}

void display::printControls(std::vector<controlInfo*>& ctrls)
{
	if (ctrls.size() <=0)return;

	std::cout<<"\n\tinformations of controls in this function:"<<std::endl;
	std::vector<controlInfo*>::iterator it;
	std::cout<<"\tname:\t\t\tline@\t\t\tbreath"<<std::endl;;
	std::cout<<std::string(70,'-')<<std::endl;
	for (it = ctrls.begin(); it != ctrls.end(); ++it)
	{
		controlInfo& ctrl = *(*it);
		std::cout<<"\t"<<ctrl.getName();
		std::cout<<"\t\t\t"<<ctrl.getBeginLine();
		std::cout<<"\t\t\t"<<ctrl.getControlSize()<<std::endl;
	}
}

void display::printVaraibels(std::vector<variableInfo*>& vInfos)
{
	if (vInfos.size() <=0)return;

	std::cout<<"\n\tinformations of variables in this function:"<<std::endl;
	std::vector<variableInfo*>::iterator it;
	std::cout<<"\tname\t\ttype\t\tline@\t\tref#"<<std::endl;;
	std::cout<<std::string(70,'-')<<std::endl;
	for (it = vInfos.begin(); it != vInfos.end(); ++it)
	{
		variableInfo& var = *(*it);
		std::cout<<"\t"<<var.getName();
		std::cout<<"\t\t"<<var.getType();
		std::cout<<"\t\t"<<var.getBeginLine();
		std::cout<<"\t\t"<<var.getReferencedCount()<<std::endl;
	}
}


#ifdef DISPLAY_TEST

#include "fileHandler.h"

int main(int argc, char* argv[])
{
	std::cout << "\n  Testing Display module\n "
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
			int count = 5;
			char* parameter[] = {" ","..","*.h","*.cpp", "/r"};
			handler.attach(count,parameter);
			handler.parse();
			handler.printResult();
		}
		catch(std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}
	}

	getchar();
}


#endif