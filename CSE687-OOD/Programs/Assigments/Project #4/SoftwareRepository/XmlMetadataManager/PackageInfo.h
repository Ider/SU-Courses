#ifndef PACKAGE_INFO_H
#define PACKAGE_INFO_H
/////////////////////////////////////////////////////////////////////////
//  PackageInfo.h    -  facility to provider basic package information //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module provides PackageInfo class.
 *
 * PackageInfo provides struct for containing basic package informations.
 * Those information contains the paths of head and implement file, and 
 * package name.
 *
 * PackagesGenerator provides functionality to get package information
 * from the folder that given by path.
 * Before start package generation, SetResultContainer should be called
 * to specify where to put the packageInfos that generated
 * ClearResults will delete every data in container, and clear the container.
 *
 * Public Interface:
 * =================
 * PackageInfo:
 * AddFileName(fName)					add full path of file
 * std::string operator[](size_t n)     return the nth file path in package
 * size_t FileCount()					return the files count in package
 * std::string& Name()					return package name
 *
 * Required Files:
 * ===============
 * PackageInfo.h, PackageInfo.cpp
 */


#include <string>
#include <vector>


class PackageInfo
{
public:
	void AddFileName(const std::string& fName){filePaths.push_back(fName);}
	std::string operator[](size_t n) {return filePaths[n];}
	size_t FileCount(){return filePaths.size();}
	std::string& Name(){return name;}
private:
	std::string name; //the name for this package
	//it contains full paths of head and implement files of this package
	std::vector<std::string> filePaths; 
};

#endif
