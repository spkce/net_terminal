#ifndef __NET_SERVER_H__
#define __NET_SERVER_H__

#include "thread.h"

struct sockaddr_in;

namespace NetServer
{

/**
 * @brief �������ӿ���
*/
class INetServer
{
public:
	/**
	* @brief �������ص��������� void fun(int fd, struct sockaddr_in* addr);
	* @param fd �׽��־��
	* @param addr �Զ˵�ַ
	**/
	typedef Infra::TFuncation2<void, int, struct sockaddr_in*> ServerProc_t;
	/**
	* @brief ����������ö��
	**/
	typedef enum Type_t
	{
		emTCPServer,
		emUDPServer,
	}Type_t;
protected:
	/**
	* @brief INetServer���캯����Ȩ���趨protected����ֹʵ��
	**/
	INetServer();
	/**
	* @brief INetServer���캯����Ȩ���趨protected����ֹʵ��
	**/
	virtual ~INetServer();
public:
	/**
	* @brief ��������������
	* @param port �������󶨵Ķ˿�
	* @param type ����������
	* @return �������ӿ�
	**/
	static INetServer* create(unsigned int port, Type_t type);
	/**
	* @brief ��������ʼ����
	* @param maxlisten �������
	* @return �ɹ�/ʧ��
	**/
	virtual bool start(unsigned int maxlisten) = 0;
	/**
	* @brief ע��������ص�����
	* @param proc �������ص�����
	* @return �ɹ�/ʧ��
	**/
	virtual bool attach(ServerProc_t proc) = 0;
	/**
	* @brief ������ֹͣ����
	* @return �ɹ�/ʧ��
	**/
	virtual bool stop() = 0;

	/**
	* @brief �������Ƿ�����
	* @return ��/��
	**/
	virtual bool isRun() = 0;
};





} //NetServer
#endif //__NET_SERVER_H__
