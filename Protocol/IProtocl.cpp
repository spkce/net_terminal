
#include "IProtocl.h"
#include "NetProtocl.h"
#include "terminal.h"

namespace Screen
{

/**
* @brief 创建协议实例
* @param type 协议类型
* @param termial 终端
* @return 协议接口
**/
IProtocl * IProtocl::createInstance(protocl_t type, Terminal::ITerminal* termial)
{
	if (type == emProtocl_hk)
	{
		return new CNetProtocl(termial);
	}
	
	return NULL;
}

/**
* @brief 取消协议实例
* @param protocl 议接指针
**/
void IProtocl::cancelInstance(IProtocl * protocl)
{
	if (protocl != NULL)
	{
		delete protocl;
	}
}

/**
* @brief 构造函数，设定protected权限，不可实例，可继承
**/
IProtocl::IProtocl()
{

}

/**
* @brief 析构函数，设定protected权限，不可实例，可继承
**/
IProtocl::~IProtocl()
{

}

}//Screen
