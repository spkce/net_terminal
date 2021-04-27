#ifndef __NET_SERVER_H__
#define __NET_SERVER_H__

#include "thread.h"

namespace NetServer
{
class CNetServer
{
private:
	CNetServer();
	~CNetServer();
public:
	static CNetServer* instance();

	bool start(unsigned int port, bool isTcp = true);

	bool stop();

private:
	void server_task(void* arg);

private:
	int m_sockfd;
	Infra::CThread* m_pThread;
};



} //NetServer
#endif //__NET_SERVER_H__
