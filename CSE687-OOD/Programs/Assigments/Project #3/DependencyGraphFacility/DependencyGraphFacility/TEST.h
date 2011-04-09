#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>

#include "Graph.h"
#include "Vertex.h"
#include "StrongComponents.h"

class TestVertex
{
public:
	TestVertex(int k,std::string v):key(k),value(v){}
	bool operator==(const TestVertex& value){return (this->key == value.key);}
	int Key()const{return key;}
	std::string& Value(){return value;}
	std::string Value()const {return value;}

private:
	int key;
	std::string value;
	
};

std::ostream& operator<<(std::ostream& out, const TestVertex &s);
std::istream& operator>>(std::istream& in, TestVertex &value);
bool operator==(const TestVertex& a, const TestVertex& b);

class FinderFunctor
{
public:
	FinderFunctor(int n):num(n){}
	bool operator()(const Vertex<TestVertex,std::string>& v);
	bool operator()(Vertex<TestVertex,std::string>::pair& edge);
private:
	int num;
};



class StrongPrinter
{
public:
	StrongPrinter(StrongComponents<TestVertex,std::string>& sc):strong(sc){}
	StrongPrinter(const StrongPrinter& value):strong(value.strong){}
	void operator()(Vertex<int,std::string>& v);
private:
	StrongPrinter& operator=(const StrongPrinter& value){return (*this);}
	StrongComponents<TestVertex,std::string>& strong;
};


#endif
