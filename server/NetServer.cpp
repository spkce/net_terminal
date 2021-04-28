#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "NetServer.h"
#include "jsoncpp.h"


namespace NetServer
{

CNetServer::CNetServer()
:m_sockfd(-1)
{
	m_pThread = new Infra::CThread();
	m_pThread->attachProc(Infra::ThreadProc_t(&CNetServer::server_task, this));
	m_pThread->createTread();
	
}

CNetServer::~CNetServer()
{
	stop();
	m_pThread->detachProc(Infra::ThreadProc_t(&CNetServer::server_task, this));

	delete m_pThread;
	m_pThread = NULL;
}

CNetServer* CNetServer::instance()
{
	static CNetServer* pInstance = NULL;
	if (pInstance == NULL)
	{
		static Infra::CMutex sm_mutex;
		Infra::CGuard<Infra::CMutex> guard(sm_mutex);
		if (pInstance == NULL)
		{
			pInstance = new CNetServer;
		}
	}
	return pInstance;
}

bool CNetServer::start(unsigned int port, bool isTcp)
{
	if (m_sockfd >= 0)
	{
		return false;
	}

	m_sockfd = socket(AF_INET, isTcp ? SOCK_STREAM : SOCK_DGRAM, 0);
	if (m_sockfd < 0)
	{
		return false;
	}
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);
	if (bind(m_sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
	{
		return false;
	}

	m_pThread->run();

	return true;
}

bool CNetServer::stop()
{
	if (m_sockfd >= 0)
	{
		::close(m_sockfd);
		m_sockfd = -1;
	}

	return m_pThread->stop(true);
}

void CNetServer::server_task(void* arg)
{

}

}//NetServer
