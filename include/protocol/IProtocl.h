#ifndef __I_PROTOCL_H__
#define __I_PROTOCL_H__

namespace NetServer {
	class ISession;
}

namespace Terminal {
	class ITerminal;
}

namespace Screen
{

/**
* @brief Э��ӿ���
**/
class IProtocl
{	
public:
	/**
	* @brief ֧�ֵ�Э������
	**/
	typedef  enum protocl_t
	{
		emProtocl_hk,
		emProtocl_media,
	}protocl_t;
protected:
	/**
	* @brief ���캯�����趨protectedȨ�ޣ�����ʵ�����ɼ̳�
	**/
	IProtocl();
	/**
	* @brief �����������趨protectedȨ�ޣ�����ʵ�����ɼ̳�
	**/
	virtual ~IProtocl();
public:
	/**
	* @brief ����Э��ʵ��
	* @param type Э������
	* @param termial �ն�
	* @return Э��ӿ�
	**/
	static IProtocl * createInstance(protocl_t type, Terminal::ITerminal* termial);
	/**
	* @brief ȡ��Э��ʵ��
	* @param protocl ���ָ��
	**/
	static void cancelInstance(IProtocl * protocl);
	/**
	* @brief Э���������,����Э�������ʵ��
	* @param session �Ự��ָ��
	* @param buf ���յ�������
	* @param len ���յ������ݳ���
	* @return �ɹ�/ʧ��
	**/
	virtual bool parse(NetServer::ISession* session, char* buf, int len) = 0;
	/**
	* @brief ��װ��Ϣ,����Э�������ʵ��
	* @param msgID ��ϢID
	* @param buf ���յ�������
	* @param len ���յ������ݳ���
	* @return �ɹ�/ʧ��
	**/
	virtual bool notify(NetServer::ISession* session, char* buf, int len) = 0;
};





} //Screen

#endif //__I_PROTOCL_H__
