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
#define MAX_DATA_BUF 4096
 struct sendPacket
 {
	NetServer::ISession* pSession;
	int len;
	char* buf[MAX_DATA_BUF];
 };
 
public:
	CScreen();
	virtual ~CScreen();

	virtual bool init();
	virtual bool connect(NetServer::ISession* session);
	virtual bool disconnet(NetServer::ISession* session);
	virtual bool send(NetServer::ISession* session, char* buf, int len);
	void serverTask(int sockfd, struct sockaddr_in* addr);
	void sessionTask(NetServer::ISession* session, char* buf, int len);
	void messageProc(void* arg);

private:
	const int m_maxSession;
	const int m_port;
	NetServer::INetServer* m_pServ;
	IProtocl* m_protocl;
	Infra::CThread* m_pThread;
	Infra::CMutex m_mutex;
	std::vector<NetServer::ISession*> m_vecSession;
	Infra::CMsgQueue m_queue;
};



} // Screen
#endif //__SCREEN_H__