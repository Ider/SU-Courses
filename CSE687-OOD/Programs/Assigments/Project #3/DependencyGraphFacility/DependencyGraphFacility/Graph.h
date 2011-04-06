#ifndef TEMPLATE_GRAPH_H
#define  TEMPLATE_GRAPH_H

#include <list>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include "Vertex.h"
#include "StrongComponents.h"

template <typename VertexType, typename EdgeType> class StrongComponents;

template <typename VertexType, typename EdgeType>
class Graph
{
public:
	typedef VertexType v_value;
	typedef EdgeType e_value;
	typedef Vertex<v_value, e_value> vertex;
	typedef std::list<vertex*> container;

	Graph(){};
	Graph(const Graph<VertexType,EdgeType>& g);
	~Graph();
	Graph<VertexType,EdgeType>& operator=(const Graph<VertexType,EdgeType>& g);

	void AddNode(const VertexType& v, bool addFront=false);
	bool Contains(const VertexType& v);
	bool AddEdge(const VertexType& from, const VertexType& toV, const EdgeType& toE);
	int AddEdge(const VertexType& from, std::vector<std::pair<VertexType, EdgeType>>& tos);

	template<typename Func> void DFS(Func func, bool preorder = true);

	friend StrongComponents<VertexType,EdgeType>;

private:
	template<typename Func> void DFS(Func func, Vertex<VertexType, EdgeType>& top, bool preorder = true);
	void ClearMask(bool clearLowlink = false);
	Vertex<VertexType, EdgeType>* Find(const VertexType& v);
	void CopyAdjacentList(const container& old);
	void ClearAdjacentList();

	container adjList;
};

//////////////////////////////////////////////////////////////////////////
//Copy Constructor
template <typename VertexType, typename EdgeType>
Graph<VertexType, EdgeType>::Graph(const Graph<VertexType,EdgeType>& g)
{
	CopyAdjacentList(g.adjList);
}

//////////////////////////////////////////////////////////////////////////
//Assignment Operator
template <typename VertexType, typename EdgeType>
Graph<VertexType,EdgeType>& 
	Graph<VertexType, EdgeType>::operator=(const Graph<VertexType,EdgeType>& g)
{
	if (this == &g)return *this;

	ClearAdjacentList();
	CopyAdjacentList(g.adjList);
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//Destructor
template <typename VertexType, typename EdgeType>
Graph<VertexType, EdgeType>::~Graph()
{
	ClearAdjacentList();
}

//////////////////////////////////////////////////////////////////////////
//Indicate whether the graph contains a node with VertexType value v.
template <typename VertexType, typename EdgeType>
bool Graph<VertexType, EdgeType>::Contains(const VertexType& v)
{
	return Find(v) != 0;
}

//////////////////////////////////////////////////////////////////////////
//Add node to adjacent list.
//If node already exists, an exception will be thrown.
template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::AddNode(const VertexType& v,bool addFront)
{
	if (Contains(v))
		throw std::string("The node with such value already exists.");
	else
	{
		if (addFront)
			adjList.push_front(new Vertex<VertexType, EdgeType>(v));
		else
			adjList.push_back(new Vertex<VertexType, EdgeType>(v));
	}
}

//////////////////////////////////////////////////////////////////////////
//This method connect "from" node to all nodes in "tos".
//If "from" node does not exist, an exception will be thrown.
//If the connection built between "from" and "to", or it already exists
//(it would not be built again), the node in "tos" will be removed.
//All nodes that not exist in graph will be returned by "tos".
//return the number of connections between "from" and "tos".
template <typename VertexType, typename EdgeType>
int Graph<VertexType, EdgeType>::AddEdge(const VertexType& from, std::vector<std::pair<VertexType, EdgeType>>& tos)
{
	Vertex<VertexType, EdgeType>* node = Find(from);
	if (node==0)
		throw std::string("The node with such value does not exist.");

	Vertex<VertexType, EdgeType>& v=*(node);
	std::vector<std::pair<VertexType, EdgeType>> notExist;
	size_t succeed = 0;

	for (size_t i = 0;i < tos.size(); ++i)
	{
		std::pair<VertexType, EdgeType>& to = tos[i];
		//edge to Vertex itself is allowed
		//otherwise, uncomment following codes
		//if(from == to.first)continue;

		node = Find(to.first);
		if (node==0)
			notExist.push_back(to);
		else
		{
			//any of edges in a vertex should not have the same EdgeType value
			//but I do not mind that vertex has more than one edges point to
			//the same other vertex with different EdgeType value.
			if (!v.Find(to.second))
			{
				v.AddEdge(to.second, node);
				++succeed;
			}
		}
	}

	tos.swap(notExist);
	return succeed;
}

//////////////////////////////////////////////////////////////////////////
//Build connection "from" and "to"
template <typename VertexType, typename EdgeType>
bool Graph<VertexType, EdgeType>::AddEdge(const VertexType& from, const VertexType& toV, const EdgeType& toE)
{
	std::pair<VertexType, EdgeType> to(toV,toE);
	std::vector<std::pair<VertexType, EdgeType>> tos(1,to);
	return AddEdge(from,tos)>0?true:false;
}

template <typename VertexType, typename EdgeType>
template<typename Func> 
void Graph<VertexType, EdgeType>::DFS(Func func, bool preorder)
{
	ClearMask();
	typename Graph<VertexType, EdgeType>::container::iterator node;
	for (node = adjList.begin(); node != adjList.end(); ++node)
	{
		Vertex<VertexType, EdgeType>& v = *(*node);
		if (v.Mask()==0)
			DFS(func,v,preorder);
	}

}

template <typename VertexType, typename EdgeType>
template<typename Func> 
void Graph<VertexType, EdgeType>::DFS(Func func, Vertex<VertexType, EdgeType>& top, bool preorder)
{
	top.Mask()=-1;//set to max value of unsigned int
	if (preorder)func(top);//pre-order traversal

	for (size_t i = 0; i<top.Size(); ++i)
	{
		Vertex<VertexType, EdgeType>& v =*(top[i].second);
		if (v.Mask()==0)
			DFS(func,v,preorder);
	}

	if (!preorder)func(top);//post-order traversal
}


template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::ClearMask(bool clearLowlink)
{
	Graph<VertexType, EdgeType>::container::iterator node;
	for (node = adjList.begin(); node != adjList.end(); ++ node)
	{
		if(clearLowlink)(*node)->Lowlink() =0;
		(*node)->Mask() = 0;
	}
}

template <typename VertexType, typename EdgeType>
Vertex<VertexType, EdgeType>* Graph<VertexType, EdgeType>::Find(const VertexType& v)
{
	Graph<VertexType, EdgeType>::container::iterator node = adjList.begin();
	for (  ;node!=adjList.end();++node)
		if ((*node)->Key() == v)return *node;

	return 0;
}


template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::CopyAdjacentList(const container& old)
{
	typedef Vertex<VertexType,EdgeType>* vPoint;
	std::map<vPoint,vPoint> mapper; //map old address to new address

	Graph<VertexType, EdgeType>::container::const_iterator node;
	//copy adjacent list

	for (node = old.begin(); node !=old.end(); ++node)
	{
		VertexType v = (*node)->Key();
		vPoint newAddress= new Vertex<VertexType,EdgeType>(v);
		adjList.push_back(newAddress);
		mapper[*node]=newAddress;
	}

	//copy edges
	for (node = old.begin(); node !=old.end(); ++node)
	{
		Vertex<VertexType, EdgeType>& vOld = *(*node);
		Vertex<VertexType, EdgeType>& vNew = *(mapper[*node]);
		for (size_t i = 0; i< vOld.Size(); ++i)
		{
			vNew.AddEdge(vOld[i].first,mapper[vOld[i].second]);
		}
	}
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::ClearAdjacentList()
{
	Graph<VertexType, EdgeType>::container::iterator node;
	for (node = adjList.begin(); node != adjList.end(); ++ node)
	{
		delete (*node);
	}
	adjList.clear();
}




#endif