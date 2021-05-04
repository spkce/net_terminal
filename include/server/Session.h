#ifndef __SESSION_H__
#define __SESSION_H__

#include "thread.h"
#include "timer.h"
#include <vector>
namespace NetServer
{

class ISession
{
public:
	typedef Infra::TFuncation3<void, ISession*, char*, int> SessionProc_t;
	typedef  enum state_t
	{
		emStateCreated,
		emStateLogout,
		emStateLogin,
		emStateClose,
	}state_t;
protected:
	ISession(){};
	virtual ~ISession(){};
public:
	virtual bool bind(const SessionProc_t & proc) = 0;
	virtual bool unbind() = 0;
	
	virtual bool login() = 0;
	virtual bool logout() = 0;
	virtual bool keepAlive() = 0;
	
	virtual state_t getState() = 0;
	
	virtual bool close() = 0;
	virtual void destroy() = 0;
};

class CSessionManager
{
private:
	CSessionManager();
	~CSessionManager();
public:
	static CSessionManager* instance();

	ISession* createSession(int sockfd, struct sockaddr_in* addr, int timeout);

private:
	bool cancelSession(ISession* session);

	void timerProc(int arg);

	Infra::CTimer m_timer;
	Infra::CMutex m_mutex;
	std::vector<ISession*> m_vecSession;
	
};



} //NetServer
#endif //__SESSION_H__