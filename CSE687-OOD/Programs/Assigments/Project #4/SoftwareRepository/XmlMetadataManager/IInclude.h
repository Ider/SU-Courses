#ifndef IINCLUDE_H
#define IINCLUDE_H
/////////////////////////////////////////////////////////////////////////
//  IInclude.h    -  IInclude interface						   		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * IIclude is an interface that support basic methods to extract include
 * information.
 * 
 * In test stub of MetaGenerator.cpp, we define a class VectorInclude that
 * implement this interface. VectorInclude extract include information
 * from vector<string>
 *
 * Includes also implement this interface, it extrace include information
 * from package files.
 *
 */

#include <string>

class IInclude
{
public:
	virtual ~IInclude(){}
	virtual bool Attach(std::string name) =0; 
	virtual bool Next()=0;	//find next include, if found return true
	virtual std::string GetFullName()=0;	//return full name of included package
	virtual std::string GetPackageName()=0;	//return name of included package
	virtual bool IsSystem()=0;
};

#endif