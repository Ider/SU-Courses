/////////////////////////////////////////////////////////////////////////
//  MetaGenerator.h    -  facility to generator metadata xml files     //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////

#include "MetaGenerator.h"


//////////////////////////////////////////////////////////////////////////
//Get Metadata according from a file that given by the filepath
std::string MetaGenerator::GetMetadata(std::string& filePath)
{
	Clear();

	GeneratePackInfo(filePath);
	GenerateReferences(filePath);

	return CombineMetaElements(GetKeyName(filePath));
}

//////////////////////////////////////////////////////////////////////////
//Get MetaData for a package,retrieve all local reference from the files 
//that PackageInfo contains
std::string MetaGenerator::GetMetadata(PackageInfo& pack)
{
	Clear();

	for (size_t i =0; i<pack.fileCount(); ++i)
	{
		GeneratePackInfo(pack[i]);
		GenerateReferences(pack[i]);
	}

	return CombineMetaElements(pack.Name());
}

//////////////////////////////////////////////////////////////////////////
//Remove the path and file extension, return the pure file name
std::string MetaGenerator::GetKeyName(std::string filePath)
{
	filePath.erase(filePath.find_last_of('.'),filePath.size());
	filePath.erase(0,filePath.find_last_of('\\')+1);
	return filePath;
}

//////////////////////////////////////////////////////////////////////////
//flush all private xml data
void MetaGenerator::Clear()
{
	meta.flush();
	references.flush();
	packInfo.flush();
}

//////////////////////////////////////////////////////////////////////////
//Generate the basic package information tag
std::string MetaGenerator::GeneratePackInfo(std::string& filePath)
{
	std::string tag;
	if(filePath[filePath.size()-1] == 'h')
		tag="head";
	else
		tag="implement";

	packInfo.addSibling(xmlElem(tag,filePath));

	return packInfo.format();
}

//////////////////////////////////////////////////////////////////////////
//Retrieve all local references from the file
std::string MetaGenerator::GenerateReferences(std::string& filePath)
{
	if(!inc->Attach(filePath))return "";

	while(inc->Next())
	{
		if(inc->IsSystem())continue;
		std::string refTag = "reference name=\""+inc->GetPackageName()+"\"";
		xmlElem refElem(refTag,inc->GetFullName());
		references.addSibling(refElem);
	}

	return references.format();
}

//////////////////////////////////////////////////////////////////////////
//Embrace whole <reference> tags with <references> tag
std::string MetaGenerator::EmbraceReferences()
{
	RemoveReferenceEmbrace();
	references.makeParent(refEnbrace);
	return references.format();
}

//////////////////////////////////////////////////////////////////////////
//Combine packinfo and references tags, and embrace them with Package tag
//add xml document title
std::string MetaGenerator::CombineMetaElements(std::string packName)
{
	EmbraceReferences();

	std::string attribe = "name=\""+packName+"\"";
	std::string tag = xmlElem::makeTag("package",attribe);
	xmlElem	combine(tag,packInfo.xmlStr()+references.xmlStr());

	meta.xmlStr() = combine.elemStr();
	meta.makeDoc();

	return meta.format();
}

void MetaGenerator::RemoveReferenceEmbrace()
{
	xmlElem refer;
	if (references.find(refEnbrace,refer))
		references.xmlStr() = refer.body();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////< test stub >///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#ifdef TEST_META_GENERATOR

#include <vector>

class VectorInclude:public IInclude
{
public:
	VectorInclude()
	{
		index =-1; 
		ins.push_back("string");
		ins.push_back("vector");
		ins.push_back("list");
		ins.push_back("iostream");
		ins.push_back("vector");
	}
	virtual bool Attach(std::string path){index =-1; return true;}
	virtual bool Next(){return ++index<ins.size();}
	virtual std::string GetFullName(){return GetPackageName()+".h";}
	virtual std::string GetPackageName(){return index <ins.size()?ins[index]:"";}
	virtual bool IsSystem(){return false;};
private:
	std::vector<std::string> ins;
	size_t index;
};
//----< create a string with both over and under lines >-----------------

void title(const std::string &msg, char underChar='-') {

	std::string over = "\n";
	over += std::string(msg.size()+2,underChar);
	std::string under = std::string(msg.size()+2,underChar);
	std::string body = "\n ";
	body += msg;
	body += "\n";
	body += under;
	body += '\n';
	std::cout<< over + body;
}


void main()
{
	MetaGenerator gnrtor(new VectorInclude());
	std::string fileName = "StandardLibrary.h";

	title("Test Package Name:");
	std::cout<<fileName<<std::endl;

	title("Test Generate Package information:");
	std::cout<< gnrtor.GeneratePackInfo(fileName)<<std::endl;

	title("Test Generate References:");
	std::cout<< gnrtor.GenerateReferences(fileName)<<std::endl;
	
	title("Test Embrace References:");
	std::cout<< gnrtor.EmbraceReferences()<<std::endl;

	title("Test Create Whole Metadata xml:");
	std::cout<< gnrtor.CombineMetaElements(gnrtor.GetKeyName(fileName))<<std::endl;
}



#endif