#include <iostream>
#include "display.h"


void display::printAnalysis(packageInfo* packInfo)
{
	pack = packInfo;
	printFunctions();
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
	}
}