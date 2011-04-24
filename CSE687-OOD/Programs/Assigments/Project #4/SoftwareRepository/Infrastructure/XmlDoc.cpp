
#include <iostream>
#include "XmlDoc.h"

using namespace std;


vector<XmlDoc> XmlDoc::Children(conStrRef tagName)
{
	vector<XmlDoc> children;
	xmlRep rep(_elemStr);
	xmlElem elem;

	//escape the <?xml> title,
	//and only return the children of first elem
	if(!rep.firstElem(elem))return children;
	rep.xmlStr() = elem.body();

	while(rep.firstElem(elem))
	{
		if(tagName.size()==0 || tagName==elem.tagName())
			children.push_back(elem);

		rep.front();
		strPos end = rep.findCloseTag(elem.tagName());
		if (end+1 >= rep.xmlStr().size())break;

		strVal xml = rep.xmlStr();
		rep.xmlStr() = xml.substr(end+1);
	}

	return children;
}

XmlDoc XmlDoc::Children(size_t index)
{
	xmlRep rep(_elemStr);
	xmlElem elem;

	//escape the <?xml> title,
	//and only return the children of first elem
	if(!rep.firstElem(elem))return XmlDoc();
	rep.xmlStr() = elem.body();

	while(rep.firstElem(elem))
	{
		rep.front();
		strPos end = rep.findCloseTag(elem.tagName());
		strRef xml = rep.xmlStr();
		rep.xmlStr() = xml.substr(end+1,string::npos);

		if (index ==0)return XmlDoc(elem);
		--index;
		elem.flush();
	}

	//index is out of range, no exception, just return empty doc
	return XmlDoc();
}

#ifdef XMLDOC_TEST


void title(string msg, char underChar='-') {

	string over = "\n";
	over += string(msg.size()+2,underChar);
	string under = string(msg.size()+2,underChar);
	string body = "\n ";
	body += msg;
	body += "\n";
	body += under;
	body += '\n';
	cout<< (over + body);
}

void main()
{

	string xml ="<package name=\"Display\">		<head>Display.h  </head>  <implement>Display.cpp  </implement>  <references>  <reference name=\"Graph\">  Graph.h  </reference>  <reference name=\"Display\">  Display.h  </reference>  </references>  </package>";

	XmlDoc doc(xml);
	title("get doc name");
	string name = doc.Name();

	cout<<name<<endl;


	title("Test children function");

	vector<XmlDoc> children = doc.Children();

	cout<<"Children size "<<children.size()<<endl<<endl;

	for (size_t i=0; i<children.size(); ++i)
	{
		cout<<children[i].ToString()<<endl;
	}

	cout<<endl;
	children =	children[2].Children();
	cout<<"Children of Children[2] size "<<children.size()<<endl<<endl;

	for (size_t i=0; i<children.size(); ++i)
	{
		cout<<children[i].ToString()<<endl;
	}


	title("Test children function with index");
	cout<<endl<<doc.Children(2).ToString();

	title("Test children function with string ");
	cout<<endl<<doc.Children("head")[0].ToString();
}

#endif
