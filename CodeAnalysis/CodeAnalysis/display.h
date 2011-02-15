#ifndef IDER_DISPLAY_H
#define IDER_DISPLAY_H

#include "packageInfo.h"

class display
{
public:
	//display(){}
	void printAnalysis(packageInfo* package);

private:
	void printFunctions();
	void printControls(funcInfo* func);
	packageInfo* pack;
};


#endif

