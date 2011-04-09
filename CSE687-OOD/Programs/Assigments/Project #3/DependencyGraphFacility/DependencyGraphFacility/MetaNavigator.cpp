/////////////////////////////////////////////////////////////////////////
//  MetaNavigator.cpp  -  Navigate metadata xml files and print file info//
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


#include "MetaNavigator.h"
#include "Vertex.h"
#include <list>


//////////////////////////////////////////////////////////////////////////
//Navigate the xml file named fileName under folderPath
void MetaNavigator::BeginNavigation(const std::string& filePath)
{
	//Get package xml data
	xmlRep xml;
	ExtractFileContent(xml.xmlStr(),filePath);
	if (xml.xmlStr().size()<=0)return;

	std::list<std::string> deps;
	Dependencies(xml,deps);

	GenerateEdges(filePath,deps);
}

//////////////////////////////////////////////////////////////////////////
//Extract xml file content to container
void MetaNavigator::ExtractFileContent
	(std::string& container, const std::string& filePath)
{
	container.clear();

	inf.open(filePath);
	if (!inf.good())
	{
		std::cout<<"Can't open File "<<filePath<<".xml"<<std::endl;
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

//////////////////////////////////////////////////////////////////////////
//Retrieve the dependencies from xml file and print it
void MetaNavigator::Dependencies(xmlRep& xml,std::list<std::string>& deps)
{
	xmlElem elem;
	std::string tagName = "references";
	xml.find(tagName,elem);
	if (elem.elemStr().size()<=0)return;

	xmlRep refs(elem.elemStr());

	//skip <references> tag
	refs.firstElem(elem);

	while(refs.nextElem(elem))
	{
		std::string refer = elem.body();
		Trim(refer);
		refer = GetKeyName(refer);
		deps.push_back(refer);
	}
}

//////////////////////////////////////////////////////////////////////////
//Generate Edges base on the dependencies and and them to Graph
void MetaNavigator::GenerateEdges(std::string filePath,std::list<std::string>& deps)
{
	if (deps.size()<=0)return;

	typedef std::vector<std::pair<std::string, std::string>> Vector;
	typedef std::pair<std::string, std::string> Pair;

	std::string name = GetKeyName(filePath);
	size_t pos = filePath.find_last_of('\\');
	if (pos < filePath.size()-1)
		filePath.erase(pos+1,filePath.size());

	Vector edges;
	std::list<std::string>::iterator it; 
	for( it= deps.begin();it!=deps.end(); ++it)
		edges.push_back(Pair((*it),filePath+(*it)));

	graph.AddEdge(name,edges);
}

//////////////////////////////////////////////////////////////////////////
//Remove the path and file extension, return the pure file name
std::string MetaNavigator::GetKeyName(std::string filePath)
{
	//remove path
	//If filePath.find_last_of('\\') failed, it return std::string::npos
	//npos + 1 equals to 0, so nothing erased
	filePath.erase(0,filePath.find_last_of('\\')+1);
	//remove extension
	size_t pos = filePath.find_last_of('.');
	if (pos < filePath.size())
		filePath.erase(pos,filePath.size());
	return filePath;
}

//////////////////////////////////////////////////////////////////////////
//Removes all occurrences of white space characters from the beginning and 
//end of string. 
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

	IMetaNavigator*  nav = new MetaNavigator();

	std::string file = "MetaManager";	
	std::string fold = "MetaXML";
	std::cout<<"includes of file: " + file<<std::endl;
	std::cout<<std::string(50,'=');
	nav->BeginNavigation(file,"MetaXML");
	//std::cout<<"Can't open file: " + file;
	delete nav;
}

#endif