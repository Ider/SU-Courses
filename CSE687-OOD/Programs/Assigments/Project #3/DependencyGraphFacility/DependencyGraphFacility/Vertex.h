#ifndef TEMPLATE_VERTEX_H
#define  TEMPLATE_VERTEX_H

#include <vector>
#include <utility>

template <typename VertexType, typename EdgeType> class Vertex
{
public:
	typedef VertexType v_value;
	typedef EdgeType e_value;
	typedef Vertex<VertexType, EdgeType> vertex;
	typedef std::vector<std::pair<e_value,vertex*>> vertics;
	typedef std::pair<e_value,vertex*> pair;

	Vertex(VertexType k):key(k){}
	~Vertex();
	size_t Size(){return children.size();}
	v_value& Key(){return key;}
	size_t& Mask() {return mask;}
	size_t& Lowlink(){return lowlink;}
	//vertics& Children(){return children;}
	pair& operator[](int index){return children[index];}
	void AddEdge(pair edge){children.push_back(edge);}
	void AddEdge(EdgeType e,Vertex<VertexType, EdgeType>* child){ children.push_back(pair(e,child));}

	pair* Find(EdgeType e);

private:
	v_value key;
	size_t mask;
	size_t lowlink;
	vertics children;

};

template <typename VertexType, typename EdgeType> //template mark
typename Vertex<VertexType, EdgeType>::pair* //return type
	Vertex<VertexType, EdgeType>::Find(EdgeType e) //method signature
{
	Vertex<VertexType, EdgeType>::vertics::iterator it;
	for (it = children.begin(); it != children.end(); ++it)
		if ((*it).first==e)break;

	if (it == children.end())return NULL;
	return &(*it);
}

template <typename VertexType, typename EdgeType>
Vertex<VertexType,EdgeType>::~Vertex()
{
	children.clear();
}

#endif