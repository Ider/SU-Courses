#ifndef TEMPLATE_STRONGCOMPONENTS_H
#define  TEMPLATE_STRONGCOMPONENTS_H

#include "Graph.h"

template <typename VertexType, typename EdgeType> class Graph;

template <typename VertexType, typename EdgeType>
class StrongComponents
{
public:
	StrongComponents(Graph<VertexType,EdgeType>& orl);
	StrongComponents(const StrongComponents<VertexType,EdgeType>& value);
	
	Graph<int,EdgeType> Condensed;
	std::map<int,std::list<VertexType>> Components;

	void Rebuild();
private:
	void StrongAnalyzer();
	void StrongAnalyzer(Vertex<VertexType, EdgeType>& top);

	void EdgesAnalyzer();
	void EdgesAnalyzer(Vertex<VertexType, EdgeType>& top);

	bool Contain(const VertexType& v);

	std::list<Vertex<VertexType, EdgeType>*> stack;
	Graph<VertexType,EdgeType>& original;
	int order;

	//Hide assignment, as original graph is not allowed to modify inside
	StrongComponents<VertexType,EdgeType>& 
		operator=(const StrongComponents<VertexType,EdgeType>& value);
};

//////////////////////////////////////////////////////////////////////////
//Constructor, set the original graph for analyze the strong components
template <typename VertexType, typename EdgeType> 
StrongComponents<VertexType,EdgeType>::StrongComponents(Graph<VertexType,EdgeType>& orl)
	:original(orl),order(0)
{
	StrongAnalyzer();
	EdgesAnalyzer();
}

//////////////////////////////////////////////////////////////////////////
//Copy constructor
template <typename VertexType, typename EdgeType> 
StrongComponents<VertexType,EdgeType>::StrongComponents(const StrongComponents<VertexType,EdgeType>& value)
	:original(value.original),order(value.order)
	,Condensed(value.Condensed),Components(value.Components)
{}

//////////////////////////////////////////////////////////////////////////
//Reanalyze the graph that assigned to the StrongComponents object in construct time,
//build new strong components information.
template <typename VertexType, typename EdgeType> 
void StrongComponents<VertexType,EdgeType>::Rebuild()
{
	//clear all data
	Condensed = Graph<int,EdgeType>();
	Components.clear();
	stack.clear();
	order=0;

	StrongAnalyzer();
	EdgesAnalyzer();
}

template <typename VertexType, typename EdgeType> 
bool StrongComponents<VertexType,EdgeType>::Contain(const VertexType& v)
{
	std::list<Graph<VertexType,EdgeType>::vertex*>::iterator it = stack.begin();
	for (  ; it !=stack.end(); ++it)
		if (v ==(*it)->Key())return true;

	return false;
}

template <typename VertexType, typename EdgeType>
void StrongComponents<VertexType, EdgeType>::StrongAnalyzer()
{
	original.ClearMask(true);
	order = 0;

	typename Graph<VertexType, EdgeType>::container::iterator node;
	for (node = original.adjList.begin(); node != original.adjList.end(); ++node)
	{
		Vertex<VertexType, EdgeType>& v = *(*node);
		if (v.Mask()==0)
			StrongAnalyzer(v);
	}
}

template <typename VertexType, typename EdgeType>
void StrongComponents<VertexType, EdgeType>::StrongAnalyzer(Vertex<VertexType, EdgeType>& top)
{
	++order;
	top.Mask() = order;
	top.Lowlink() = order;
	stack.push_back(&top);

	//Strong analyze all children nodes
	for (size_t i=0; i<top.Size(); ++i)
	{
		Vertex<VertexType, EdgeType>& v =*(top[i].second);
		if (v.Mask()==0)
		{
			StrongAnalyzer(v);
			top.Lowlink()= std::min(top.Lowlink(),v.Lowlink());
		}
		else if (top.Mask() > v.Mask())
			if (Contain(v.Key()))
				top.Lowlink() = std::min(top.Lowlink(),v.Mask());
	}

	//pop up the node in the same strong components
	if (top.Mask() == top.Lowlink())
	{
		size_t num = top.Mask();
		Condensed.AddNode(num,true);

		Graph<VertexType,EdgeType>::vertex* ver = stack.back();
		while (top.Mask() <= ver->Mask())
		{
			Components[num].push_front(ver->Key());
			stack.pop_back();
			if(stack.size()>0)
				ver = stack.back();
			else
				break;
		} 
	}
}

template <typename VertexType, typename EdgeType>
void StrongComponents<VertexType, EdgeType>::EdgesAnalyzer()
{
	original.ClearMask();

	typename Graph<VertexType, EdgeType>::container::iterator node;
	for (node = original.adjList.begin(); node != original.adjList.end(); ++node)
	{
		Vertex<VertexType, EdgeType>& v = *(*node);
		if (v.Mask()==0)
			EdgesAnalyzer(v);
	}
}

template <typename VertexType, typename EdgeType>
void StrongComponents<VertexType, EdgeType>::EdgesAnalyzer(Vertex<VertexType, EdgeType>& top)
{
	top.Mask() = -1;
	if (top.Size()<=0)return;

	std::vector<std::pair<int,EdgeType>> edges;
	for (size_t i=0; i<top.Size(); ++i)
	{
		Vertex<VertexType, EdgeType>& v =*(top[i].second);
		//if top and its child has different Lowlink num,
		//it mean they are in the different strong components
		//so connect the vertics in the condensed graph
		if (top.Lowlink() != v.Lowlink())
			edges.push_back(std::pair<int,EdgeType>(v.Lowlink(),top[i].first));

		//Travel child node
		if (v.Mask()==0)
			EdgesAnalyzer(v);
	}

	//if edges is not empty, add this edges to condensed graph
	if (edges.size()>0)
		Condensed.AddEdge(top.Lowlink(),edges);

}


#endif