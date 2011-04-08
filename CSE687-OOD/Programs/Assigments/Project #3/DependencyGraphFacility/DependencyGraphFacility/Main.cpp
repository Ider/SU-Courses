
#include "MetaNavigator.h"
#include "FileSystem.h"
#include "Printers.h"

#include "Display.h"
using namespace IderPrinter2;
using namespace std;

void BuildMetadataGraph(Graph<string,string>& graph,string filePath)
{
	WinTools_Extracts::FileHandler fh;

	std::vector<std::string> files = fh.getFileSpecs(filePath,"*.xml");
	//fh.setCurrentDirectory(filePath);
	//std::vector<std::string> file2 = fh.getFiles("*.xml");
	
	MetaNavigator nav = MetaNavigator(graph);
	//add nodes
	for (size_t i=0; i<files.size(); ++i)
		graph.AddNode(nav.GetKeyName(files[i]));

	//add graph
	for (size_t i=0; i<files.size(); ++i)
		nav.BeginNavigation(files[i]);
}

#ifdef MAIN_STUB

void main()
{
	Graph<string,string> graph;
	BuildMetadataGraph(graph,"C:\\Users\\Ider\\Project\\SU\\CSE687-OOD\\Programs\\Assigments\\Project #3\\DependencyGraphFacility\\MetaXML");

	graph.DFS(MetaPrinter());
	graph.DFS(NestedPrinter());

	graph.DFS(ReachableVertexPrinter());

	
}

#endif
