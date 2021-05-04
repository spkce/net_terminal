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
public:
	CNetProtocl(Terminal::ITerminal* terminal);
	virtual ~CNetProtocl();

	virtual bool parse(NetServer::ISession* session, char* buf, int len);

	bool hub(NetServer::ISession * session, Json::Value &request, Json::Value &response);

	bool login(NetServer::ISession* session, Json::Value &request, Json::Value &response);

	bool logout(NetServer::ISession* session, Json::Value &request, Json::Value &response);

	bool keepAlive(NetServer::ISession* session, Json::Value &request, Json::Value &response);
private:
	Terminal::ITerminal* m_pTerminal;
};


}//Screen

#endif // __NET_PROTOCL_H__
