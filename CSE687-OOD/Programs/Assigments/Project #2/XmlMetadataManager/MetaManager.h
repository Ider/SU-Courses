#ifndef META_MANAGER_H
#define META_MANAGER_H

#include <iostream>
#include <map>

#include "IIncludes.h"
#include "MetaGenerator.h"
#include "PackageInfo.h"


class MetaManager
{
public:
	MetaManager(IInclude* iInc, IMetaGenerator* metaGen, std::iostream* stream);
	void Build(int argc, char** argv);
private:
	IInclude* inc;
	IMetaGenerator* gen;
	std::istream* inStream;
	PackagesGenerator packMaker;
	PackMap results;

};


inline MetaManager::MetaManager(IInclude* iInc, IMetaGenerator* metaGen, std::iostream* stream)
:inc(iInc),gen(metaGen),inStream(stream)
{
}

#endif