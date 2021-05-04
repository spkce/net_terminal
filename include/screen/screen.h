#ifndef __SCREEN_H__
#define __SCREEN_H__
#include <vector>
#include "thread.h"
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

	virtual bool init();
	virtual bool connect(NetServer::ISession* session);
	virtual bool disconnet(NetServer::ISession* session);
	void serverTask(int sockfd, struct sockaddr_in* addr);
	void sessionTask(NetServer::ISession* session, char* buf, int len);
private:
	const int m_maxSession;
	NetServer::INetServer* m_pServ;
	IProtocl* m_protocl;
	Infra::CMutex m_mutex;
	std::vector<NetServer::ISession*> m_vecSession;
};



} // Screen
#endif //__SCREEN_H__