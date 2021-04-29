#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "NetServer.h"
#include "jsoncpp.h"


namespace NetServer
{

INetServer::INetServer()
{

}

INetServer::~INetServer()
{

}

CNetServer::CNetServer(unsigned int port, bool isTcp)
:m_sockfd(-1)
,m_port(port)
,m_isTcp(isTcp)
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

INetServer* CNetServer::create(unsigned int port, bool isTcp)
{
	static CNetServer* pInstance = NULL;
	if (pInstance == NULL)
	{
		static Infra::CMutex sm_mutex;
		Infra::CGuard<Infra::CMutex> guard(sm_mutex);
		if (pInstance == NULL)
		{
			pInstance = new CNetServer(port, isTcp);
		}
	}
	return pInstance;
}

bool CNetServer::attach(INetServer::ServerProc_t proc)
{
	if (!m_proc.isEmpty())
	{
		return false;
	}
	m_proc = proc;
	return true;
}

bool CNetServer::start(unsigned int maxlisten)
{
	if (m_sockfd >= 0)
	{
		return false;
	}

	m_sockfd = socket(AF_INET, m_isTcp ? SOCK_STREAM : SOCK_DGRAM, 0);
	if (m_sockfd < 0)
	{
		return false;
	}
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(m_port);
	if (bind(m_sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
	{
		return false;
	}

	if(listen(m_sockfd, maxlisten) < 0)
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

	struct sockaddr_in cliaddr = {0};
	socklen_t clilen = sizeof(struct sockaddr_in);

	//if(uWaitMsec != WAIT_FOREVER)
	//{
	//	stTimeout.tv_sec = uWaitMsec/1000;
	//stTimeout.tv_usec = uWaitMsec%1000;
    //    FD_ZERO(&rset);
    //    FD_SET(iSockFd, &rset);
    //    if(select(iSockFd + 1, &rset, NULL, NULL, &stTimeout) <= 0)
    //    {
    //        SYS_SOCKET_INFO("wait accept client connect failed, err:%s\n", strerror(errno));
    //        return ERROR;
    //	}
    //}

	int sock = accept(m_sockfd, (struct sockaddr *)&cliaddr, &clilen);
	if (sock < 0 )
	{
		return;
	}
	printf("\033[35m""connect:%s:%d""\033[0m\n", (char*)inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
	if (!m_proc.isEmpty())
	{
		m_proc(sock, &cliaddr);
	}
}

}//NetServer
