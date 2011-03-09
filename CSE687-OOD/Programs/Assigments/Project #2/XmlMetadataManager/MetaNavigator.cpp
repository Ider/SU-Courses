

#include <iostream>
#include "MetaNavigator.h"

void MetaNavigator::BeginNavigation(const std::string& folderPath, const std::string& fileName)
{
	char last = folderPath[folderPath.length()-1];
	if(  last == '\\' || last == '/')
		xmlFolder = folderPath;
	else
		xmlFolder = folderPath + '\\';

	navigatingList.push(fileName);

	BeginNavigation();
}

void MetaNavigator::BeginNavigation()
{
	while(navigatingList.size()>0)
	{
		std::string name = navigatingList.front();
		navigatingList.pop();
		//if the file have been navigated, search next file
		if (navigatedFiles.find(name)!=navigatedFiles.end())
			continue;

		xmlRep xml;
		ExtractFileContent(xml.xmlStr(),name);
		if (xml.xmlStr().size()<=0)continue;
	
	}
}

void MetaNavigator::ExtractFileContent
	(std::string& container, const std::string& name)
{
	container = std::string("");

	inf.open(xmlFolder+name+".xml");
	if (!inf.good())
	{
		std::cout<<"Can't open File "<<name<<".xml"<<std::endl;
		inf.close();
		return;
	}
	
	char buffer[255];
	while(inf.good())
	{
		inf.getline(buffer,255);
		container += std::string(buffer);
	}

	inf.close();
}


void MetaNavigator::RetrivePackageInfo(xmlRep& xml)
{
	std::cout<<std::endl<<std::string(30,'-')<<std::endl;
	xmlElem pack;
	std::string tagName = "package";
	xml.find(tagName,pack);
	std::cout<<"Package "<<pack.attribExpression()<<std::endl;
	tagName = "head";
	xml.find(tagName,pack);
	std::cout<<"Head file:      "<<pack.body()<<std::endl;
	tagName = "implement";
	xml.find(tagName,pack);
	std::cout<<"Implement file: "<<pack.body()<<std::endl;

	Dependencies(xml);
}

void MetaNavigator::Dependencies(xmlRep& xml)
{
	xmlElem pack;
	std::string tagName = "references";
	xml.find(tagName,pack);
	std::string refs = pack.body();
	std::cout<<"Package dependencies:"<<std::endl;

	if (refs.size()<=0)return;
	
	//refs.replace("<reference>","\t");
}

