#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>


using namespace std;

template <class T>
void printVector(vector<T> vet)
{
	vector<T>::iterator it;
	for (it = vet.begin(); it!=vet.end();it++)
	{
		cout<<*it<<endl;
	}
}

void stlTest()
{
	vector<string> vet1;

	vet1.push_back("string 1");
	vet1.push_back("string 2");
	vet1.push_back("string 3");

	printVector(vet1);

	vector<string> vet2 = vet1;
	vet1[0]="string 0";
	printVector(vet1);

	printVector(vet2);


}

void elses()
{
 cout<<"hello world";
}

