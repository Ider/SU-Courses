#ifndef XMLDOC_H
#define XMLDOC_H
/////////////////////////////////////////////////////////////////////////
//  XmlDoc.h    -  facility to do operation on xml file   		   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 2010                               //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #4	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module is intended to work with xml file.
   Load xml from file, save xml to file, get directly child elements

   Public Interface:
   =================
   XmlDoc doc(xml);
   string name = doc.Name();
   vector<XmlDoc> children = doc.Children();
   cout<<children[i].ToString()<<endl;
   doc.Children("head")[0]
   doc.Children(2).ToString();

   Build Process:
   ==============
   Required Files:
		xmlTran.h, xmlTran.cpp, XmlDoc.h, XmlDoc.cpp
*/


#include <vector>
#include "xmlTran.h"


class XmlDoc:public xmlElem
{
public:
	XmlDoc(){}
	XmlDoc(const xmlElem& elem):xmlElem(elem){}
	XmlDoc(conStrRef xml){_elemStr = xml;}

	//Sub element
	std::vector<XmlDoc> Children(conStrRef tagName = "");
	XmlDoc Children(size_t index);

	//element information
    strVal Name(){return tagName();}
	strVal InnerText();

	//disk operation
	void LoadXml(conStrRef xml){_elemStr = xml;}
	bool LoadXmlFile(conStrRef fileName);
	bool SaveToFile(conStrRef fileName);

	//to string
	strVal ToString()const{return _elemStr;}
private:

	void Trim(strRef value);
	

};

#endif


