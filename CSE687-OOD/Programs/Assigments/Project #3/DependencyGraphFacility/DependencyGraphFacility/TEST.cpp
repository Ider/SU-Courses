#include <iostream>
#include <utility>
#include <string>
//using namespace std;

#include "Graph.h"

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

	Graph<int,int> text ;
	try
	{
		int a =1;
	text.AddNode(a);
	a = 2;
	text.AddNode(a);
	a = 3;
	text.AddNode(4);
	text.AddEdge(1,2);

	Graph<int,int> test = text;
	test = text;

	}
	catch(std::string x)
	{
		std::cout<<x;
	}
}