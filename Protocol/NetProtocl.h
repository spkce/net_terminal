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

	bool decode(const char* buf, int len, char* decodeBuf, int* Length);

	bool reply(NetServer::ISession* session, Param_t* param, const char *buf, int len);



	Terminal::ITerminal* m_pTerminal;

	unsigned char m_AesKey[aesKeyLength];

	unsigned int m_tokenId;
	unsigned int m_reqIndex;
};


}//Screen

#endif // __NET_PROTOCL_H__
