#ifndef __MEDIA_PROTOCL_H__
#define __MEDIA_PROTOCL_H__

#include "IProtocl.h"

namespace NetServer {
	class ISession;
}

namespace Terminal {
	class ITerminal;
}

namespace Screen
{

/**
* @brief media ����Э��
**/
class CMediaProtocl : public IProtocl
{
#define REQ_START_CODE 0xAABB /*�����ͷ��ʶ��*/
#define RES_START_CODE 0xBBAA /*�����ͷ��ʶ��*/
	/**
	* @brief ����ID
	**/
	enum
	{
		emReqMedia = 0xB90B,
	};
	
	/**
	* @brief ������
	**/
	enum
	{
		emNoError = 0,
		emError = 2,
	};
	/**
	* @brief ����ͷ
	**/
	typedef struct tagMediaReqHder
	{
		unsigned short startCode;
		unsigned short msgID;
		unsigned int seekType;
		unsigned int seek;
		unsigned int resolution;
	}MediaReqHder;

	/**
	* @brief �ظ�ͷ
	**/
	typedef struct tagMediaResHder
	{
		unsigned short startCode;
		unsigned short msgID;
		unsigned int retVal;
		unsigned int packetSzie;
		unsigned int totalSzie;
	}MediaResHder;
public:
	/**
	* @brief ���캯����
	* @param terminal �ն�ָ��
	**/
	CMediaProtocl(Terminal::ITerminal* terminal);

	/**
	* @brief ����������
	**/
	virtual ~CMediaProtocl();

	/**
	* @brief Э���������
	* @param session �Ự��ָ��
	* @param buf ���յ�������
	* @param len ���յ������ݳ���
	* @return �ɹ�/ʧ��
	**/
	virtual bool parse(NetServer::ISession* session, char* buf, int len);

	/**
	* @brief ������Ϣ
	* @param msgID ��ϢID
	* @param buf ���յ�������
	* @param len ���յ������ݳ���
	* @return �ɹ�/ʧ��
	**/
	virtual bool notify(NetServer::ISession* session, char* buf, int len);

	/**
	* @brief ��¼
	* @param session �Ự��ָ��
	* @return �ɹ�/ʧ��
	**/
	virtual bool login(NetServer::ISession* session);

private:
	/**
	* @brief ���ͻذ�
	* @param session �Ự��ָ��
	* @param param ����APP�˲���
	* @param buf ���͵ı���
	* @param len ���͵ı��ĳ���
	* @return �ɹ�/ʧ��
	**/
	bool reply(NetServer::ISession* session, const char *buf, int len);

	/**
	* @brief ���Ͱ�
	* @param session �Ự��ָ��
	* @param param ����APP�˲���
	* @param buf ���͵ı���
	* @param len ���͵ı��ĳ���
	* @return �ɹ�/ʧ��
	**/
	bool sendPacket(NetServer::ISession* session, const char *buf, int len);

private:
	Terminal::ITerminal* m_pTerminal; //�ն�ָ��
};

}//Screen

#endif // __GPS_PROTOCL_H__
