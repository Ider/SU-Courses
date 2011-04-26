#ifndef META_MANAGER_H
#define META_MANAGER_H
/////////////////////////////////////////////////////////////////////////
// MetaManager.h - integrate meta modules and configure them           //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module integrate meta module together, and build each module object;
 * let the object to work under control;
 * provide basic data for modules
 *
 * Public Interface:
 * =================
 * MetaManager mgr2xml;
 * mgr2xml.Build(argc,argv);
 * mgr2xml.CreateMetaXML();
 * mgr2xml.NavigateMetaXML(name);
 *
 * Required Files:
 * ===============
 * FileSystem.cpp, FileSystem.h, IIncludes.h, Includes.cpp, Includes.h
 * MetaGenerator.cpp, MetaGenerator.h, MetaManager.cpp, MetaManager.h
 * MetaNavigator.cpp, MetaNavigator.h, PackageInfo.cpp, PackageInfo.h
 * xmlTran.cpp, xmlTran.h
 *
 * Build Command:
 * ==============
 * [path](\S+) [pattern](*.*){0,2} [recursion](/r)? [entry](\S+)
 * path: the folder path that start to navigate
 * pattern: files patterns that need to get, *.h or *.cpp or both
 * recursion: need recursively navigate sub-folders
 * entry: package name that provided to begin navigation
 *
 * Example: .. *.h *.cpp /r MetaManager
 */
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