#ifndef INCLUDES_H
#define INCLUDES_H
/////////////////////////////////////////////////////////////////////////
//  Includes.h    -  facility to extract include from file   		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


#include "IIncludes.h"
#include <iostream>

class Includes :public IInclude
{
public:
	Includes(std::istream* pIn):inStream(pIn){}
	virtual ~Includes();
	virtual bool Attach(std::string name);
	virtual bool Next();
	virtual std::string GetFullName();
	virtual std::string GetPackageName();
	virtual bool IsSystem();
private:
	void ExtractName();
	bool ExtractInclude(char* buffer);
	std::string curInc;//save current include line
	std::string curName; //save current include name
	std::istream* inStream;
	static const int bufSize = 255;
};

#endif