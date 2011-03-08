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
#include <string>
#include <vector>
#include <map>

#include "FileSystem.h"

class PackageInfo
{
public:
	void AddFileName(const std::string& fName){fileNames.push_back(fName);}
	std::string operator[](size_t n) {return	fileNames[n];}
	size_t FileCount(){return fileNames.size();}
	std::string& Name(){return name;}
private:
	std::string name; //the name for this package
	//it contains full paths of head and implement files of this package
	std::vector<std::string> fileNames; 
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
