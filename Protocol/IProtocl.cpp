
#include "IProtocl.h"
#include "NetProtocl.h"
#include "terminal.h"

namespace Screen
{

/**
* @brief ����Э��ʵ��
* @param type Э������
* @param termial �ն�
* @return Э��ӿ�
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
* @brief ȡ��Э��ʵ��
* @param protocl ���ָ��
**/
void IProtocl::cancelInstance(IProtocl * protocl)
{
	if (protocl != NULL)
	{
		delete protocl;
	}
}

/**
* @brief ���캯�����趨protectedȨ�ޣ�����ʵ�����ɼ̳�
**/
IProtocl::IProtocl()
{

}

/**
* @brief �����������趨protectedȨ�ޣ�����ʵ�����ɼ̳�
**/
IProtocl::~IProtocl()
{

}

}//Screen
