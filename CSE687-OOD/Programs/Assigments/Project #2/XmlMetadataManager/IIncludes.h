#ifndef IINCLUDE_H
#define IINCLUDE_H


#include <string>

class IInclude
{
public:
	virtual ~IInclude(){}
	virtual bool Attach(std::string path) =0;
	virtual bool Next()=0;
	virtual std::string GetFullName()=0;
	virtual std::string GetPackageName()=0;
	virtual bool IsSystem()=0;
};

#endif