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
		printControls(func);
	}
}

void display::printControls(funcInfo* func)
{
	std::vector<controlInfo*>& ctrls = func->controls;
	if (ctrls.size() <=0)return;

	std::cout<<"\tinformations of controls in this function:"<<std::endl;
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
