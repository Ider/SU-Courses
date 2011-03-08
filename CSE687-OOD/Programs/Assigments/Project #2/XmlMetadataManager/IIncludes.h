#ifndef IINCLUDE_H
#define IINCLUDE_H
/////////////////////////////////////////////////////////////////////////
//  IInclude.h    -  IInclude interface						   		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


#include <string>

class IInclude
{
public:
	virtual ~IInclude(){}
	virtual bool Attach(std::string name) =0;
	virtual bool Next()=0;
	virtual std::string GetFullName()=0;
	virtual std::string GetPackageName()=0;
	virtual bool IsSystem()=0;
};

#endif