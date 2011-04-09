/////////////////////////////////////////////////////////////////////////
//  Executeive.h  -  Execute each functionality in graph to test it    //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #3	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////

#include <string>
using namespace std;

#include "Executive.h"
#include "GraphAlgorithm.h"
#include "Display.h"
#include "StrongComponents.h"

using namespace IderPrinter;

//////////////////////////////////////////////////////////////////////////
//Run test
void Executive::Run()
{
	Graph<TestVertex,string> g;
	GraphAssignmentTest(g);

	TestDFS(g);
	StrongComponentsTest(g);

	AlgorithmTest(g,7);
}

//////////////////////////////////////////////////////////////////////////
//Display test stub title
void Executive::Title(string title, char c)
{
	cout<<endl<<title<<endl;
	cout<<string(title.size()*2,c)<<endl;
}

//////////////////////////////////////////////////////////////////////////
//Use BasicPrinter class object to run DFS of graph
void Executive::DoDFS(string title,Graph<TestVertex,string>& g)
{
	Title(title);
	g.DFS(BasicPrinter<TestVertex,string>());
}

//////////////////////////////////////////////////////////////////////////
//Show edge information and add the edge to graph
void Executive::NodesInfo(int from, int to,string edge,Graph<TestVertex,string>& g)
{
	cout<<"Edge:"<<'\t'<<"V"<<from;
	cout<<"----"<<edge<<"---->";
	cout<<"V"<<to<<endl;
	g.AddEdge(TestVertex(from,""),TestVertex(to,""),edge);
}

//////////////////////////////////////////////////////////////////////////
//Test graph copy constructor and assignment operator
void Executive:: GraphAssignmentTest (Graph<TestVertex,string>& basic)
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

//////////////////////////////////////////////////////////////////////////
//Use NestedPrinter to test DFS of Graph
void Executive::TestDFS(Graph<TestVertex,string>& g)
{
	cout<<endl<<endl<<endl;
	Title("Test on DSF use NestedPrinter");
	g.DFS(NestedPrinter<TestVertex,string>());
}

//////////////////////////////////////////////////////////////////////////
//Test strong component generation
void Executive::StrongComponentsTest(Graph<TestVertex,string>& g)
{
	Title("Test on strong component");
	StrongComponents<TestVertex,string> sc(g);
	StrongPrinter printer(sc);
	sc.Condensed.DFS(printer);

	Title("DFS on strong component");
	sc.Condensed.DFS(NestedPrinter<int,string>());
}

//////////////////////////////////////////////////////////////////////////
//Test globe algorithm
void Executive::AlgorithmTest(Graph<TestVertex,string>& g,	int num)
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


/************************************************************************/
/* Test Stub                                                                     */
/************************************************************************/
#ifdef EXECUTIVE_TEST

void main()
{
	Executive exe;
	Graph<TestVertex,string> g;
	// test graph assignment
	exe.GraphAssignmentTest(g);

	// test deep first search
	exe.TestDFS(g);

	// test strong component
	exe.StrongComponentsTest(g);

	// test globe algorithm
	exe.AlgorithmTest(g,5);
}

#endif

