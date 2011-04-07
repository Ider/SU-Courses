#include <iostream>
#include <utility>
#include <string>
#include <list>

using namespace std;

#include "Graph.h"
#include "GraphAlgorithm.h"
#include "Printers.h"

#ifdef TEST_CPP
void printInt(const Vertex<string,int>& v)
{
	cout<<v.Key()<<"\t edges:";
	for (size_t i=0 ; i<v.Size();++i)
	{
		cout<<v[i].first<<',';
	}
	cout <<endl;
}

bool VertexPredicate(const Vertex<string,int>& v)
{
	for (size_t i=0 ; i<v.Size();++i)
	{
		if (v[i].first%10==2)
		{
			return true;
		}
	}

	return false;
}

bool EdgePredicate(const int e)
{
	return e<30;
}


class Printer
{
public:
	void operator()(const Vertex<string,int>& v);
};

void Printer::operator()(const Vertex<string,int>& v)
{
	cout<<v.Key()<<"\t edges:";
	for (size_t i=0 ; i<v.Size();++i)
	{
		cout<<v[i].first<<',';
	}

	cout <<endl;
}



void printInt2(const Vertex<int,int>& v){
	cout<<v.Key()<<"\t edges:";
	for (size_t i=0 ; i<v.Size();++i)
	{
		cout<<v[i].first<<',';
	}
	cout <<endl;
}

void  main () {

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
		text.AddNode(string("555"));

		// 	text.AddEdge("111","333",3);
		// 	text.AddEdge("333","222",2);
		// 	text.AddEdge("333","444",4);
		Graph<string,int> test = text;
		test = text;
		//test.DFS()
		// 	vector<pair<string,int>> es;
		// 	pair<string,int> e;
		// 
		// 	e.first = "444";
		// 	e.second = 4;
		// 	es.push_back(e);
		// 	e.first = "111" ;
		// 	e.second = 1;
		// 	es.push_back(e);
		// 	e.first = "222";
		// 	e.second = 2;
		// 	es.push_back(e);
		// 	text.AddEdge("111",es);
		// 
		// 	text.DFS(printInt);
		test.AddEdge("111","222",12);
		test.AddEdge("222","333",23);
		test.AddEdge("333","444",34);
		test.AddEdge("444","222",42);
		test.AddEdge("444","555",45);

		test.DFS(Printer());
		StrongComponents<string,int> sc(test);
		cout<<"_____________________________________\n";
		sc.Condensed.DFS(printInt2);
		cout<<"_____________________________________\n";

		test.AddNode(string("666"));

		test.AddEdge("333","555",35);
		sc.Rebuild();
		sc.Condensed.DFS(printInt2);
		std::list<Vertex<string,int>*>
			x =FindVertics<string,int>(test,VertexPredicate);

		cout<<endl<<endl<<x.size()<<endl<<endl;


		typedef bool (*PRE)(const int);
		EdgeFinder<string,int,PRE>::result_type 
			r =	FindEdges<string,int,PRE>(test,EdgePredicate);

		cout<<endl<<endl<<r.size()<<endl<<endl;

		//list<int> ll;

		//ll.push_back(1);
		//bool h = test==test;

		//test.DFS(printInt);

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

#endif
