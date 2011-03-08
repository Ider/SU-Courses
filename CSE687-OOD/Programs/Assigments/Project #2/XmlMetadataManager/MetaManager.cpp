


#include "MetaManager.h"


void MetaManager::Build(int argc, char** argv)
{
	packMaker.BuildPakcages(argc,argv);
}
MetaManager::~MetaManager()
{
	packMaker.ClearResults();

	delete gen;
	delete inc;
	if (inStream!= &(std::cin))delete inStream;
	if (outStream != &(std::cout))delete outStream;
}

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
}

void MetaManager::OpenOutStream(std::string& name)
{
	std::ofstream* pFs = dynamic_cast<std::ofstream*> (outStream);
	if (pFs)
		pFs->open(xmlFolder+name+".xml");
}

void MetaManager::CloseOutStream()
{
	std::ofstream* pFs = dynamic_cast<std::ofstream*> (outStream);
	if (pFs && pFs->is_open())
		pFs->close();
}

#ifdef TEST_META_MANAGER

void main(int argc, char** argv)
{
	MetaManager mgr2xml;
	mgr2xml.Build(argc,argv);
	mgr2xml.CreateMetaXML();
	std::cout<<std::endl<<"Xml writing complete"<<std::endl;
}

#endif
