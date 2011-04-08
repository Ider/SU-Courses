#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
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
}


#endif