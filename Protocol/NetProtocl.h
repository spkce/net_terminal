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
	enum
	{
		aesKeyLength = 16,
	};

public:
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
