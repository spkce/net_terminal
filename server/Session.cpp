#include <stdio.h>
#include <unistd.h>
 #include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Session.h"
#include "thread.h"
#include "ctime.h"

namespace NetServer
{

class CSession : public ISession
{
public:
	CSession();
	virtual ~CSession();
	void set(int sockfd, struct sockaddr_in* addr, int timeout);
	virtual bool bind(const ISession::SessionProc_t & proc);
	virtual bool unbind();
	
	virtual bool login();
	virtual bool logout();
	virtual bool keepAlive();

	
	virtual state_t getState();
	
	virtual bool close();

	void replyProc(void* arg);

private:
	Infra::CThread m_thread;
	struct sockaddr_in m_addr;
	ISession::SessionProc_t m_proc;
	
	const int m_RecvLen;

	long m_lastTime;
	int m_timeout;
	int m_sockfd;
	state_t m_state;
	char* m_pRecvbuf;
};

CSession::CSession()
:m_RecvLen(1024)
,m_lastTime(0)
,m_timeout(-1)
,m_sockfd(-1)
,m_state(emStateCreated)
{
	memset(&m_addr, 0, sizeof(struct sockaddr_in));
	m_thread.attachProc(Infra::ThreadProc_t(&CSession::replyProc, this));
	m_pRecvbuf = new char[m_RecvLen];
}

CSession::~CSession()
{
	close();
	m_thread.detachProc(Infra::ThreadProc_t(&CSession::replyProc, this));
	delete[] m_pRecvbuf;
}

void CSession::set(int sockfd, struct sockaddr_in* addr, int timeout)
{
	m_sockfd = sockfd;
	memcpy(&m_addr, addr, sizeof(struct sockaddr_in));
	m_timeout = timeout;
}

bool CSession::bind(const ISession::SessionProc_t & proc)
{
	if (!m_proc.isEmpty())
	{
		return false;
	}
	m_proc = proc;
	m_thread.createTread();
	m_thread.run();
	m_state = emStateLogout;
	return true;
}

bool CSession::unbind()
{
	if (m_proc.isEmpty())
	{
		return false;
	}
	m_thread.stop(true);
	m_proc.unbind();
	m_state = emStateCreated;
	return true;
}

bool CSession::login()
{
	if (m_state == emStateLogout)
	{
		m_lastTime = Infra::CTime::getSystemTimeSecond();
		m_state = emStateLogin;
		return true;
	}
	return false;
}

bool CSession::logout()
{
	if (m_state == emStateLogin)
	{
		m_state = emStateLogout;
		return true;
	}
	return false;
}

bool CSession::keepAlive()
{
	if (m_state == emStateLogin)
	{
		m_lastTime = Infra::CTime::getSystemTimeSecond();
		return true;
	}
	return false;
}

ISession::state_t CSession::getState()
{
	return m_state;
}
	
bool CSession::close()
{
	switch (m_state)
	{
	case emStateLogin:
		logout();
	case emStateLogout:
		unbind();
	case emStateCreated:
		if (m_sockfd >= 0)
		{
			::close(m_sockfd);
			m_sockfd = -1;
		}
		m_state = emStateClose;
		return true;
	default:
		return false;
	}
}

void CSession::replyProc(void* arg)
{
	memset(m_pRecvbuf, 0, m_RecvLen);
	int len = recv(m_sockfd, m_pRecvbuf, m_RecvLen, 0);

	if (len <= 0 || m_proc.isEmpty())
	{
		// len == 0时关闭为对端关闭
		return;
	}

	printf("\033[35m""recv:%s:%d len=%d""\033[0m\n", (char*)inet_ntoa(m_addr.sin_addr), ntohs(m_addr.sin_port), len);
	m_proc(this, m_pRecvbuf, len);
	
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

ISession* CSessionManager::createSession(int sockfd, struct sockaddr_in* addr, int timeout)
{
	if (sockfd < 0 || addr == NULL)
	{
		return NULL;
	}
	CSession* pSession = new CSession;
	
	pSession->set(sockfd, addr, timeout);
	
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