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
	void addFileName(const std::string& fName){fileNames.push_back(fName);}
	std::string operator[](int n) {return	fileNames[n];}
	size_t fileCount(){return fileNames.size();}
	std::string& Name(){return name;}
private:
	std::string name; //the name for this package
	//it contains full paths of head and implement files of this package
	std::vector<std::string> fileNames; 
};

typedef std::map<std::string, PackageInfo*> packMap;
typedef std::map<std::string, PackageInfo*>::iterator  packIterator;


class PackagesGenerator
{
public:
	void SetResultContainer(packMap& packs){pPacks = &packs;}
	void ClearResults();
private:
	std::string getFileKeyName(std::string fileName);

	bool getCommands(int argc, char* argv[]);
	void getFiles();
	void getFiles(std::string path, std::string& pattern);
	void getSubFiles(std::string path, std::string& pattern);

	packMap * pPacks;
	bool needRecursion;
	std::vector<std::string> pattens;
	std::string rPath;
	WinTools_Extracts::FileHandler fh;
};

#endif
