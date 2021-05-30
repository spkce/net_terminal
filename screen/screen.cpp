#include "stdio.h"
#include <string.h>
#include <algorithm>
#include "screen.h"
#include "NetServer.h"
#include "Session.h"
#include "IProtocl.h"
#include "Log.h"
#include "ctime.h"

using namespace std;
using namespace Terminal;
using namespace NetServer;
namespace Screen
{

CScreen::CScreen()
:m_maxSession(5)
,m_port(7877)
,m_pServ(NULL)
,m_queue("screenQueue", 10, sizeof(struct sendPacket))
{
	m_type = ITerminal::emTerminalScree;
	m_protocl = IProtocl::createInstance(IProtocl::emProtocl_hk, this);
	m_pThread = new Infra::CThread();
	m_pThread->attachProc(Infra::ThreadProc_t(&CScreen::messageProc, this));
	m_pThread->createTread();
}

CScreen::~CScreen()
{
	IProtocl::cancelInstance(m_protocl);
	m_pServ->stop();
	m_pThread->stop(true);
	m_pThread->detachProc(Infra::ThreadProc_t(&CScreen::messageProc, this));
	delete m_pThread;
	m_pThread = NULL;
}

bool CScreen::init()
{
	m_pServ = INetServer::create(m_port, INetServer::emTCPServer);
	m_pServ->attach(INetServer::ServerProc_t(&CScreen::serverTask, this));
	m_pServ->start(m_maxSession);
	m_pThread->run();
	return true;
}

bool CScreen::connect(ISession* session)
{
	if (session == NULL)
	{
		return false;
	}

	Infra::CGuard<Infra::CMutex> guard(m_mutex);
	if (m_vecSession.size() >= (unsigned int)m_maxSession)
	{
		return false;
	}
	
	vector<ISession*>::iterator iter = find(m_vecSession.begin(), m_vecSession.end(), session);
	if (iter == m_vecSession.end())
	{
		m_vecSession.push_back(session);
		return true;
	}
	
	return false;
}

bool CScreen::disconnet(ISession* session)
{
	if (session == NULL)
	{
		return false;
	}

	Infra::CGuard<Infra::CMutex> guard(m_mutex);

	vector<ISession*>::iterator iter = find(m_vecSession.begin(), m_vecSession.end(), session);

	if (iter == m_vecSession.end())
	{
		return false;
	}

	m_vecSession.erase(iter);

	session->close();
	return true;
}

bool CScreen::send(NetServer::ISession* session, char* buf, int len)
{
	if (buf == NULL || session == NULL || len <= 0)
	{
		Error("NetTerminal", "Input Param NULL\n");
		return false;
	}

	if (len > MAX_DATA_BUF)
	{
		Error("NetTerminal", "too large date\n");
		return false;
	}
	// todo use heap
	struct sendPacket packet = {0};
	packet.pSession = session;
	packet.len = len;
	memcpy(packet.buf, buf, len);
	return m_queue.input((const char*)&packet, sizeof(struct sendPacket), 1);
}

void CScreen::serverTask(int sockfd, struct sockaddr_in* addr)
{
	ISession* pSession = CSessionManager::instance()->createSession(sockfd, addr, 15);
	if (pSession == NULL)
	{
		return ;
	}

	pSession->bind(ISession::SessionProc_t(&CScreen::sessionTask, this));
}

void CScreen::sessionTask(NetServer::ISession* session, char* buf, int len)
{
	if (session == NULL || buf == NULL || len <= 0)
	{
		return ;
	}
	m_protocl->parse(session, buf, len);
}

void CScreen::messageProc(void *arg)
{
	struct sendPacket packet = {0}; // todo use heap
	if (m_queue.output((char *)&packet, sizeof(struct sendPacket), 300))
	{
		NetServer::ISession *p = packet.pSession;
		if (p == NULL)
		{
			Error("NetTerminal", "ISession ptr NULL\n");
			goto DELAY;
		}
		p->send((const char*)(packet.buf), packet.len);
		return ;
	}

DELAY:
	Infra::CTime::delay_ms(300);
}

} // Screen
