/////Project4Test.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <stack>
#include <list>
#include <vector>

#include <fstream>
#include <sstream>

#include "str.h"
using namespace std;

template <class T>
void printVector(list<T> vet)
{
	list<T>::iterator it;
	for (it = vet.begin(); it!=vet.end();it++)
	{
		cout<<*it<<" ";

	}

	cout << endl;
}

typedef bool (*MyPredicate)(const int&); 


bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
class is_odd
{
public:
	is_odd(){cout<<"call is_odd constructor\n";}
	static bool not_odd(const int& value) {return (value%2)==1; }
	
	bool operator() (const int& value) {return (value%2)==1; }
	bool Is_Odd(const int& value){return (value%2)==1; }
};

typedef bool (is_odd::*MemberPre)(const int&); 


// int main ()
// {
// 	int myints[]= {15,36,7,17,20,39,4,1};
// 	list<int> mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1
// 
// 	mylist.remove_if <MyPredicate>(single_digit);      // 15 36 17 20 39
// 
// 	is_odd o;
// 	//mylist.remove_if(o);//you can also use mylist.remove_if<is_odd>(o);
// 	
// 	//above two lines is equal to flowing line
// 	//mylist.remove_if (is_odd());          // 36 20
// 
// 	mylist.remove_if<MyPredicate>(is_odd::not_odd);
// 
// 	MyPredicate pre = is_odd::not_odd;
// 	//MyPredicate pre2 = o.Is_Odd; //assign 
// 
// 
// 	// pointer to member function
// 	MemberPre mp = &is_odd::Is_Odd;
// 	(o.*mp)(9);
// // 
// // 	cout << "mylist contains:";
// // 	for (list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
// // 		cout << " " << *it;
// // 	
// 	printVector(mylist);
// 	return 0;
// }



int main()
{
	ifstream* inf = new ifstream();
	inf->clear();
	inf->open("Readme.txt");

	ofstream* outf = new ofstream();
	outf->open("Hello.xml");

	char line[255];
	if (inf->good())
	{

		inf->getline(line,255);
		cout<< line<<endl;
	}
	inf->clear();
	inf->close();
	inf->open("STR.cpp");

	if (inf->good())
	{
		while (!inf->eof())
		{

			inf->getline(line,255);
			cout<< line<<endl;
			if (outf->good())
			{
				(*outf)<<line<<endl;
			}
		}
	}
	else
	{
		cout<<"Can't open the file"<<endl;
		(*outf)<<"Can't open the file"<<endl;
	}

	inf->close();
	outf->close();

	delete inf;
	delete outf;

}
