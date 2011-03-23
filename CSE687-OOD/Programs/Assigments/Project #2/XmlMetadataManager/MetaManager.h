#ifndef META_MANAGER_H
#define META_MANAGER_H

#include <iostream>
#include <fstream>
#include <map>
#include <direct.h>

#include "IIncludes.h"
#include "MetaGenerator.h"
#include "MetaNavigator.h"
#include "PackageInfo.h"
#include "Includes.h"


class MetaManager
{
public:
	//MetaManager():inc(0),gen(0),inStream(0),xmlFolder("MetaXML"){}
	MetaManager(std::ostream* oS= (new std::ofstream())
		, std::istream* iS = (new std::ifstream()));
	~MetaManager();
	void Build(int argc, char** argv);
	void CreateMetaXML();
	void NavigateMetaXML(const std::string xmlName);
	std::string XmlFolder(){return xmlFolder;}
private:
	//void Build();
	void OpenOutStream(std::string& name);
	void CloseOutStream();
	IInclude* inc;
	IMetaGenerator* gen;
	IMetaNavigator* nav;
	std::istream* inStream;
	std::ostream* outStream;
	PackagesGenerator packMaker;
	PackMap results;
	const std::string xmlFolder;
};


inline MetaManager::MetaManager(std::ostream* oS, std::istream* iS)
:outStream(oS),inStream(iS),xmlFolder("MetaXML\\")
{
	inc = new Includes(inStream);
	gen = new MetaGenerator(inc);
	nav = new MetaNavigator();
	packMaker.SetResultContainer(results);
	
	_mkdir(xmlFolder.c_str());
}

#endif