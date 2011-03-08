#include "PackageInfo.h"



void PackagesGenerator::ClearResults()
{
	if (pPacks->size()==0)return;
	packMap::iterator it;
	for ( it=pPacks->begin() ; it != pPacks->end(); it++ )
		if (it->second)delete (it->second);
	pPacks->clear();
}

bool PackagesGenerator::getCommands(int argc, char* argv[])
{
	bool h = false;
	bool cpp = false;
	if (argc <2)return false;
	pattens.clear();

	rPath =fh.getFullPath(argv[1]);
	needRecursion = !strcmp(argv[argc-1],"/r");

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
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
//get each patten of files
void PackagesGenerator::getFiles()
{
	for (size_t i = 0; i<pattens.size();++i)
		getFiles(rPath,pattens[i]);
}

//////////////////////////////////////////////////////////////////////////
//get all files in the path
//if need recursion, enter into sub folders
void PackagesGenerator::getFiles(std::string path, std::string& pattern)
{
	std::vector<std::string> files = fh.getFileSpecs(path,pattern);
	std::string key;
	packIterator it;
	PackageInfo* pack;
	for (size_t i=0; i<files.size();i++)
	{
		key = getFileKeyName(files[i]);
		it = pPacks->find(key);
		if (it == pPacks->end())
		{
			pack = new PackageInfo();
			pack->addFileName(files[i]);
			(*pPacks)[key] = pack;
		}
		else
		{
			it->second->addFileName(files[i]);
		}
	}

	if (needRecursion)getSubFiles(path,pattern);
}

//////////////////////////////////////////////////////////////////////////
//get all folders under the path, and get files uder this path
void PackagesGenerator::getSubFiles(std::string path, std::string& pattern)
{
	std::string temp = path;
	if (temp[temp.size()-1]!='\\'&&temp[temp.size()-1]!='/')
		temp+="\\";

	std::vector<std::string> currdirs = fh.getDirectories(temp+"*");
	for(size_t i=0; i<currdirs.size(); ++i)
	{
		if (currdirs[i][0] == '.')continue;
		getFiles(temp+currdirs[i],pattern);
	}

}

//////////////////////////////////////////////////////////////////////////
//remove file extension
std::string PackagesGenerator::getFileKeyName(std::string fileName)
{
	int dot = fileName.size()-1;
	while (dot >=0 && fileName[dot]!='.' && fileName[dot]!='\\')--dot;
	if (dot >=0 && fileName[dot] == '.')
		fileName.erase(dot,fileName.size());
	return fileName;
}


