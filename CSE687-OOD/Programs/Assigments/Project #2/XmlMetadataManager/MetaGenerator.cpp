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

std::string MetaGenerator::GetMetadata(std::string& filePath)
{
	Clear();

	GeneratePackInfo(filePath);
	GenerateReferences(filePath);
	CombineMetaElements(GetKeyName(filePath));

	return meta.xmlStr();

}

std::string MetaGenerator::GetMetadata(PackageInfo& pack)
{
	Clear();

	for (size_t i =0; i<pack.fileCount(); ++i)
	{
		GeneratePackInfo(pack[i]);
		GenerateReferences(pack[i]);
	}

	CombineMetaElements(pack.Name());

	return meta.xmlStr();
}

std::string MetaGenerator::GetKeyName(std::string filePath)
{
	filePath.erase(filePath.find_last_of('.'),filePath.size());
	filePath.erase(0,filePath.find_last_of('\\')+1);
	return filePath;
}

void MetaGenerator::Clear()
{
	meta.flush();
	references.flush();
	packInfo.flush();
}

void  MetaGenerator::GeneratePackInfo(std::string& filePath)
{
	std::string tag;
	if(filePath[filePath.size()-1] == 'h')
		tag="head";
	else
		tag="implement";

	packInfo.addSibling(xmlElem(tag,filePath));
}

void MetaGenerator::GeneratePackInfos(PackageInfo& pack)
{
	std::string path;
	xmlElem file;
	for (size_t i =0; i<pack.fileCount(); ++i)
	{
		file.flush();
		path = pack[i];
		if(path[path.size()-1] == 'h')
			file.reviseTagName("head");
		else
			file.reviseTagName("implement");
		file.reviseBody(path);
		packInfo.addSibling(file);
	}
}

void MetaGenerator::GenerateReferences(std::string& filePath)
{
	if(!inc->Attach(filePath))return;

	while(inc->Next())
	{
		if(inc->IsSystem())continue;
		std::string refTag = "reference name=\""+inc->GetPackageName()+"\"";
		xmlElem refElem(refTag,inc->GetFullName());
		references.addSibling(refElem);
	}

}

void MetaGenerator::EmbraceReferences()
{
	references.makeParent("references");
}

void MetaGenerator::CombineMetaElements(std::string packName)
{
	EmbraceReferences();

	std::string attribe = "name=\""+packName+"\"";
	std::string tag = xmlElem::makeTag("package",attribe);
	xmlElem	combine(tag,packInfo.xmlStr()+references.xmlStr());

	meta.xmlStr() = combine.elemStr();
	meta.makeDoc();
}
