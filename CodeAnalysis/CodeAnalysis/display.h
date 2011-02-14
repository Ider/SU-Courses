#ifndef IDER_DISPLAY_H
#define IDER_DISPLAY_H

#include "packageInfo.h"

class display
{
public:
	void printAnalysis(packageInfo* package);

private:
	void printFunctions();
	packageInfo* pack;
};


#endif

