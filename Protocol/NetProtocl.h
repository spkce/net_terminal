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
#define NET_APP_EXTRA_LEN                       16          /*附加编码缓冲区大小*/
#define AES_MAX_IN_LEN                          16384        /*16KB*/
#define AES_MAX_OUT_LEN                         ((AES_MAX_IN_LEN) + (NET_APP_EXTRA_LEN))
#define AES_MAX_OUT_LEN_BASE64                  (AES_MAX_OUT_LEN*2)
#define MSG_HEADER_LENGTH                       12          /*消息头字节*/
#define NET_APP_RECV_SIZE                       2048        /*接收缓冲区大小*/
#define NET_APP_RECV_ADD                        ((NET_APP_RECV_SIZE) + (NET_APP_EXTRA_LEN))
	enum
	{
		aesKeyLength = 16,
	};
	/**
	* @brief 返回APP端参数
	*/
	typedef struct Param_t
	{
		unsigned int uTokenId;	/*令牌ID*/
		unsigned int uMsgId;	/*命令ID*/
		unsigned int uReqIdx;	/*消息索引*/
		unsigned int uEncrypt;	/*是否需要加密*/
	} Param_t;

#define MSG_HEADER_CONS                         0x41424243  /*消息头起始码ABBC*/
	/**
	 * @brief DEVICE->APP消息头部信息
	 */
	struct msgHeader
	{
		unsigned int uMsgConstant;    /*起始码ABBC*/
		unsigned int uMsgIndex;       /*消息编号，1...n，与消息类型ID不同*/
		unsigned int uMsgLength;      /*消息报文长度*/
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
