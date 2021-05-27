#include "stdio.h"
#include <algorithm>
#include "screen.h"
#include "NetServer.h"
#include "Session.h"
#include "IProtocl.h"

using namespace std;
using namespace Terminal;
using namespace NetServer;
namespace Screen
{

CScreen::CScreen()
:m_maxSession(5)
,m_port(7877)
,m_pServ(NULL)
{
	m_type = ITerminal::emTerminalScree;
	m_protocl = IProtocl::createInstance(IProtocl::emProtocl_hk, this);
}

CScreen::~CScreen()
{
	IProtocl::cancelInstance(m_protocl);
	m_pServ->stop();
}

bool CScreen::init()
{
	m_pServ = INetServer::create(m_port, INetServer::emTCPServer);
	m_pServ->attach(INetServer::ServerProc_t(&CScreen::serverTask, this));
	m_pServ->start(m_maxSession);

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


} // Screen
