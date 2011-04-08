#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "Graph.h"
//class StrongComponentPrinter
namespace IderPrinter2
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

	class NestedPrinter
	{
	public:
		void operator()(v_ref v);
	private:
		size_t GetLevel(v_ref v);
		void SetChildrenLevel(v_ref v);

	};

	class ReachableVertexPrinter
	{
	public:
		void operator()(v_ref v);
	private:
 		void Print(v_ref v);
 		bool Traversed(v_ref v);
		void SetTraversed(v_ref v);
		//void SetChildrenLevel();
		size_t GetLevel(v_ref v);
 		int curLevel;

		Graph<std::string,std::string> graph;
		NestedPrinter nested;
	};
}
#endif