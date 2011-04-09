/////////////////////////////////////////////////////////////////////////
//  Dispaly.h  -  Provide functors for Graph DFS method		           //
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
 * This module provides two Meta printer functor for printing meta data 
 * information of meta data graph.
 * It also provides two template printer functor for generic printing format.
 *
 * For any VertexType and EdgeType want use template printer, it must 
 * overloading operator<<.
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
 * Graph.h, Graph.h,Display.h, Display.cpp
**/
#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iomanip>
#include "Graph.h"
//class StrongComponentPrinter
namespace IderPrinter
{
	typedef	Vertex<std::string,std::string>& v_ref;

	//simply print meat data information
	class MetaPrinter
	{
	public:
		//functor operation
		void operator()(const v_ref v);
	private:
		//format long file path information
		void FormatLongString(const std::string& str);
		//print out table title
		void PrintTableTitle();
	};


	//print out meta data info by nested format
	class MetaNestedPrinter
	{
	public:
		//functor operation
		void operator()(v_ref v);
	private:
		//get current vertex level info
		size_t GetLevel(v_ref v);
		//add level by 1, and set to children vertics
		void SetChildrenLevel(v_ref v);

	};

	//use nested format to print vertex
	//each child vertex is below its parent, and have enough indent
	template<typename VertexType,typename EdgeType>
	class NestedPrinter
	{
	public:
		//functor operation, add level num tabs before vertex information
		void operator()(Vertex<VertexType,EdgeType>& v)
		{
			int level = GetLevel(v);
			//if (level == 0) cout<<endl;

			string tab(level,'\t');
			cout<<tab<<"{Vertex} "<<v.Key()<<endl;

			SetChildrenLevel(v);
		}
	private:
		//get current vertex level info
		size_t GetLevel(Vertex<VertexType,EdgeType>& v)
		{
			return v.Mask()>>8;	
		}
		//add level by 1, and set to children vertics
		void SetChildrenLevel(Vertex<VertexType,EdgeType>& v)
		{
			int level = (GetLevel(v) + 1)<<8;
			for (size_t i=0 ; i<v.Size();++i)
				v[i].second->Mask() |= level;
		}
	};

	//print basic information of vertex:
	//vertex information, and each edge and child vertex
	template<typename VertexType,typename EdgeType>
	class BasicPrinter
	{
	public:
		//functor operation
		void operator()(Vertex<VertexType,EdgeType>& v)
		{
			cout<<internal;
			//PrintSeperator();
			std::cout<<"{Vertex} "<<v.Key()<<endl;
			std::cout<<std::setw(25)<<"{Edge}";
			std::cout<<std::setw(35)<<"{Node}";
			std::cout<<std::endl;
			for (size_t i=0 ; i<v.Size();++i)
			{

				cout<<setw(30)<<v[i].first;
				cout<<setw(20)<<v[i].second->Key()<<endl;
			}

			cout<<endl;
		}
	private:
		//print seperator before print vertex info
		void PrintSeperator()
		{
			char seperator = '-';
			std::cout.fill(seperator);
			std::cout<<std::setw(70)<<seperator<<endl;
			std::cout.fill(' ');
		}
	};
}

#endif