

#include "Display.h"
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;
using namespace IderPrinter;

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
		pos = pEnd+1;
		pEnd = pos+len<str.size()?(pos+len):str.size();
	}
	cout<<left;
	cout<<tab<<setw(len+10)<<string(str.begin()+pos,str.begin()+pEnd);
	cout<<right;
}

void MetaPrinter::PrintTableTitle()
{
	cout<<setw(25)<<"{Edge}";
	cout<<setw(35)<<"{Node}";
	cout<<endl;
}


void MetaNestedPrinter::operator()(v_ref v)
{
	int level = GetLevel(v);
	//if (level == 0) cout<<endl;

	string tab(level,'\t');
	cout<<tab<<"{Vertex} "<<v.Key()<<endl;

	SetChildrenLevel(v);
}

size_t MetaNestedPrinter::GetLevel(v_ref v)
{	return v.Mask()>>8;		}

void MetaNestedPrinter::SetChildrenLevel(v_ref v)
{
	int level = (GetLevel(v) + 1)<<8;
	for (size_t i=0 ; i<v.Size();++i)
		v[i].second->Mask() |= level;
}

