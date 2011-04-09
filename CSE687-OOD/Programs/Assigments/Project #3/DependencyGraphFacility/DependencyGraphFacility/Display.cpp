
/////////////////////////////////////////////////////////////////////////
//  Dispaly.cpp  -  Provide functors for Graph DFS method		           //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #3	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////

#include "Display.h"
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;
using namespace IderPrinter;

//functor operation
void MetaPrinter::operator()(const v_ref v)
{

	cout<<"{Vertex} "<<v.Key()<<endl;
	PrintTableTitle();

	for (size_t i=0 ; i<v.Size();++i)
	{

		FormatLongString(v[i].first);
		cout<<v[i].second->Key()<<endl;

	}

	cout<<endl;


}

//format long file path information
void MetaPrinter::FormatLongString(const std::string& str)
{
	const size_t len = 30;
	const string tab(10,' ');
	size_t pos = 0;
	size_t pEnd = pos+len<str.size()?(pos+len):str.size();
	while(pEnd < str.size())
	{
		cout<<tab
			<<string(str.begin()+pos,str.begin()+pEnd)
			<<endl;
		pos = pEnd;
		pEnd = pos+len<str.size()?(pos+len):str.size();
	}
	cout<<left;
	cout<<tab<<setw(len+10)<<string(str.begin()+pos,str.begin()+pEnd);
	cout<<right;
}

//print out table title
void MetaPrinter::PrintTableTitle()
{
	cout<<setw(25)<<"{Edge}";
	cout<<setw(35)<<"{Node}";
	cout<<endl;
}

//functor operation
void MetaNestedPrinter::operator()(v_ref v)
{
	int level = GetLevel(v);
	//if (level == 0) cout<<endl;

	string tab(level,'\t');
	cout<<tab<<"{Vertex} "<<v.Key()<<endl;

	SetChildrenLevel(v);
}

//get current vertex level info
size_t MetaNestedPrinter::GetLevel(v_ref v)
{	return v.Mask()>>8;		}

//add level by 1, and set to children vertics
void MetaNestedPrinter::SetChildrenLevel(v_ref v)
{
	int level = (GetLevel(v) + 1)<<8;
	for (size_t i=0 ; i<v.Size();++i)
		v[i].second->Mask() |= level;
}



/************************************************************************/
/* <Test Stub>                                                                     */
/************************************************************************/


#ifdef DISPLAY_TEST

void main()
{
	Graph<string,int> test ;
	string a="111";
	test.AddNode( a);
	a = "222";
	test.AddNode(a);
	a = "333";
	test.AddNode(a);
	test.AddNode(string("444"));
	test.AddNode(string("555"));

	test.AddEdge("111","222",12);
	test.AddEdge("222","333",23);
	test.AddEdge("333","444",34);
	test.AddEdge("444","222",42);
	test.AddEdge("444","555",45);
	test.DFS(BasicPrinter<string,int>());

}

#endif