/////////////////////////////////////////////////////////////////////////
//  PackageInfo.cpp    -  facility to provider basic package information //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


#include <iostream>
#include "PackageInfo.h"

//////////////////////////////////////////////////////////////////////////
//Clear the result map, add new package infos to it
size_t PackagesGenerator::BuildPakcages(int argc, char* argv[])
{
	if (!GetCommands(argc,argv))return 0;
	
	ClearResults();
	GetFiles();

	return pPacks->size();
}

//////////////////////////////////////////////////////////////////////////
//Generator new package infos, and append them to the result map
size_t PackagesGenerator::AppendPakcages(int argc, char* argv[])
{
	if (!GetCommands(argc,argv))return 0;

	GetFiles();
	return pPacks->size();
}

//////////////////////////////////////////////////////////////////////////
//Delete every object in the results map, clear the result
void PackagesGenerator::ClearResults()
{
	if (pPacks->size()==0)return;
	PackIterator it;
	for ( it=pPacks->begin() ; it != pPacks->end(); it++ )
		if (it->second)delete (it->second);
	pPacks->clear();
}

//////////////////////////////////////////////////////////////////////////
//Analyze command line, and extract the information
bool PackagesGenerator::GetCommands(int argc, char* argv[])
{
	bool h = false;
	bool cpp = false;
	int recurIndex = 0;
	if (argc <2)
	{
		std::cout<<"The command line is not formated."<<std::endl;
		std::cout<<"Please enter command line as:"<<std::endl;
		std::cout<<"[path](\\S+) [pattern](*.*){0,2} [recursion](/r)?"<<std::endl;
		return false;
	}

	rPath =fh.getFullPath(argv[1]);

	pattens.clear();
	for (int i=2; i<argc; ++i)
	{
		if (!h && !strcmp(argv[i],"*.h"))h = true;
		if (!cpp&&  !strcmp(argv[i],"*.cpp"))cpp = true;
	}

	if (h)pattens.push_back("*.h");
	if (cpp)pattens.push_back("*.cpp");
	if (!pattens.size())
	{
		pattens.push_back("*.h");
		pattens.push_back("*.cpp");
		recurIndex = 2;
	}
	else
		recurIndex = 2 + pattens.size();

	if (recurIndex<argc)
		needRecursion = !strcmp(argv[recurIndex],"/r");
	else
		needRecursion = false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
//get each patten of files
void PackagesGenerator::GetFiles()
{
	for (size_t i = 0; i<pattens.size();++i)
		GetFiles(rPath,pattens[i]);
}

//////////////////////////////////////////////////////////////////////////
//get all files in the path
//if need recursion, enter into sub folders
void PackagesGenerator::GetFiles(std::string path, std::string& pattern)
{
	std::vector<std::string> files = fh.getFileSpecs(path,pattern);
	std::string key;
	PackIterator it;
	PackageInfo* pack;
	for (size_t i=0; i<files.size();i++)
	{
		key = GetKeyName(files[i]);
		it = pPacks->find(key);
		if (it == pPacks->end())
		{
			pack = new PackageInfo();
			pack->AddFileName(files[i]);
			pack->Name() = GetFileKeyName(files[i]);
			(*pPacks)[key] = pack;
		}
		else
		{
			it->second->AddFileName(files[i]);
		}
	}

	if (needRecursion)GetSubFiles(path,pattern);
}

//////////////////////////////////////////////////////////////////////////
//get all folders under the path, and get files under this path
void PackagesGenerator::GetSubFiles(std::string path, std::string& pattern)
{
	std::string temp = path;
	if (temp[temp.size()-1]!='\\'&&temp[temp.size()-1]!='/')
		temp+="\\";

	std::vector<std::string> currdirs = fh.getDirectories(temp+"*");
	for(size_t i=0; i<currdirs.size(); ++i)
	{
		if (currdirs[i][0] == '.')continue;
		GetFiles(temp+currdirs[i],pattern);
	}

}

//////////////////////////////////////////////////////////////////////////
//remove file extension
std::string PackagesGenerator::GetKeyName(std::string fileName)
{
	int dot = fileName.size()-1;
	while (dot >=0 && fileName[dot]!='.' && fileName[dot]!='\\')--dot;
	if (dot >=0 && fileName[dot] == '.')
		fileName.erase(dot,fileName.size());
	return fileName;
}

//////////////////////////////////////////////////////////////////////////
//Remove the path and file extension, return the pure file name
std::string PackagesGenerator::GetFileKeyName(std::string filePath)
{
	filePath.erase(filePath.find_last_of('.'),filePath.size());
	filePath.erase(0,filePath.find_last_of('\\')+1);
	return filePath;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////< test stub >///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


#ifdef TEST_PACKAGE_INFO

void main(int argc, char** argv)
{
	PackagesGenerator packMaker;
	PackMap results;
	packMaker.SetResultContainer(results);

	packMaker.BuildPakcages(argc,argv);
	
	if (!results.size())
	{
		std::cout<<"No files found!"<<std::endl;
		return;
	}
	std::cout<<"Test of PackInfos Generator"<<std::endl;
	std::cout<<std::string(30,'=')<<std::endl<<std::endl;

	PackIterator pIt;
	size_t count;
	for (pIt = results.begin(); pIt != results.end(); ++pIt)
	{
		PackageInfo& pack = *(pIt->second);
		std::cout<<"Package Name:\t";
		std::cout<<pack.Name()<<std::endl;
		count = 0;
		while (count < pack.FileCount())
		{
			std::cout<<pack[count]<<std::endl;
			++count;
		}

		std::cout<<std::endl<<std::endl;
	}
}

#endif