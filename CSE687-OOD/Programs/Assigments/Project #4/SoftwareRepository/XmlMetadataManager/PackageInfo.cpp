/////////////////////////////////////////////////////////////////////////
//  PackageInfo.cpp    -  facility to provider basic package information //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//////////////////////< test stub >///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <fstream>
using namespace std;

#include "PackageInfo.h"
#include "Includes.h"
#include "MetaGenerator.h"
#include "IInclude.h"

void main(int argc, char** argv)
{
	PackageInfo pack;
	pack.Name() = "PackageInfo";
	pack.AddFileName(".\\PackageInfo.h");
	pack.AddFileName(".\\PackageInfo.cpp");

	ifstream fIn;
	IInclude* inc = new Includes(&fIn);
	MetaGenerator gen(inc);

	gen.OwnerName()="Ider";

	cout<<gen.GetMetadata(pack);



	delete inc;

}
#ifdef TEST_PACKAGE_INFO

#endif