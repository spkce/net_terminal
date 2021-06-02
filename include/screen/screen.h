#ifndef __SCREEN_H__
#define __SCREEN_H__
#include <vector>
#include "thread.h"
#include "terminal.h"
#include "MsgQueue.h"

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
public:
	CScreen();
	virtual ~CScreen();

	virtual bool init();
	virtual bool connect(NetServer::ISession* session);
	virtual bool disconnet(NetServer::ISession* session);
	virtual bool notify(char* buf, int len);
	
	void serverTask(int sockfd, struct sockaddr_in* addr);
	void sessionTask(NetServer::ISession* session, char* buf, int len);
	void servGpsTask(int sockfd, struct sockaddr_in* addr);
	void pushGpsTask(NetServer::ISession* session, char* buf, int len);
private:
#define PORT_MAIN 7877
#define PORT_GPS 8881
#define MAX_SESSION_MAIN 5
#define MAX_SESSION_GPS 1
	const int m_maxSession;
	const int m_maxGpsSession;
	const int m_portMain;
	const int m_portGps;
	NetServer::INetServer* m_pServMain;
	NetServer::INetServer* m_pServGps;
	IProtocl* m_protocl;
	Infra::CMutex m_mutex;
	std::vector<NetServer::ISession*> m_vecSession;
};



} // Screen
#endif //__SCREEN_H__