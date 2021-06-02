#include <stdio.h>
#include <unistd.h>
#include <algorithm>
 #include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Session.h"
#include "thread.h"
#include "ctime.h"
#include "Log.h"
#include "MsgQueue.h"

namespace NetServer
{

class CSession : public ISession
{
	//friend class CSessionManager;
private:
	#define MAX_DATA_BUF 4096
 	struct sendPacket
 	{
		int len;
		char* buf[MAX_DATA_BUF];
 	};
protected: 
	CSession();
	virtual ~CSession();
public:
	void set(int sockfd, struct sockaddr_in* addr, int timeout);
	virtual bool bind(const ISession::SessionProc_t & proc);
	virtual bool unbind();
	
	virtual bool login();
	virtual bool logout();
	virtual bool keepAlive();

	
	virtual state_t getState();
	
	virtual bool close();

	static CSession* create();
	virtual void destroy();

	virtual int send(const char* buf, int len);
	virtual bool transmit(const char* buf, int len);
	void replyProc(void* arg);
	void sendProc(void* arg);
private:
	Infra::CMsgQueue m_queue;
	Infra::CThread m_recvThread;
	Infra::CThread m_sendThread;
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
:m_queue(5, sizeof(struct sendPacket))
,m_RecvLen(1024)
,m_lastTime(0)
,m_timeout(-1)
,m_sockfd(-1)
,m_state(emStateCreated)
{
	memset(&m_addr, 0, sizeof(struct sockaddr_in));
	m_recvThread.attachProc(Infra::ThreadProc_t(&CSession::replyProc, this));
	m_sendThread.attachProc(Infra::ThreadProc_t(&CSession::sendProc, this));
	m_pRecvbuf = new char[m_RecvLen];
}

CSession::~CSession()
{
	close();
	m_recvThread.detachProc(Infra::ThreadProc_t(&CSession::replyProc, this));
	m_sendThread.detachProc(Infra::ThreadProc_t(&CSession::sendProc, this));
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
	m_recvThread.createTread();
	m_recvThread.run();
	m_sendThread.createTread();
	m_sendThread.run();
	m_state = emStateLogout;
	return true;
}

bool CSession::unbind()
{
	if (m_proc.isEmpty())
	{
		return false;
	}
	m_recvThread.stop(true);
	m_sendThread.stop(true);
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
	case emStateClose:
		return true;
	default:
		return false;
	}
}
CSession* CSession::create()
{
	return new CSession();
}

void CSession::destroy()
{
	Debug("NetTerminal", "Session:%s:%d destory\n", (char*)inet_ntoa(m_addr.sin_addr), ntohs(m_addr.sin_port));
	delete this;
}

int CSession::send(const char* buf, int len)
{
	if (m_sockfd < 0)
	{
		return m_sockfd;
	}

	if (buf == NULL || len <= 0)
	{
		return -1;
	}

	char* p = (char*)buf;

	while (len > 0)
	{
		int sendlen = ::send(m_sockfd, p, len, MSG_NOSIGNAL);
		if (sendlen > 0 )
		{
			len -= sendlen;
			p += sendlen;
		}
		else if (errno == EINTR)
		{
			continue;
		}
		else
		{
			Error("NetTerminal","send err : %s\n", strerror(errno));
			return -1;
		}
	}

	return len;
}

bool CSession::transmit(const char* buf, int len)
{
	if (buf == NULL || len <= 0)
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
	packet.len = len;
	memcpy(packet.buf, buf, len);
	return m_queue.input((const char*)&packet, sizeof(struct sendPacket), 1);
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

	Debug("NetTerminal","recv:%s:%d len=%d\n", (char*)inet_ntoa(m_addr.sin_addr), ntohs(m_addr.sin_port), len);
	m_proc(this, m_pRecvbuf, len);
	
}

void CSession::sendProc(void* arg)
{
	struct sendPacket packet = {0}; // todo use heap
	if (m_queue.output((char *)&packet, sizeof(struct sendPacket), 300) > 0)
	{
		Debug("NetTerminal", "send len : %d\n", packet.len);
		send((const char*)(packet.buf), packet.len);
		return ;
	}

	Infra::CTime::delay_ms(300);
}

CSessionManager::CSessionManager()
:m_timer("SessionManager")
{
	m_timer.setTimerAttr(Infra::CTimer::TimerProc_t(&CSessionManager::timerProc, this), 3000);
	m_timer.run();
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
	CSession* pSession = CSession::create();
	
	pSession->set(sockfd, addr, timeout);
	
	registerSession(pSession);
	return pSession;
}

bool CSessionManager::cancelSession(ISession* session)
{
	//if (session == NULL)
	//{
	//	return false;
	//}
//
	//session->destroy();

	return true;
}

void CSessionManager::registerSession(ISession* session)
{
	if (session == NULL)
	{
		return ;
	}

	Infra::CGuard<Infra::CMutex> guard(m_mutex);

	std::vector<ISession*>::iterator iter = find(m_vecSession.begin(), m_vecSession.end(), session);
	if (iter == m_vecSession.end())
	{
		m_vecSession.push_back(session);
	}
}

void CSessionManager::timerProc(int arg)
{
	Infra::CGuard<Infra::CMutex> guard(m_mutex);
	std::vector<ISession*>::iterator it;
	for (it = m_vecSession.begin(); it != m_vecSession.end();)
	{
		ISession* p = *it;
		if (p->getState() == ISession::emStateClose)
		{
			p->destroy(); 
			it = m_vecSession.erase(it);
		}
		else
		{
			it++;
		}
	}

}

} //NetServer