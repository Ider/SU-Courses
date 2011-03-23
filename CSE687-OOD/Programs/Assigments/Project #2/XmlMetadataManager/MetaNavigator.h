#ifndef META_NAVIGATOR_H
#define META_NAVIGATOR_H
/////////////////////////////////////////////////////////////////////////
//  MetaNavigator.h  -  Navigate metadata xml files and print file info//
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
 * This module provides a interface, IMetaNavigator, and a class, MetaNavigator,
 * that implement this interface.
 * IMetaNavigator supports only one method BeginNavigation to start navigation
 * on xml file cluster.
 *
 * MetaNavigator is a example the implement navigation functionality. It also
 * been use for OOD project #2
 *
 * Public Interface:
 * =================
 * IMetaNavigator*  nav = new MetaNavigator();
 * nav->BeginNavigation("MetaManager","MetaXML");
 *
 * Required Files:
 * ===============
 * MetaNavigator.h, MetaNavigator.cpp, xmlTran.h, xmlTran.cpp
 * MetaXML/MetaManager.xml
 */

#include <string>
#include <fstream>
#include <queue>
#include <set>

#include "xmlTran.h"

class IMetaNavigator
{
public:
	virtual void BeginNavigation(const std::string& folderPath,const std::string fileName)=0;
	~IMetaNavigator(){}
};

class MetaNavigator: public IMetaNavigator
{
public:
	virtual void BeginNavigation
		(const std::string& fileName, const std::string folderPath = "");
private:
	void BeginNavigation();
	void ExtractFileContent
		(std::string& containerconst, const std::string& name);
	void RetrivePackageInfo(xmlRep& xml);
	void Dependencies(xmlRep& xml);
	std::string GetKeyName(std::string filePath);
	void Trim(std::string& value);
	std::string xmlFolder;
	std::ifstream inf;
	std::set<std::string> navigatedFiles; //the files that has already been navigated
	std::queue<std::string> navigatingList;//the files that to be navigated.
};

#endif