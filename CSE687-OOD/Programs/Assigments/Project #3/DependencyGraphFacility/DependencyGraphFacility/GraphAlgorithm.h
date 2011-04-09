#ifndef TEMPLATE_GRAPHALGORITHM_H
#define TEMPLATE_GRAPHALGORITHM_H

/////////////////////////////////////////////////////////////////////////
//  GraphAlgorithm.h  -  Provide Graph search algorithm			       //
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
 * This module provides two functors and two methods for graph search.
 * One pair of functor and method is used for vertex search, and the other
 * pair is used for edge search.
 * 
 * The method could accept a predicate, a predicate is a function pointer or 
 * functor that accept a Vertex or Edge (pair<EdgeType, Vertex*>), and return bool value.
 * The method will wrap predicate into functor, and pass the functor to graph DFS method.
 *
 * The functor will check each vertex or edge, pass the vertex or edge to predicate to see
 * whether it meat the requirement of predicate. If so add it to result collection of funtor.
 *
 * Finally, return collection result of functor.
 *
 * Public Interface:
 * =================
 * Graph<TestVertex,int> test;
 * test.AddNode(string("444"));
 * test.AddEdge("111","222",12);
 * test.DFS(Printer());
 *
 * Required Files:
 * ===============
 * StrongComponents.h, Graph.h
**/

#include "Graph.h"

/************************************************************************/
/* Graph algorithm helper functors                                      */
/************************************************************************/


template <typename VertexType, typename EdgeType, typename Predicate>
class VertexFinder
{
public:
	//result type
	typedef std::list<Vertex<VertexType,EdgeType>*> result_type;
	
	//constructors and destructor
	VertexFinder(Predicate& pr):pred(pr){}
	VertexFinder(const VertexFinder<VertexType,EdgeType,Predicate>& value)
		:pred(value.pred),result(value.result){}
	~VertexFinder(){Clear();}

	//functor operator
	void operator()(Vertex<VertexType,EdgeType>& v);
	
	//clear result
	void Clear(){result.clear();}
	//return search result
	result_type& Result(){return result;}
private:
	//predicate function operator
	Predicate& pred;
	//result collection
	result_type result;
};

//////////////////////////////////////////////////////////////////////////
//Test whether the vertex meat the Predicate requirement, if so add to result collection
template <typename VertexType, typename EdgeType, typename Predicate>
void VertexFinder<VertexType,EdgeType,Predicate>::operator()(Vertex<VertexType,EdgeType>& v)
{
	//when the vertex satisfy the predicate, add its address to result
	if (pred(v))
		result.push_back(&v);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

template <typename VertexType, typename EdgeType, typename Predicate>
class EdgeFinder
{
public:
	//result type
	typedef std::list<typename Vertex<VertexType, EdgeType>::pair*> result_type;

	//constructors and destructor
	EdgeFinder(Predicate& pr):pred(pr){}
	EdgeFinder(const VertexFinder<VertexType,EdgeType,Predicate>& value)
		:pred(value.pred),result(value.result){}
	~EdgeFinder(){Clear();}

	//functor operator
	void operator()(Vertex<VertexType,EdgeType>& v);

	//clear result
	void Clear(){result.clear();}
	//return search result
	result_type& Result(){return result;}
private:
	//predicate function operator
	Predicate& pred;
	result_type result;
};

//////////////////////////////////////////////////////////////////////////
//Test whether the edge meat the Predicate requirement, if so add to result collection
template <typename VertexType, typename EdgeType, typename Predicate>
void EdgeFinder<VertexType,EdgeType,Predicate>::operator()(Vertex<VertexType,EdgeType>& v)
{
	for (size_t i=0; i<v.Size(); ++i)
	{
		Vertex<VertexType,EdgeType>::pair& edge = v[i];
		if (pred(edge))result.push_back(&edge);
	}
}




/************************************************************************/
/* Graph find algorithm                                                 */
/************************************************************************/


//////////////////////////////////////////////////////////////////////////
//Vertex search algorithm, find all vertics that match Predicate requirement
template <typename VertexType, typename EdgeType, typename Predicate>
inline typename VertexFinder<VertexType, EdgeType, Predicate>::result_type
	FindVertics(Graph<VertexType, EdgeType>& graph, Predicate pred)
{
	VertexFinder<VertexType, EdgeType, Predicate> finder(pred);
	graph.DFS(finder);
	return finder.Result();
}

//////////////////////////////////////////////////////////////////////////
//Vertex search algorithm, find all vertics that match Predicate requirement
template <typename VertexType, typename EdgeType, typename Predicate>
inline typename EdgeFinder<VertexType, EdgeType,Predicate>::result_type
	FindEdges(Graph<VertexType, EdgeType>& graph, Predicate pred)
{
	EdgeFinder<VertexType, EdgeType, Predicate> finder(pred);
	graph.DFS(finder);
	return finder.Result();
}

#endif
