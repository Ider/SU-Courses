#include <iostream>
#include <utility>
#include <string>
using namespace std;
#include <list>

#include "Graph.h"

void printInt(Vertex<string,int> v)
{
	cout<<v.Key()<<"\t edges:";
		for (size_t i=0 ; i<v.Size();++i)
		{
			cout<<v[i].first<<',';
		}

	cout <<endl;
}

void printInt2(Vertex<int,int> v)
{
	cout<<v.Key()<<"\t edges:";
	for (size_t i=0 ; i<v.Size();++i)
	{
		cout<<v[i].first<<',';
	}
	cout <<endl;
}

void  main () {
// 	std::pair <std::string,double> product1 ("tomatoes",3.25);
// 	std::pair <std::string,double*> product2;
// 	std::pair <std::string,double> product3;
// 
// 	double d = 0.99;
// 	product2.first = "lightbulbs";     // type of first is std::string
// 	product2.second = &d;            // type of second is double
// 
// 	//double* s = (double*)();
// 
// 	product3 = std::make_pair ("shoes",20.0);
// 
// 	std::cout << "The price of " << product1.first << " is $" << product1.second << "\n";
// 	std::cout << "The price of " << product2.first << " is $" << product2.second << "\n";
// 	std::cout << "The price of " << product3.first << " is $" << product3.second << "\n";
// 	return 0;

	Graph<string,int> text ;
	try
	{

	
		string a ="111";
	text.AddNode( a);
	a = "222";
	text.AddNode(a);
	a = "333";
	text.AddNode(a);
	text.AddNode(string("444"));

// 	text.AddEdge("111","333",3);
// 	text.AddEdge("333","222",2);
// 	text.AddEdge("333","444",4);
	Graph<string,int> test = text;
	test = text;

	vector<pair<string,int>> es;
	pair<string,int> e;

	e.first = "444";
	e.second = 4;
	es.push_back(e);
	e.first = "111" ;
	e.second = 1;
	es.push_back(e);
	e.first = "222";
	e.second = 2;
	es.push_back(e);
	text.AddEdge("111",es);

	text.DFS(printInt);
	StrongComponents<string,int> sc(test);

	sc.Condensed.DFS(printInt2);

	test.DFS(printInt);

	//Graph<string,int>::StrongComponents s = text.GetStrongComponents();

	//s.Condensed.DFS(printInt2);
	//s.

// 	list<int> b;
// 	b.remove_if()
	}
	catch(std::string x)
	{
		std::cout<<x;
	}
}