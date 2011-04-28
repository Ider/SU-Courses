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
/*
 * Module Operations:
 * ==================
 * This module provides a interface IMetaGenerator, and a class MetaGenerator,
 * which implement the interface.
 *
 * IMetaGenerator provides basic method to get meta data, xml format string.
 * There are two ways: from packageInfo, get meta data for this package, or 
 * filePath, get meta data only for this file.
 *
 * MetaGenerator provides a example for implementation of IMetaGenerator. It is
 * also used in OOD project #2.
 *
 * Public Interface:
 * =================
 * std::cout<< gnrtor.GeneratePackInfo(fileName)<<std::endl;
 * std::cout<< gnrtor.GenerateReferences(fileName)<<std::endl;
 * std::cout<< gnrtor.EmbraceReferences()<<std::endl;
 * std::cout<< gnrtor.CombineMetaElements(gnrtor.GetKeyName(fileName))<<std::endl;
 *
 * Required Files:
 * ===============
 * xmlTran.h, xmlTran.cpp, PackageInfo.h, PackageInfo.cpp
 * IIncludes.h, MetaGenerator.h, MetaGenerator.cpp
 */

#include "..\Infrastructure\xmlTran.h"
#include "PackageInfo.h"
#include "IInclude.h"
#include <string>

class IMetaGenerator
{
public:
	virtual std::string GetMetadata(std::string& filePath) = 0;
	virtual std::string GetMetadata(PackageInfo& pack) = 0;
	virtual ~IMetaGenerator(){}
};


class MetaGenerator:public IMetaGenerator
{
public:
	MetaGenerator(IInclude* include):inc(include),refEnbrace("references"){};
	~MetaGenerator(){Clear();}
	virtual std::string GetMetadata(std::string& filePath);
	virtual std::string GetMetadata(PackageInfo& pack);
	std::string GetKeyName(std::string filePath);
	void Clear();
	std::string GeneratePackInfo(std::string& filePath);
	std::string  GenerateReferences(std::string& filePath);
	std::string  EmbraceReferences();
	std::string CombineMetaElements(std::string packName);
	std::string& OwnerName(){return owner;}
private:
	void RemoveReferenceEmbrace();
	xmlRep meta;
	xmlRep packInfo;
	xmlRep references;
	IInclude* inc;
	std::string refEnbrace;
	std::string owner;
};

#endif