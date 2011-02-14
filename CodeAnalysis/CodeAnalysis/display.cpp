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
	for (it=funcs.begin();it!=funcs.end();++it)
	{
		funcInfo* func = (*it);
		std::string info = "Func Name:  ";
		info.append(func->getName());
		info.append("\n\t");
		std::cout << info;
		std::cout << "size:  " <<func->getFunctionSize()<<"\n\t";
		std::cout <<"scope nesting:  " << func->getFunctionScopeNesting();

		std::cout << std::endl;		
	}
}