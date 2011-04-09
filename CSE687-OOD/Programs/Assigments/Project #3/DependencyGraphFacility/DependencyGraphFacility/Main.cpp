/////////////////////////////////////////////////////////////////////////
//  Main.cpp  -  Provide project entry, and a globe function to get    //
//				  edge infomation from xml and generate meta graph	   //
//  ver 1.0                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////

#include "MetaNavigator.h"
#include "FileSystem.h"
#include "Executive.h"
#include "Display.h"
using namespace IderPrinter;
using namespace std;

//////////////////////////////////////////////////////////////////////////
//Build metadata graph from xml files
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

void main(int argc, char* argv[])
{
	try
	{
		Executive exe;
		Graph<TestVertex,string> g;
		// test graph assignment
		exe.GraphAssignmentTest(g);
		// test deep first search
		exe.TestDFS(g);
		// test strong component
		exe.StrongComponentsTest(g);
		// test globe algorithm
		exe.AlgorithmTest(g,5);

		if(argc < 2)
		{
			std::cout << "\n\n  Please enter, on the command line, a filepath to process.\n";
			return;
		}
		for(int i=1; i<argc; ++i)
		{
			Graph<string,string> graph;
			BuildMetadataGraph(graph,argv[i]);

			exe.Title("Metadata Graph information:");
			graph.DFS(MetaPrinter());
			exe.Title("Metadata Graph nested:");
			graph.DFS(MetaNestedPrinter());
		}

	}
	catch(string ex)
	{
		cout<<ex;
	}
}

#endif
