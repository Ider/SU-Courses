#ifndef IDER_DISPLAY_H
#define IDER_DISPLAY_H

#include "packageInfo.h"

class display
{
public:
	display():optimalFuncSize(50),optimalCtrlSpan(20)
		,optimalCyclom(10),optimalReference(10),optimalLocality(20){}
	void printAnalysis(packageInfo* package);

private:
	void printPackageInfo();
	void printFunctions();
	void printControls(std::vector<controlInfo*>& ctrls);
	void printVaraibels(std::vector<variableInfo*>& vInfos);
	packageInfo* pack;

	const int optimalFuncSize;
	const int optimalReference;
	const int optimalCyclom;
	const int optimalCtrlSpan;
	const int optimalLocality;
};


#endif

