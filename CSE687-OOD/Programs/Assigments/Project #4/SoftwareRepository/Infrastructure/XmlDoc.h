#ifndef XMLDOC_H
#define XMLDOC_H

#include <vector>
#include "xmlTran.h"


class XmlDoc:public xmlElem
{
public:
	XmlDoc(){}
	XmlDoc(const xmlElem& elem):xmlElem(elem){}
	XmlDoc(conStrRef xml){_elemStr = xml;}
	std::vector<XmlDoc> Children(conStrRef tagName = "");
	XmlDoc Children(size_t index);

    strVal Name(){return tagName();}
	strVal InnerText(){return body();}
	void LoadXml(conStrRef xml){_elemStr = xml;}
	strVal ToString()const{return _elemStr;}
private:

};

#endif


