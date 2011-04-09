#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iomanip>
#include "Graph.h"
//class StrongComponentPrinter
namespace IderPrinter
{
	typedef	Vertex<std::string,std::string>& v_ref;

	class MetaPrinter
	{
	public:
		void operator()(const v_ref v);
	private:
		void FormatLongString(const std::string& str);
		void PrintTableTitle();
	};


	class MetaNestedPrinter
	{
	public:
		void operator()(v_ref v);
	private:
		size_t GetLevel(v_ref v);
		void SetChildrenLevel(v_ref v);

	};

	template<typename VertexType,typename EdgeType>
	class NestedPrinter
	{
	public:
		void operator()(Vertex<VertexType,EdgeType>& v)
		{
			int level = GetLevel(v);
			//if (level == 0) cout<<endl;

			string tab(level,'\t');
			cout<<tab<<"{Vertex} "<<v.Key()<<endl;

			SetChildrenLevel(v);
		}
	private:
		size_t GetLevel(Vertex<VertexType,EdgeType>& v)
		{
			return v.Mask()>>8;	
		}
		void SetChildrenLevel(Vertex<VertexType,EdgeType>& v)
		{
			int level = (GetLevel(v) + 1)<<8;
			for (size_t i=0 ; i<v.Size();++i)
				v[i].second->Mask() |= level;
		}
	};

	template<typename VertexType,typename EdgeType>
	class BasicPrinter
	{
	public:
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