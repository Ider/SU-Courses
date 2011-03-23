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

/*
 * Module Operations:
 * ==================
 * This module provides class, Include, that implement interface IInclude.
 * Include will extract include info from instream.
 * If in-stream is file stream, it will open the file by path that given.
 *
 * Public Interface:
 * =================
 * Includes inc(new std::ifstream());
 * inc.Attach(file)
 * while(inc.Next())
 * inc.IsSystem()?"System":"Local"
 * inc.GetFullName();
 * inc.GetPackageName();
 * 
 * Required Files:
 * ===============
 * Includes.h, Includes.cpp, IIncludes.h
 *
 * Build Command:
 * ==============
 * [paths](S+ )+
 * paths: paths of files that need to extract include info
 *
 * Example: ../Include.h ../Include.cpp
 */

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