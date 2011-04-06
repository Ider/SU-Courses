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

	//Member accessors
	v_value& Key(){return key;}
	size_t& Mask() {return mask;}
	size_t& Lowlink(){return lowlink;}

	//vertics& Children(){return children;}
	pair& operator[](int index){return children[index];}
	void AddEdge(pair edge){children.push_back(edge);}
	void AddEdge(EdgeType e,Vertex<VertexType, EdgeType>* child){ children.push_back(pair(e,child));}
	pair* Find(const EdgeType& e);

	//const methods
	size_t Size()const{return children.size();}
	v_value Key()const{return key;}
	size_t Mask()const {return mask;}
	size_t Lowlink()const {return lowlink;}
	pair operator[](int index)const {return children[index];}

private:
	//Not allow Vertex copy and assignment,
	//because how to copy the edges is not decided, 
	//as the address of Vertex that point to is not clear for the new Vertex
	Vertex(const Vertex<VertexType, EdgeType>& v);
	Vertex<VertexType, EdgeType> operator=(const Vertex<VertexType, EdgeType>& v);

	//data members
	v_value key;
	size_t mask;
	size_t lowlink;
	vertics children;

};

//////////////////////////////////////////////////////////////////////////
//Find the EdgeType value in the edges of the vertex,
//If found, return the address of the pair, otherwise return NULL.
//For Find method works successfully, the VertexType must have implemented operator==
template <typename VertexType, typename EdgeType> //template mark
typename Vertex<VertexType, EdgeType>::pair* //return type
	Vertex<VertexType, EdgeType>::Find(const EdgeType& e) //method signature
{
	Vertex<VertexType, EdgeType>::vertics::iterator it;
	for (it = children.begin(); it != children.end(); ++it)
		if ((*it).first == e)break;

	if (it != children.end())
		return &(*it);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//Destructor
template <typename VertexType, typename EdgeType>
Vertex<VertexType,EdgeType>::~Vertex()
{
	children.clear();
}

#endif