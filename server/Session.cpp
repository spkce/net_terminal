#include <stdio.h>
#include <unistd.h>
 #include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Session.h"
#include "thread.h"

namespace NetServer
{

class CSession : public ISession
{
public:
	CSession();
	virtual ~CSession();
	void set(int sockfd, struct sockaddr_in* addr);
	virtual bool bind(const SessionProc_t & proc);
	virtual bool unbind();
	void replyProc(void* arg);
private:
	Infra::CThread m_thread;
	struct sockaddr_in m_addr;
	SessionProc_t m_proc;
	int m_sockfd;
	char* m_pRecvbuf;
	const int m_RecvLen;
};

CSession::CSession()
:m_sockfd(-1)
,m_RecvLen(1024)
{
	memset(&m_addr, 0, sizeof(struct sockaddr_in));
	m_thread.attachProc(Infra::ThreadProc_t(&CSession::replyProc, this));
	m_pRecvbuf = new char[m_RecvLen];
}

CSession::~CSession()
{
	m_thread.detachProc(Infra::ThreadProc_t(&CSession::replyProc, this));
	delete[] m_pRecvbuf;
}

void CSession::set(int sockfd, struct sockaddr_in* addr)
{
	m_sockfd = sockfd;
	memcpy(&m_addr, addr, sizeof(struct sockaddr_in));
}

bool CSession::bind(const SessionProc_t & proc)
{
	if (!m_proc.isEmpty())
	{
		return false;
	}
	m_proc = proc;
	m_thread.createTread();
	m_thread.run();
	return true;
}

bool CSession::unbind()
{
	if (m_proc.isEmpty())
	{
		return false;
	}
	m_thread.stop();
	m_proc.unbind();
	return true;
}

void CSession::replyProc(void* arg)
{
	memset(m_pRecvbuf, 0, m_RecvLen);
	ssize_t len = recv(m_sockfd, m_pRecvbuf, m_RecvLen, 0);

	printf("\033[35m""len = %s""\033[0m\n", len);
	if (m_proc.isEmpty())
	{
		return;
	}

	
}

CSessionManager::CSessionManager()
{
}

CSessionManager::~CSessionManager()
{
}

CSessionManager* CSessionManager::instance()
{
	static CSessionManager* pInstance = NULL;
	if (pInstance == NULL)
	{
		static Infra::CMutex sm_mutex;
		Infra::CGuard<Infra::CMutex> guard(sm_mutex);
		if (pInstance == NULL)
		{
			pInstance = new CSessionManager;
		}
	}
	return pInstance;
}

ISession* CSessionManager::createSession(int sockfd, struct sockaddr_in* addr)
{
	if (sockfd < 0 || addr == NULL)
	{
		return NULL;
	}
	CSession* pSession = new CSession;
	
	pSession->set(sockfd, addr);
	
	return pSession;
}

bool CSessionManager::cancelSession(ISession* session)
{
//	if (session == NULL)
//	{
//		return false;
//	}

//	delete session;

	return true;
}


} //NetServer