#ifndef TEMPLATE_GRAPHALGORITHM_H
#define TEMPLATE_GRAPHALGORITHM_H

#include "Graph.h"

/************************************************************************/
/* Graph algorithm helper functors                                      */
/************************************************************************/


template <typename VertexType, typename EdgeType, typename Predicate>
class VertexFinder
{
public:
	typedef std::list<Vertex<VertexType,EdgeType>*> result_type;
	//constructors and destructor
	VertexFinder(Predicate& pr):pred(pr){}
	VertexFinder(const VertexFinder<VertexType,EdgeType,Predicate>& value)
		:pred(value.pred),result(value.result){}
	~VertexFinder(){Clear();}

	void operator()(Vertex<VertexType,EdgeType>& v);

	void Clear(){result.clear();}
	result_type& Result(){return result;}
private:
	Predicate& pred;
	result_type result;
};

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
	typedef std::list<typename Vertex<VertexType, EdgeType>::pair*> result_type;

	//constructors and destructor
	EdgeFinder(Predicate& pr):pred(pr){}
	EdgeFinder(const VertexFinder<VertexType,EdgeType,Predicate>& value)
		:pred(value.pred),result(value.result){}
	~EdgeFinder(){Clear();}

	void operator()(Vertex<VertexType,EdgeType>& v);

	void Clear(){result.clear();}
	result_type& Result(){return result;}
private:
	Predicate& pred;
	result_type result;
};

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

template <typename VertexType, typename EdgeType, typename Predicate>
inline typename VertexFinder<VertexType, EdgeType, Predicate>::result_type
	FindVertics(Graph<VertexType, EdgeType>& graph, Predicate pred)
{
	VertexFinder<VertexType, EdgeType, Predicate> finder(pred);
	graph.DFS(finder);
	return finder.Result();
}

template <typename VertexType, typename EdgeType, typename Predicate>
inline typename EdgeFinder<VertexType, EdgeType,Predicate>::result_type
	FindEdges(Graph<VertexType, EdgeType>& graph, Predicate pred)
{
	EdgeFinder<VertexType, EdgeType, Predicate> finder(pred);
	graph.DFS(finder);
	return finder.Result();
}

#endif
