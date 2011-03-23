#ifndef PACKAGE_INFO_H
#define PACKAGE_INFO_H
/////////////////////////////////////////////////////////////////////////
//  PackageInfo.h    -  facility to provider basic package information //
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
 * This module provides two classes, PackageInfo and PackagesGenerator.
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
 * PackageGenerator:
 * packMaker.SetResultContainer(results) set result container
 * packMaker.BuildPakcages(argc,argv);	clear data and add new data
 * packMaker.AppendPakcages(argc,argv)	append data to container
 * ClearResults();						clear data in container
 * Build Command:
 * ==============
 * [path](\S+) [pattern](*.*){0,2} [recursion](/r)?
 * path: the folder path that start to navigate
 * pattern: files patterns that need to get, *.h or *.cpp or both
 * recursion: need recursively navigate sub-folders
 *
 * Example: . *.h *.cpp /r
 *
 * Required Files:
 * ===============
 * PackageInfo.h, PackageInfo.cpp, FileSystem.h, FileSystem.cpp
 */


#include <string>
#include <vector>
#include <map>

#include "FileSystem.h"

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

typedef std::map<std::string, PackageInfo*> PackMap;
typedef std::map<std::string, PackageInfo*>::iterator  PackIterator;


class PackagesGenerator
{
public:
	size_t BuildPakcages(int argc, char* argv[]);
	size_t AppendPakcages(int argc, char* argv[]);
	void SetResultContainer(PackMap& packs){pPacks = &packs;}
	void ClearResults();
private:
	std::string GetKeyName(std::string fileName);
	std::string GetFileKeyName(std::string filePath);
	bool GetCommands(int argc, char* argv[]);
	void GetFiles();
	void GetFiles(std::string path, std::string& pattern);
	void GetSubFiles(std::string path, std::string& pattern);

	PackMap * pPacks; //packages container
	bool needRecursion;
	std::vector<std::string> pattens; //package patterns that needed to find
	std::string rPath; //root path
	WinTools_Extracts::FileHandler fh;
};

#endif
