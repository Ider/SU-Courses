#ifndef META_NAVIGATOR_H
#define META_NAVIGATOR_H


#include <string>
#include <fstream>
#include <queue>
#include <set>

#include "xmlTran.h"

class IMetaNavigator
{
public:
	virtual void BeginNavigation(const std::string& folderPath,const std::string& fileName)=0;
	~IMetaNavigator(){}
};

class MetaNavigator: public IMetaNavigator
{
public:
	virtual void BeginNavigation
		(const std::string& folderPath, const std::string& fileName);
private:
	void BeginNavigation();
	void ExtractFileContent
		(std::string& containerconst, const std::string& name);
	void RetrivePackageInfo(xmlRep& xml);
	void Dependencies(xmlRep& xml);
	std::string xmlFolder;
	std::ifstream inf;
	std::set<std::string> navigatedFiles; //the files that has already been navigated
	std::queue<std::string> navigatingList;//the files that to be navigated.
};

#endif