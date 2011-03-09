

#include <iostream>
#include "MetaNavigator.h"

void MetaNavigator::BeginNavigation(const std::string& fileName, const std::string folderPath)
{
	char last = folderPath.length()>0?
		folderPath[folderPath.length()-1]:'\\';
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

		RetrivePackageInfo(xml);

		navigatedFiles.insert(name);

		int size = navigatingList.size();
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
	std::cout<<"Package dependencies:"<<std::endl;
	std::string tag= "<reference>";
	std::string closeTag= "</reference>";

	xmlElem elem;
	std::string tagName = "references";
	xml.find(tagName,elem);
	if (elem.elemStr().size()<=0)return;

	xmlRep refs(elem.elemStr());

	refs.firstElem(elem);

	while(refs.nextElem(elem))
	{
		std::string refer = elem.body();
		Trim(refer);
		std::cout<<"\t"<<refer<<std::endl;
		refer = GetKeyName(refer);
		if (navigatedFiles.find(refer)==navigatedFiles.end())
			navigatingList.push(refer);
	}
}

std::string MetaNavigator::GetKeyName(std::string filePath)
{
	filePath.erase(filePath.find_last_of('.'),filePath.size());
	filePath.erase(0,filePath.find_last_of('\\')+1);
	return filePath;
}

void MetaNavigator::Trim(std::string& value)
{
	const char * ch = value.c_str();
	size_t top = 0;
	size_t end = value.size() - 1;
	while(top <= end && 
		(ch[top] ==' ' || ch [top] == '\t'))
		++top;
	while(end >=0 && (ch[end] ==' ' || ch [end] == '\t'))
		--end;

	top = (top >= value.size())?top = 0 : top;
	end  =  end<0? end = value.size() : end+1;

	value.erase(end,value.size());
	value.erase(0,top);

}


//////////////////////////////////////////////////////////////////////////
//////////////////////< test stub >///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


#ifdef TEST_META_NAVIGATOR

void main()
{

	MetaNavigator nav;

	std::string file = "MetaManager";	
	std::string fold = "MetaXML";
	std::cout<<"includes of file: " + file<<std::endl;
	std::cout<<std::string(30,'=');
	nav.BeginNavigation(file,"MetaXML");
	//std::cout<<"Can't open file: " + file;
}

#endif