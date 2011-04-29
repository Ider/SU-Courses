/////////////////////////////////////////////////////////////////////////
// MetaManager.h - integrate meta modules and configure them           //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       MacBook Pro, Windows7 Pro				           //
//  Application:    CSE687 project #2	                               //
//  Author:         Ider Zheng, Syracuse University					   //
//                  (315) 560-4977, ider.cs@gmail.com				   //
/////////////////////////////////////////////////////////////////////////


#include "MetaManager.h"


void MetaManager::Build(int argc, char** argv)
{
	packMaker.BuildPakcages(argc,argv);
}

//////////////////////////////////////////////////////////////////////////
//Destructor, delete each member of MetaManager
MetaManager::~MetaManager()
{
	packMaker.ClearResults();

	delete gen;
	delete inc;
	if (inStream!= &(std::cin))delete inStream;
	if (outStream != &(std::cout))delete outStream;
}

//////////////////////////////////////////////////////////////////////////
//Create meta xml files, and output to outStream.
void MetaManager::CreateMetaXML()
{
	PackIterator pIt;
	for (pIt = results.begin(); pIt!=results.end(); ++pIt)
	{
		PackageInfo& pack = *(pIt->second);
		OpenOutStream(pack.Name());
		(*outStream)<<gen->GetMetadata(pack)<<std::endl<<std::endl;
		CloseOutStream();
	}

	std::cout<<std::endl
		<<results.size()
		<<" xml files have been generated under folder "
		<<xmlFolder<<std::endl;
}

void MetaManager::NavigateMetaXML(const std::string xmlName)
{
	nav->BeginNavigation(xmlName,xmlFolder);
}


//////////////////////////////////////////////////////////////////////////
//If out stream is file stream, open the xml file named name
void MetaManager::OpenOutStream(std::string& name)
{
	std::ofstream* pFs = dynamic_cast<std::ofstream*> (outStream);
	if (pFs)
		pFs->open(xmlFolder+name+".xml");
}

//////////////////////////////////////////////////////////////////////////
//If out stream is file stream, close it.
void MetaManager::CloseOutStream()
{
	std::ofstream* pFs = dynamic_cast<std::ofstream*> (outStream);
	if (pFs && pFs->is_open())
		pFs->close();
}



//////////////////////////////////////////////////////////////////////////
//////////////////////< test stub >///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



#ifdef TEST_META_MANAGER

void main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cout << "\n  please enter command line\n\n";
		return;
	}

	MetaManager mgr2xml;
	try
	{
		mgr2xml.Build(argc,argv);
		mgr2xml.CreateMetaXML();
	}
	catch(...)
	{
		std::cout<<"Oops, unable to generate xml meta data.";
	}

	std::string name = std::string(argv[argc-1]);
	std::cout<<"Now, start to navigate dependencies from "<< name
		<<std::endl<<std::endl;
	system("pause");
	mgr2xml.NavigateMetaXML(name);
}

#endif
