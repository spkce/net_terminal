
#include "IProtocl.h"
#include "NetProtocl.h"

namespace Screen
{

IProtocl * IProtocl::createInstance(protocl_t type)
{
	if (type == emProtocl_hk)
	{
		return new CNetProtocl;
	}
	
	return NULL;
}

void IProtocl::cancelInstance(IProtocl * protocl)
{
	if (protocl != NULL)
	{
		delete protocl;
	}
}

IProtocl::IProtocl()
{

}

IProtocl::~IProtocl()
{

}

}//Screen
