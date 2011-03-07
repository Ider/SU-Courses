#ifndef META_GENERATOR_H
#define META_GENERATOR_H
/////////////////////////////////////////////////////////////////////////
//  MetaGenerator.h    -  facility to generator metadata xml files     //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


#include "xmlTran.h"
#include "PackageInfo.h"
#include "IIncludes.h"
#include <string>

class IMetaGenerator
{
public:
	virtual std::string GetMetadata(std::string& filePath) = 0;
	virtual std::string GetMetadata(PackageInfo& pack) = 0;
};


class MetaGenerator:public IMetaGenerator
{
public:
	MetaGenerator(IInclude* include):inc(include),refEnbrace("references"){};
	~MetaGenerator(){Clear();	delete inc;}
	virtual std::string GetMetadata(std::string& filePath);
	virtual std::string GetMetadata(PackageInfo& pack);
	std::string GetKeyName(std::string filePath);
	void Clear();
	std::string GeneratePackInfo(std::string& filePath);
	std::string  GenerateReferences(std::string& filePath);
	std::string  EmbraceReferences();
	void CombineMetaElements(std::string packName);
private:
	void RemoveReferenceEmbrace();
	xmlRep meta;
	xmlRep packInfo;
	xmlRep references;
	IInclude* inc;
	std::string refEnbrace;
};

#endif