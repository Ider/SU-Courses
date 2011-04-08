#ifndef  PRINTERS_H
#define PRINTERS_H

#include <string>
#include "Graph.h"
//class StrongComponentPrinter


namespace IderPrinter
{

	void printInt(const Vertex<std::string,std::string>& v);


	class MetaPrinter
	{
	public:
		void operator()(const Vertex<std::string,std::string>& v);
	private:
		void FormatLongString(const std::string& str);
		void PrintTableTitle();
	};

	class NestedPrinter
	{
	public:
		void operator()(Vertex<std::string,std::string>& v);
	private:
		int GetLevel(Vertex<std::string,std::string>& v);
		void SetChildrenLevel(Vertex<std::string,std::string>& v);

	};
}

#endif