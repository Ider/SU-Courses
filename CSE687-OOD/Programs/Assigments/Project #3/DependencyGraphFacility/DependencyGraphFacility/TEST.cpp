#include <iostream>
#include <utility>
#include <string>
#include <list>
#include <iomanip>

using namespace std;
#include "TEST.h"
#include "Graph.h"
#include "GraphAlgorithm.h"
#include "Display.h"
#include "StrongComponents.h"
using namespace IderPrinter;



void StrongPrinter::operator()(Vertex<int,string>& v)
{
	cout<<"Vertics of Strong Component "<<	v.Key()<<endl;
	cout<<string(50,'-')<<endl;
	list<TestVertex>& nodes= strong.Components[v.Key()];
	for (list<TestVertex>::iterator it = nodes.begin(); it!=nodes.end(); ++it)
		cout<<(*it)<<endl;
}

bool FinderFunctor::operator()(const Vertex<TestVertex,string>& v)
{
	for (size_t i=0; i<v.Size();++i)
		if (v[i].second->Key().Key() == num)return true;

	return false;
}

bool FinderFunctor::operator()(Vertex<TestVertex,string>::pair& edge)
{
	return edge.second->Key().Key() == num;
}

bool operator==(const TestVertex& a, const TestVertex& b)
{
	return	a.Key() == b.Key();
}

ostream& operator<<(ostream& out, const TestVertex &value)
{
	out << value.Value();
	return out;
}

istream& operator>>(istream& in, TestVertex &value)
{
	std::string& v= value.Value();
	v.clear();
	in >> v;
	return in;
}


#ifdef TEST_TEST

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

bool EdgePredicate(const Vertex<string,int>::pair& e)
{
	return e.first<30;
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

void  GraphTest () {

	Graph<string,int> text ;

	Graph<TestVertex,int> test1;
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


		typedef bool (*PRE)(const Vertex<string,int>::pair& e);
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

void Title(string title, char c='=')
{
	cout<<endl<<title<<endl;
	cout<<string(title.size()*2,c)<<endl;
}

void DoDFS(string title,Graph<TestVertex,string>& g)
{
	Title(title);
	g.DFS(BasicPrinter<TestVertex,string>());
}

void NodesInfo(int from, int to,string edge,Graph<TestVertex,string>& g)
{
	cout<<"Edge:"<<'\t'<<"V"<<from;
	cout<<"----"<<edge<<"---->";
	cout<<"V"<<to<<endl;
	g.AddEdge(TestVertex(from,""),TestVertex(to,""),edge);
}

void  GraphAssignmentTest (Graph<TestVertex,string>& basic)
{
	Title("Add nodes");
	string v="V1";
	cout<<"nodes:V1,V2,V3,V4,V5,V6,V7"<<endl;
	//string v
	for (int i=1; i<8;++i)
	{
		v[1] = '0'+i;
		basic.AddNode(TestVertex(i,v));
	}

	DoDFS("DFS on Basic graph",basic);

	Title("Test copy constructor");
	Graph<TestVertex,string> copy = basic;

	Title("Add Edges to Basic graph");
	NodesInfo(1,4,"e1",basic);
	NodesInfo(1,7,"e2",basic);
	NodesInfo(2,5,"e3",basic);
	NodesInfo(2,7,"e4",basic);
	NodesInfo(3,1,"e5",basic);
	NodesInfo(5,6,"e6",basic);
	NodesInfo(5,7,"e7",basic);
	NodesInfo(6,2,"e8",basic);
	NodesInfo(7,3,"e9",basic);


	DoDFS("DFS on Basic graph",basic);
	DoDFS("DFS on Copied graph",copy);

	Title("Test assignment operator: copy = basic");
	copy = basic;

	DoDFS("DFS on Copied graph",copy);
}

void TestDFS(Graph<TestVertex,string>& g)
{
	cout<<endl<<endl<<endl;
	Title("Test on DSF use NestedPrinter");
	g.DFS(NestedPrinter<TestVertex,string>());
}

void StrongComponentsTest(Graph<TestVertex,string>& g)
{
	Title("Test on strong component");
	StrongComponents<TestVertex,string> sc(g);
	StrongPrinter printer(sc);
	sc.Condensed.DFS(printer);

	Title("DFS on strong component");
	sc.Condensed.DFS(NestedPrinter<int,string>());
}

void AlgorithmTest(Graph<TestVertex,string>& g,	int num = 1)
{
	Title("Test on globe search algorithm");

	cout<<"Get all parent nodes of V"<<num<<endl;
	cout<<string(50,'-')<<endl;
	
	//typedef std::list<Vertex<VertexType,EdgeType>*>
	VertexFinder<TestVertex,string,FinderFunctor>::result_type::iterator vIt;
	VertexFinder<TestVertex,string,FinderFunctor>::result_type vetics=	
		FindVertics<TestVertex,string>(g,FinderFunctor(num));
	for (vIt=vetics.begin(); vIt!= vetics.end(); ++vIt)
		cout<<(*vIt)->Key()<<endl;
	
	cout<<"Get all edges that point to node V"<<num<<endl;
	cout<<string(50,'-')<<endl;

	//std::list<typename Vertex<VertexType, EdgeType>::pair*>
	EdgeFinder<TestVertex,string,FinderFunctor>::result_type::iterator eIt;
	EdgeFinder<TestVertex,string,FinderFunctor>::result_type edges=	
		FindEdges<TestVertex,string>(g,FinderFunctor(num));
	for (eIt = edges.begin();eIt!=edges.end(); ++eIt)
		cout<<(*(*eIt)).first<<endl;
}



void main()
{
	GraphTest();


	Graph<TestVertex,string> g;
	GraphAssignmentTest(g);

	TestDFS(g);
	StrongComponentsTest(g);

	AlgorithmTest(g,5);
}
#endif