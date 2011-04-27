
#include <iostream>
#include <fstream>

using namespace std;

#include "XmlDoc.h"


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
		if (end >= rep.xmlStr().size())break;

		strVal xml = rep.xmlStr();
		rep.xmlStr() = xml.substr(end);
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

bool XmlDoc::LoadXmlFile(conStrRef fileName)
{
	ifstream inf;
	strVal container;
	char buffer[255];

	inf.open(fileName);
	while(inf.good())
	{
		inf.getline(buffer,255);
		container += strVal(buffer);
	}
	inf.close();

	if (container.size()>0)
	{
		_elemStr = container;
		return true;
	}

	return false;
}

bool XmlDoc::SaveToFile(conStrRef fileName)
{
	throw string("To be implemented.");

	ofstream out(fileName.c_str());
	if(!out.good())
		return false;
	
	out << _elemStr;
	out.flush();
	return true;
}

strVal XmlDoc::InnerText()
{
	strVal text = body();
	Trim(text);
	return text;
}

//////////////////////////////////////////////////////////////////////////
//Removes all occurrences of white space characters from the beginning and 
//end of string. 
void XmlDoc::Trim(strRef value)
{
	const char * ch = value.c_str();
	size_t top = 0;
	size_t end = value.size() - 1;
	while(top <= end && 
		(ch[top] ==' ' || ch [top] == '\t'))
		++top;
	while(end >=0 && (ch[end] ==' ' || ch [end] == '\t'))
		--end;

	top = (top >= value.size())?top = 0 : top;
	end  =  end<0? end = value.size() : end+1;

	value.erase(end,value.size());
	value.erase(0,top);

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
