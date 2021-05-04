
#include "IProtocl.h"
#include "NetProtocl.h"
#include "terminal.h"

namespace Screen
{

IProtocl * IProtocl::createInstance(protocl_t type, Terminal::ITerminal* termial)
{
	if (type == emProtocl_hk)
	{
		return new CNetProtocl(termial);
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
