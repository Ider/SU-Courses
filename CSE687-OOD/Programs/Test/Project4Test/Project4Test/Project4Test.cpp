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


bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
class is_odd
{
public:
	is_odd(){cout<<"call is_odd constructor\n";}
	bool not_odd(const int& value) {return (value%2)==1; }
	
	bool operator() (const int& value) {return (value%2)==1; }
};

int main ()
{
	int myints[]= {15,36,7,17,20,39,4,1};
	list<int> mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1

	mylist.remove_if (single_digit);      // 15 36 17 20 39

	is_odd o;
	mylist.remove_if(o);
	//above two lines is equal to flowing line
	//mylist.remove_if (is_odd());          // 36 20

	cout << "mylist contains:";
	for (list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
		cout << " " << *it;
	cout << endl;

	return 0;
}

