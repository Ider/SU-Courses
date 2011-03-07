/////////////////////////////////////////////////////////////////////////
//  Includes.h    -  facility to extract include from file   		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


#include "Includes.h"
#include <fstream>
#include <sstream>

bool Includes::Attach(std::string name)
{
	if(inStream)
	{
		inStream->clear();
	}

	std::ifstream* pFs = dynamic_cast<std::ifstream*>(inStream);
	if(!pFs)return false;

	pFs->close();

	pFs->open(name);
	return pFs->good();
}


bool Includes::Next()
{
	char buffer[bufSize];
	while(!inStream->good())
	{
		inStream->getline(buffer,bufSize);
		if (ExtractInclude(buffer))
		{
			ExtractName();
			return true;
		}
	}

	curInc="";
	curName="";
	return false;
}

std::string Includes::GetFullName()
{
	return curName;
}

std::string Includes::GetPackageName()
{
	size_t slash = curInc.find('\\');
	if (slash == std::string::npos)
		slash = curInc.find('/');
	if (slash == std::string::npos)
		return curInc;

	return curInc.substr(slash+1);
}


bool Includes::IsSystem()
{
	return curInc.find('<')<curInc.length();
}

void Includes::ExtractName()
{
	size_t bracket = curInc.find('<');
	size_t quote = curInc.find('\"');
	size_t start = std::min(bracket,quote);
	if (start == std::string::npos)
	{
		curName = "";
		return;
	}

	bracket = curInc.find_last_of('>');
	quote = curInc.find_last_of('\"');
	size_t end = std::min(bracket,quote);
	if (end ==std::string::npos || end <= start+1)
	{
		curName = "";
		return;
	}

	curName = curInc.substr(start+1, end-start-1);
}

bool Includes::ExtractInclude(char* buffer)
{
	while(*buffer =='\t'||*buffer ==' ')++buffer;
	if (*buffer!='#')return false;

	curInc = std::string(buffer);
}
