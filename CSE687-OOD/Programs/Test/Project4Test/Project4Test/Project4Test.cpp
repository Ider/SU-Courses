/////Project4Test.cpp : Defines the entry point for the console application.


 #include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <stack>
#include <list>
#include <vector>
#include "str.h"
using namespace std;



class base
{
public:
	base(){l="base data";}
	 void func1(){ cout<<l.c_str();}
	void func2(){}
	virtual void fun4(){ cout<<l.c_str();}

private:
	void func3(){}
	string l;
};


class child: public base
{
public:
	child(){l ="child data\n";}
	void func1(){ cout<<l.c_str();}
	void func3(){}

	void fun4(){ cout<<l.c_str();}
private:
	void func2(){}
	string l;
};

void stlTest();
void funtest(int a)
{
	cout<<a<<'\n';
}
class DemoComp
{
public:
	DemoComp(){cout<<"demo comp constructor\n";}
	~DemoComp(){cout<<"demo  destructor\n";}
};
vector<DemoComp *> vec;

void getv()
{
	for (int i = 0; i < 2; i++)
	{
		DemoComp* pd = new DemoComp();
		vec.push_back(pd);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
// 	string s ="\n";
// 	char c1 = '\n';
// 	str s0;
// 	str s1 = str("this is a string");
// 	str s2 = s1;
// 
// 	s0 =s2;
// 
// 	cout << s1 << "\n";
// 	char c ;
// 
// 
// 	getchar();
// 
// 	const str cstr = "This is const string";
// 	cout << cstr << "\n";
// 	 c =cstr[0];
// 	 cstr[0]='0';
// 
// 	 cout << cstr << "\n";
// 	 getchar();

//stlTest();
// 	string aa ="\0";
// 	cout<<aa.length()<<endl;
// 
// 	stack<int> st;
// 	st.push(1);
// 	cout<<st.top()<<endl;
// 	if (!st.empty())
// 	{
// 		st.pop();
// 		//st.pop();
// 	}
	getv();

	vector<DemoComp*>::iterator it = vec.begin();
	for (;it != vec.end();++it)
	{
		DemoComp* p = *it;
		delete p;

	}


	cout<<"hello world";
	child* c = new child();


	base* b =c;


	c->fun4();
	b->fun4();
	c->func1();
	b->func1();



	getchar();
	return 0;
}
