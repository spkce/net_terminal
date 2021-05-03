#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "terminal.h"

struct sockaddr_in;

namespace NetServer {
	class INetServer;
	class ISession;
}
namespace Screen
{

class IProtocl;
class CScreen : public Terminal::ITerminal
{
private:

public:
	CScreen();
	virtual ~CScreen();

	bool init();

	void serverTask(int sockfd, struct sockaddr_in* addr);
	void sessionTask(NetServer::ISession* session, char* buf, int len);
private:
	NetServer::INetServer* m_pServ;
	IProtocl* m_protocl;
};



} // Screen
#endif //__SCREEN_H__