#ifndef __NET_PROTOCL_H__
#define __NET_PROTOCL_H__
#include "IProtocl.h"
#include "jsoncpp.h"
#include "aes_encrypt.h"
#include "rsa_app.h"
#include "Session.h"

namespace NetServer {
	class ISession;
}

namespace Terminal {
	class ITerminal;
}

namespace Screen
{

/**
* @brief ���������豸ͨ��Э����
**/
class CNetProtocl: public IProtocl
{
#define NET_APP_EXTRA_LEN                       16          /*���ӱ��뻺������С*/
#define AES_MAX_IN_LEN                          16384        /*16KB*/
#define AES_MAX_OUT_LEN                         ((AES_MAX_IN_LEN) + (NET_APP_EXTRA_LEN))
#define AES_MAX_OUT_LEN_BASE64                  (AES_MAX_OUT_LEN*2)
#define MSG_HEADER_LENGTH                       12          /*��Ϣͷ�ֽ�*/
#define NET_APP_RECV_SIZE                       2048        /*���ջ�������С*/
#define NET_APP_RECV_ADD                        ((NET_APP_RECV_SIZE) + (NET_APP_EXTRA_LEN))
	enum
	{
		aesKeyLength = 16,
	};
	/**
	* @brief ����APP�˲���
	*/
	typedef struct Param_t
	{
		unsigned int uTokenId;	/*����ID*/
		unsigned int uMsgId;	/*����ID*/
		unsigned int uReqIdx;	/*��Ϣ����*/
		unsigned int uEncrypt;	/*�Ƿ���Ҫ����*/
	} Param_t;

#define MSG_HEADER_CONS                         0x41424243  /*��Ϣͷ��ʼ��ABBC*/
	/**
	 * @brief DEVICE->APP��Ϣͷ����Ϣ
	 */
	struct msgHeader
	{
		unsigned int uMsgConstant;    /*��ʼ��ABBC*/
		unsigned int uMsgIndex;       /*��Ϣ��ţ�1...n������Ϣ����ID��ͬ*/
		unsigned int uMsgLength;      /*��Ϣ���ĳ���*/
	}msgHeader;
public:
	/**
	* @brief ���캯����
	* @param terminal �ն�ָ��
	**/
	CNetProtocl(Terminal::ITerminal* terminal);
	/**
	* @brief ����������
	**/
	virtual ~CNetProtocl();
	/**
	* @brief ���Ľ���
	* @param session �Ự��ָ��
	* @param buf ���յ�������
	* @param len ���յ������ݳ���
	* @return �ɹ�/ʧ��
	**/
	virtual bool parse(NetServer::ISession* session, char* buf, int len);
	/**
	* @brief ��װ��Ϣ����,����Э�������ʵ��
	* @param session �Ự��ָ��
	* @param buf ���յ�������
	* @param len ���յ������ݳ���
	* @return �ɹ�/ʧ��
	**/
	virtual bool notify(NetServer::ISession* session, char* buf, int len);
	/**
	* @brief ��Ϣ�ַ�
	* @param session �Ự��ָ��
	* @param msgID ��ϢID
	* @param request ������
	* @param response �ظ�
	* @return �ɹ�/ʧ��
	**/
	bool msgHub(NetServer::ISession * session, unsigned int msgID, Json::Value &request, Json::Value &response);
	/**
	* @brief ��¼
	* @param session �Ự��ָ��
	* @return �ɹ�/ʧ��
	**/
	bool login(NetServer::ISession* session, Json::Value &request, Json::Value &response);
	/**
	* @brief �ǳ�
	* @param session �Ự��ָ��
	* @return �ɹ�/ʧ��
	**/
	bool logout(NetServer::ISession* session);
	/**
	* @brief ����
	* @param session �Ự��ָ��
	* @return �ɹ�/ʧ��
	**/
	bool keepAlive(NetServer::ISession* session);
private:
	/**
	* @brief ��Ϣ����
	* @param session �Ự��ָ��
	* @param buf ���յ�������
	* @param len ���յ������ݳ���
	* @return �ɹ�/ʧ��
	**/
	bool messageProcess(NetServer::ISession* session, char* buf, int len);
	/**
	* @brief ������������
	* @param session �Ự��ָ��
	* @param request ������
	* @param response �ظ�����
	* @return �ɹ�/ʧ��
	**/
	bool handShake(NetServer::ISession* session, char* buf, int len);
	/**
	* @brief ��鱨��Э��ͷ
	* @param buf ���յ�������
	* @param index ��Ϣindex ÿ��ͨѶ+1
	* @param len ���յ������ݳ���
	* @return �ɹ�/ʧ��
	**/
	bool headerCheck(const char *buf, unsigned int *index, unsigned int * len);
	/**
	* @brief ����
	* @param buf �����������
	* @param len ����������ݳ���
	* @param decodeBuf ����������
	* @param Length ���������ݳ���
	* @return �ɹ�/ʧ��
	**/
	bool decrypt(const char* buf, int len, char* decodeBuf, int* Length);
	/**
	* @brief ����
	* @param buf �����ܵ�����
	* @param len �����ܵ����ݳ���
	* @param encryptBuf ���ܺ������
	* @param Length ���ܺ�����ݳ���
	* @return �ɹ�/ʧ��
	**/
	bool encrypt(const char* buf, int len, unsigned char* encryptBuf, int* Length);
	/**
	* @brief ���ͻذ�
	* @param session �Ự��ָ��
	* @param param ����APP�˲���
	* @param buf ���͵ı���
	* @param len ���͵ı��ĳ���
	* @return �ɹ�/ʧ��
	**/
	bool reply(NetServer::ISession* session, Param_t* param, const char *buf, int len);
	/**
	* @brief ���Ͱ�
	* @param session �Ự��ָ��
	* @param param ����APP�˲���
	* @param buf ���͵ı���
	* @param len ���͵ı��ĳ���
	* @return �ɹ�/ʧ��
	**/
	bool sendPacket(NetServer::ISession* session, Param_t* param, const char *buf, int len);

	Terminal::ITerminal* m_pTerminal; //�ն�ָ��

	unsigned char m_AesKey[aesKeyLength]; //aes��Կ

	int m_tokenId; //teokenId
	unsigned int m_reqIndex; //����index
	
};


}//Screen

#endif // __NET_PROTOCL_H__
