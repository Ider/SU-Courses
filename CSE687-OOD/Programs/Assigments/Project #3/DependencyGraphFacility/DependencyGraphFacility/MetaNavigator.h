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

#include <vector>
#include <string>
#include <fstream>
#include "Graph.h"
#include "xmlTran.h"
class MetaNavigator
{
public:
	MetaNavigator(Graph<std::string,std::string>& g):graph(g){}
	void BeginNavigation(const std::string& filePath);
	std::string GetKeyName(std::string filePath);

private:
	void ExtractFileContent
		(std::string& containe, const std::string& filePath);
	void Dependencies(xmlRep& xml,std::list<std::string>& deps);
	void GenerateEdges(std::string filePath,std::list<std::string>& deps);
	void Trim(std::string& value);

	Graph<std::string,std::string>& graph;
	std::ifstream inf;
};


#endif