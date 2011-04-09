#ifndef EXECUTEIVE_H
#define EXECUTEIVE_H
/////////////////////////////////////////////////////////////////////////
//  Executeive.h  -  Execute each functionality in graph to test it    //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #3	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module is used to test graph functionality, it use user-defined
 * object as VertexType, test on each functionality of graph, and also test
 * globe function of search algorithm
 *
 * Public Interface:
 * =================
 * Executive exe;
 * exe.GraphAssignmentTest(g);
 * exe.TestDFS(g);
 * exe.StrongComponentsTest(g);
 * exe.AlgorithmTest(g,5);
 *
 * Required Files:
 * ===============
 * Executive.h, Executive.cpp, GraphAlgorithm.h,
 * Display.h, Display.cpp, StrongComponents.h, TEST.h, TEST.cpp
 */

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