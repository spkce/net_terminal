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
:m_maxSession(MAX_SESSION_MAIN)
,m_maxGpsSession(MAX_SESSION_GPS)
,m_portMain(PORT_MAIN)
,m_portGps(PORT_GPS)
,m_pServMain(NULL)
,m_pServGps(NULL)
,m_GpsSession(NULL)
{
	m_type = ITerminal::emTerminalScree;
	m_protocl = IProtocl::createInstance(IProtocl::emProtocl_hk, this);
	m_protoclGps = IProtocl::createInstance(IProtocl::emProtocl_media, this);
}

CScreen::~CScreen()
{
	m_pServGps->stop();
	m_pServMain->stop();
	IProtocl::cancelInstance(m_protocl);
	IProtocl::cancelInstance(m_protoclGps);
}

bool CScreen::init()
{
	m_pServMain = INetServer::create(m_portMain, INetServer::emTCPServer);
	m_pServMain->attach(INetServer::ServerProc_t(&CScreen::serverTask, this));
	m_pServMain->start(m_maxSession);

	m_pServGps = INetServer::create(m_portGps, INetServer::emTCPServer);
	m_pServGps->attach(INetServer::ServerProc_t(&CScreen::servGpsTask, this));
	return true;
}

bool CScreen::connect(ISession* session, int type)
{
	if (session == NULL)
	{
		return false;
	}

	if (type == IProtocl::emProtocl_hk)
	{
		Infra::CGuard<Infra::CMutex> guard(m_mutex);
		if (m_vecSession.size() >= (unsigned int)m_maxSession)
		{
			return false;
		}

		vector<ISession*>::iterator iter = find(m_vecSession.begin(), m_vecSession.end(), session);
		if (iter == m_vecSession.end())
		{
			m_vecSession.push_back(session);
			if (!m_pServGps->isRun())
			{
				Trace("NetTerminal", "GPS Server run\n");
				m_pServGps->start(m_maxGpsSession);
			}
			return true;
		}
	}
	else if (type == IProtocl::emProtocl_media)
	{
		if (m_GpsSession == NULL)
		{
			Trace("NetTerminal", "GPS session connect\n");
			m_GpsSession = session;
			return true;
		}
	}
	
	return false;
}

bool CScreen::disconnet(ISession* session, int type)
{
	if (session == NULL)
	{
		return false;
	}

	if (type == IProtocl::emProtocl_hk)
	{
		Infra::CGuard<Infra::CMutex> guard(m_mutex); // todo usd rwlock

		vector<ISession*>::iterator iter = find(m_vecSession.begin(), m_vecSession.end(), session);

		if (iter == m_vecSession.end())
		{
			return false;
		}

		m_vecSession.erase(iter);
		session->close();

		if (m_vecSession.size() == 0 && m_pServGps->isRun())
		{
			if (m_GpsSession != NULL)
			{
				m_GpsSession->close();
			}
			m_pServGps->stop();
			Trace("NetTerminal", "GPS Server stop\n");
		}
		
		return true;
	}
	else if (type == IProtocl::emProtocl_media)
	{
		if (m_GpsSession == session)
		{
			Trace("NetTerminal", "GPS session disconnet\n");
			session->close();
			m_GpsSession = NULL;
			return true;
		}
	}
	
	return false;
}

bool CScreen::notify(char* buf, int len)
{
	if (buf == NULL || len <= 0)
	{
		Error("NetTerminal", "Input Param NULL\n");
		return false;
	}

	ISession* pSession = NULL;
	{
		Infra::CGuard<Infra::CMutex> guard(m_mutex);
		//默认第一个连接为主链接
		vector<ISession*>::iterator iter = m_vecSession.begin();
		if (iter == m_vecSession.end())
		{
			Error("NetTerminal", "screen connection dropped\n");
			return false;
		}
		pSession = *iter;
	}
	 
	return m_protocl->notify(pSession, buf, len);
}

bool CScreen::pushGps(char* buf, int len)
{
	if (m_GpsSession != NULL)
	{
		return m_protoclGps->notify(m_GpsSession, buf, len);
	}

	return false;
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

void CScreen::servGpsTask(int sockfd, struct sockaddr_in* addr)
{
	ISession* pSession = CSessionManager::instance()->createSession(sockfd, addr);
	if (pSession == NULL)
	{
		return ;
	}
	pSession->bind(ISession::SessionProc_t(&CScreen::pushGpsTask, this));
}

void CScreen::pushGpsTask(NetServer::ISession* session, char* buf, int len)
{
	if (session == NULL || buf == NULL || len <= 0)
	{
		return ;
	}
	m_protoclGps->parse(session, buf, len);
}

} // Screen
