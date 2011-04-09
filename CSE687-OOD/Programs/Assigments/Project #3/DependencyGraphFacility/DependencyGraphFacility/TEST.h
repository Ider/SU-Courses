#ifndef TEST_H
#define TEST_H
/////////////////////////////////////////////////////////////////////////
//  TEST.h  -  Provide class and method for Graph functionality test   //
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
 * This module provides TestType for using as VertexType of graph.h
 * The TestType works like dictionary, it contains key and value,
 * but overloading operator== only compare the key.
 *
 * class FinderFunctor used for testing globe search algorithm
 * class StrongPrinter used for printing out strong component information
 *
 * Public Interface:
 * =================
 * 	Graph<TestVertex,string> g;
 void StrongPrinter::operator()(Vertex<int,string>& v)
 bool FinderFunctor::operator()(const Vertex<TestVertex,string>& v)
 bool operator==(const TestVertex& a, const TestVertex& b)
 ostream& operator<<(ostream& out, const TestVertex &value)
 *
 * Required Files:
 * ===============
 * Graph.h, GraStrongComponentsph.h,Vertex.h, GraphAlgorithm.h,
 * Display.cpp,Display.cpp, TEST.cpp,TEST.h
**/
#include <string>
#include <iostream>

#include "Graph.h"
#include "Vertex.h"
#include "StrongComponents.h"

//used as VertexType
class TestVertex
{
public:
	TestVertex(int k,std::string v):key(k),value(v){}
	//only compare Key
	bool operator==(const TestVertex& value){return (this->key == value.key);}
	int Key()const{return key;}
	std::string& Value(){return value;}
	std::string Value()const {return value;}

private:
	int key;
	std::string value;
	
};

//stream insertion
std::ostream& operator<<(std::ostream& out, const TestVertex &s);
std::istream& operator>>(std::istream& in, TestVertex &value);
bool operator==(const TestVertex& a, const TestVertex& b);

//for testing globe algorithm
class FinderFunctor
{
public:
	//constructor
	FinderFunctor(int n):num(n){}
	//for testing Vertex searching method
	bool operator()(const Vertex<TestVertex,std::string>& v);
	//for testing Edge searching method
	bool operator()(Vertex<TestVertex,std::string>::pair& edge);
private:
	int num;
};

//used for printing strong components information
class StrongPrinter
{
public:
	//constructor
	StrongPrinter(StrongComponents<TestVertex,std::string>& sc):strong(sc){}
	StrongPrinter(const StrongPrinter& value):strong(value.strong){}
	//print out all strong components information, and vertics in component
	void operator()(Vertex<int,std::string>& v);
private:
	//hide assignment operator
	StrongPrinter& operator=(const StrongPrinter& value){return (*this);}
	//associated strong component object
	StrongComponents<TestVertex,std::string>& strong;
};


#endif
