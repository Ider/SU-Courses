#ifndef TEMPLATE_STRONGCOMPONENTS_H
#define  TEMPLATE_STRONGCOMPONENTS_H

#include "Graph.h"

template <typename VertexType, typename EdgeType> class Graph;

template <typename VertexType, typename EdgeType>
class StrongComponents
{
public:
	StrongComponents(Graph<VertexType,EdgeType>& orl);
	Graph<int,EdgeType> Condensed;
	std::map<int,std::list<VertexType>> Components;

private:
	void StrongAnalyzer();
	void StrongAnalyzer(Vertex<VertexType, EdgeType>& top);

	std::list<Vertex<VertexType, EdgeType>*> stack;
	bool Contain(const VertexType& v);
	Graph<VertexType,EdgeType> original;
	int order;
};


template <typename VertexType, typename EdgeType> 
StrongComponents<VertexType,EdgeType>::StrongComponents(Graph<VertexType,EdgeType>& orl)
	:original(orl),order(0)
{StrongAnalyzer();}

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

	for (size_t i=0; i<top.Size();)
	{
		Vertex<VertexType, EdgeType>& v =*(top[i].second);
		if (v.Mask()==0)
		{
			StrongAnalyzer(v);
			top.Lowlink()= min(top.Lowlink(),v.Lowlink());
		}
		else if (top.Mask() > v.Mask())
			if (Contain(v.Key()))
				top.Lowlink() = min(top.Lowlink(),v.Mask());
	}

	if (top.Mask() == top.Lowlink())
	{
		size_t num = top.Mask();
		Condensed.AddNode(num);

		Graph<VertexType,EdgeType>::vertex* ver = stack.back();
		while (top.Mask() <= ver->Mask())
		{
			Components[num].push_back(ver->Key());
			stack.pop_back();
			if(stack.size()>0)
				ver = stack.back();
			else
				break;
		} 
	}
}


#endif