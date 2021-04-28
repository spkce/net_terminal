#ifndef __NET_SERVER_H__
#define __NET_SERVER_H__

#include "thread.h"

struct sockaddr_in;

namespace NetServer
{
class INetServer
{
public:
	typedef Infra::TFuncation2<void, int, struct sockaddr_in*> ServerProc_t;
protected:
	INetServer();
	virtual ~INetServer();
public:
	virtual bool start(unsigned int maxlisten) = 0;
	virtual bool attach(ServerProc_t proc) = 0;
	virtual bool stop() = 0;

};

class CNetServer : public INetServer
{
private:
	CNetServer(unsigned int port, bool isTcp);
	~CNetServer();
public:
	static INetServer* create(unsigned int port, bool isTcp = true);

	virtual bool attach(INetServer::ServerProc_t proc);
	bool start(unsigned int maxlisten);

	bool stop();

private:
	void server_task(void* arg);

private:
	INetServer::ServerProc_t m_proc;
	Infra::CThread* m_pThread;
	int m_sockfd;
	int m_port;
	bool m_isTcp;
	
};



} //NetServer
#endif //__NET_SERVER_H__
