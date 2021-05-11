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
	CNetProtocl(Terminal::ITerminal* terminal);
	virtual ~CNetProtocl();

	virtual bool parse(NetServer::ISession* session, char* buf, int len);

	bool msgHub(NetServer::ISession * session, unsigned int msgID, Json::Value &request, Json::Value &response);

	bool login(NetServer::ISession* session, Json::Value &request, Json::Value &response);

	bool logout(NetServer::ISession* session, Json::Value &request, Json::Value &response);

	bool keepAlive(NetServer::ISession* session, Json::Value &request, Json::Value &response);
private:
	bool messageProcess(NetServer::ISession* session, char* buf, int len);

	bool handShake(NetServer::ISession* session, char* buf, int len);

	bool headerCheck(const char *buf, unsigned int *index, unsigned int * len);

	bool decrypt(const char* buf, int len, char* decodeBuf, int* Length);

	bool encrypt(const char* buf, int len, char* encryptBuf, int* Length);
	
	bool reply(NetServer::ISession* session, Param_t* param, const char *buf, int len);

	int getSetting(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam);

	bool getCameraStatus(NetServer::ISession* session, Json::Value &request, Json::Value &response);

	int getVehicleStatus(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam);

	int getDeviceStatus(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam);

	int sendAppInfo(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam);
	
	int sendTouchInfo(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam);

	Terminal::ITerminal* m_pTerminal;

	unsigned char m_AesKey[aesKeyLength];

	unsigned int m_tokenId;
	unsigned int m_reqIndex;
	
	//std::unique_ptr<Json::StreamWriter> m_uPtrJsonWriter;
};


}//Screen

#endif // __NET_PROTOCL_H__
