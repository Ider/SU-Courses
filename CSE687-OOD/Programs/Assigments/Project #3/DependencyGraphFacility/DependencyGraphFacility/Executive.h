#ifndef EXECUTEIVE_H
#define EXECUTEIVE_H

#include <string>
#include "Graph.h"
#include "TEST.h"


class Executive
{
public:
	//Run test
	void Run();
	//Display test stub title
	void Title(std::string title, char c='=');
	//Use BasicPrinter class object to run DFS of graph
	void DoDFS(std::string title,Graph<TestVertex,std::string>& g);
	//Show edge information and add the edge to graph	
	void NodesInfo(int from, int to,std::string edge,Graph<TestVertex,std::string>& g);
	//Test graph copy constructor and assignment operator
	void GraphAssignmentTest (Graph<TestVertex,std::string>& basic);
	//Use NestedPrinter to test DFS of Graph
	void TestDFS(Graph<TestVertex,std::string>& g);
	//Test strong component generation
	void StrongComponentsTest(Graph<TestVertex,std::string>& g);
	//Test globe algorithm
	void AlgorithmTest(Graph<TestVertex,std::string>& g,	int num = 1);
};
#endif