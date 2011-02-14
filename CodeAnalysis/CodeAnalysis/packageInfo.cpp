#include "packageInfo.h"


funcInfo* packageInfo::getFunction(const std::string& funcName)
{
	std::map<std::string,funcInfo*>::iterator it = functions.find(funcName);
	if (it==functions.end()) 
		return NULL;
	else
		return it->second;
} 

funcInfo* packageInfo::getFunction(const std::string& cName,const std::string& fName)
{
	std::string name;
	if (fName.length()>0)
		name =  cName + "::" + fName;
	else
		name = fName;

	return getFunction(name);
}


bool packageInfo::addFunction(funcInfo* func)
{
	try
	{
		std::pair<std::string,funcInfo*> item = 
			std::pair<std::string,funcInfo*>(func->getFullName(),func);
		functions.insert(item);
		return true;
	}
	catch (std::exception* e)
	{
		return false;
	}
}
