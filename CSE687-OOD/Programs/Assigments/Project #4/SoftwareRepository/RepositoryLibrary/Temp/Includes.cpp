/////////////////////////////////////////////////////////////////////////
//  Includes.cpp    -  facility to extract include from file   		   //
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

//////////////////////////////////////////////////////////////////////////
//Destructor, close in-stream if it is file stream
Includes::~Includes()
{
	if(inStream)
	{
		inStream->clear();
		std::ifstream* pFs = dynamic_cast<std::ifstream*>(inStream);
		if(pFs)
		{
			pFs->close();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//Open file given by name, if in-stream is file stream
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

//////////////////////////////////////////////////////////////////////////
//Find next include, if found return true.
bool Includes::Next()
{
	char buffer[bufSize];
	while(inStream->good())
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

	std::ifstream* pFs = dynamic_cast<std::ifstream*>(inStream);
	if(pFs)	pFs->close();

	return false;
}
//////////////////////////////////////////////////////////////////////////
//Return full name of package that included
std::string Includes::GetFullName()
{
	return curName;
}

//////////////////////////////////////////////////////////////////////////
//Remove the path and file extension, return the pure file name
std::string Includes::GetPackageName()
{
	size_t slash = curName.find('\\');
	size_t dot = curName.find_last_of('.');

	if (slash == std::string::npos)
		slash = curName.find('/');
	if (slash == std::string::npos)
		return curName.substr(0,dot);;
	

	return curName.substr(slash+1,dot);
}

//////////////////////////////////////////////////////////////////////////
//Specify whether the include is system or local
bool Includes::IsSystem()
{
	return curInc.find('<')<curInc.length();
}

//////////////////////////////////////////////////////////////////////////
//Extract package name from angle bracket
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

//////////////////////////////////////////////////////////////////////////
//Check whether the line get from file is include or not
bool Includes::ExtractInclude(char* buffer)
{
	while(*buffer =='\t'||*buffer ==' ')++buffer;
	if (*buffer!='#')return false;

	//exclude the pro-process definitions
	std::string temp (buffer);
	if (temp.find('<') == std::string::npos 
		&& temp.find('\"') == std::string::npos )
	return false;

	curInc = temp;
	return true;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////< test stub >///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


#ifdef TEST_INCLUDES

void title(const std::string &msg, char underChar='-') {

	std::string over = "\n";
	over += std::string(msg.size()+2,underChar);
	std::string under = std::string(msg.size()+2,underChar);
	std::string body = "\n ";
	body += msg;
	body += "\n";
	body += under;
	body += '\n';
	std::cout<< over + body;
}


void main(int argc, char** argv)
{
 	std::string  file = "..\\Includes.cpp";
	Includes inc(new std::ifstream());
	title("includes of file: " + file);

	if (inc.Attach(file))
		while(inc.Next())
		{
			std::cout<<(inc.IsSystem()?"System":"Local");
			std::cout<<"\t\t";
			std::cout<<inc.GetFullName();
			std::cout<<"\t\t";
			std::cout<<inc.GetPackageName();
			std::cout<<std::endl;
		}
		else
			std::cout<<"Can't open file: " + file;

	if(argc < 2)
	{
		std::cout 
			<< "\n  please enter name of file to process on command line\n\n";
		return;
	}

	for(int i=1; i<argc; ++i)
	{
		file = argv[i];
		title("includes of file: " + file);

		if (inc.Attach(file))
			while(inc.Next())
			{
				std::cout<<(inc.IsSystem()?"System":"Local");
				std::cout<<"\t\t";
				std::cout<<inc.GetFullName();
				std::cout<<"\t\t";
				std::cout<<inc.GetPackageName();
				std::cout<<std::endl;
			}
		else
			std::cout<<"Can't open file: " + file;
	}
}

#endif