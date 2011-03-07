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

std::string MetaGenerator::GetMetadata(const std::string& filePath)
{
	if(!inc->Attach(filePath))return "";

	while(inc->Next())
	{
		if(inc->IsSystem())continue;

	}

	return "";

}

std::string MetaGenerator::GetMetadata(const PackageInfo& pack)
{
	return "";
}