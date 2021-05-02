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
	typedef enum Type_t
	{
		emTCPServer,
		emUDPServer,
	}Type_t;
protected:
	INetServer();
	virtual ~INetServer();
public:
	static INetServer* create(unsigned int port, Type_t type);
	virtual bool start(unsigned int maxlisten) = 0;
	virtual bool attach(ServerProc_t proc) = 0;
	virtual bool stop() = 0;
};





} //NetServer
#endif //__NET_SERVER_H__
