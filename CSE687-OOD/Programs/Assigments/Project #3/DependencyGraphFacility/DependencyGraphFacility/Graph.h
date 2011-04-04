#ifndef TEMPLATE_GRAPH_H
#define  TEMPLATE_GRAPH_H

#include <map>
#include <vector>
#include <utility>
#include <string>
#include "Vertex.h"

template <typename VertexType, typename EdgeType> class Graph
{
public:
	typedef VertexType v_value;
	typedef EdgeType e_value;
	typedef Vertex<v_value, e_value> vertex;
	typedef std::map<v_value,vertex*> v_map;

	Graph(){};
	Graph(const Graph<VertexType,EdgeType>& g);
	~Graph();
	Graph<VertexType,EdgeType>& operator=(const Graph<VertexType,EdgeType>& g);

	void AddNode(const VertexType& v);
	bool Contains(const VertexType& v);
	bool AddEdge(const VertexType& from, const VertexType& toV, const EdgeType& toE);
	int AddEdge(const VertexType& from, std::vector<std::pair<VertexType, EdgeType>>& tos);

	template<typename Func> void DFS(Func func, bool preorder = true);
private:
	template<typename Func> void DFS(Func func, Vertex<VertexType, EdgeType>& top, bool preorder = true);
	void ClearMask();

	void CopyAdjacentList(const v_map& old);
	void ClearAdjacentList();
	/*I assume that iterator operations of map are very fast, so that traversal 
	of adjacent list is efficient.
	Otherwise, I would use structure like this:
	std::map<v_value,int> auxiliary;	vector<vertex*> adjList;
	auxiliary is only used to find node by value quickly, and it is easy to do node remove
	*/
	v_map adjList;

};



template <typename VertexType, typename EdgeType>
Graph<VertexType, EdgeType>::Graph(const Graph<VertexType,EdgeType>& g)
{
	CopyAdjacentList(g.adjList);
}


template <typename VertexType, typename EdgeType>
Graph<VertexType,EdgeType>& 
Graph<VertexType, EdgeType>::operator=(const Graph<VertexType,EdgeType>& g)
{
	if (this == &g)return *this;

	ClearAdjacentList();
	CopyAdjacentList(g.adjList);
	return *this;
}

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
	return adjList.find(v)!=adjList.end();
}

//////////////////////////////////////////////////////////////////////////
//Add node to adjacent list.
//If node already exists, an exception will be thrown.
template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::AddNode(const VertexType& v)
{
	if (Contains(v))
		throw std::string("The node with such value already exists.");
	else
		adjList[v]=new Vertex<VertexType, EdgeType>(v);
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
	Graph<VertexType, EdgeType>::v_map::iterator node = adjList.find(from);
	if (node==adjList.end())
		throw std::string("The node with such value does not exist.");

	Vertex<VertexType, EdgeType>& v=*(node->second);
	std::vector<std::pair<VertexType, EdgeType>> notExist;
	size_t succeed = 0;

	for (size_t i = 0;i < tos.size(); ++i)
	{
		std::pair<VertexType, EdgeType>& to = tos[i];
		node = adjList.find(to.first);
		if (node==adjList.end())
			notExist.push_back(to);

		else
		{
			++succeed;
			if (!v.Find(to.second)) v.AddEdge(to.second, node->second);
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
	Graph<VertexType, EdgeType>::v_map::iterator node;
	for (node = adjList.begin(); node != adjList.end(); ++node)
	{
		Vertex<VertexType, EdgeType>& v = *(node->second);
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
	
	 for (size_t i = 0; i<top.size(); ++i)
	 {
		 Vertex<VertexType, EdgeType>& v =*(top[i].second);
		 DFS(func,v,preorder);
	 }

	 if (!preorder)func(top);//post-order traversal
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::ClearMask()
{
	Graph<VertexType, EdgeType>::v_map::iterator node;
	for (node = adjList.begin(); node != adjList.end(); ++ node)
	{
		node->second->Mask() = 0;
	}
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::CopyAdjacentList(const v_map& old)
{
	typedef Vertex<VertexType,EdgeType>* vPoint;
	std::map<vPoint,vPoint> mapper; //map old address to new address

	Graph<VertexType, EdgeType>::v_map::const_iterator node;
	//copy adjacent list

	for (node = old.begin(); node !=old.end(); ++node)
	{
		VertexType v = node->first;
		vPoint newAddress= new Vertex<VertexType,EdgeType>(v);
		adjList[v] = newAddress;
		mapper[node->second]=newAddress;
	}

	//copy edges
	for (node = old.begin(); node !=old.end(); ++node)
	{
		Vertex<VertexType, EdgeType>& vOld = *(node->second);
		Vertex<VertexType, EdgeType>& vNew = *(mapper[node->second]);
		for (size_t i = 0; i< vOld.size(); ++i)
		{
			vNew.AddEdge(vOld[i].first,mapper[vOld[i].second]);
		}
	}
}

template <typename VertexType, typename EdgeType>
void Graph<VertexType, EdgeType>::ClearAdjacentList()
{
	Graph<VertexType, EdgeType>::v_map::iterator node;
	for (node = adjList.begin(); node != adjList.end(); ++ node)
	{
		delete node->second;
	}
	adjList.clear();
}

#endif