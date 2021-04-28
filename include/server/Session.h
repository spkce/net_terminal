#ifndef __SESSION_H__
#define __SESSION_H__

#include "thread.h"
#include "jsoncpp.h"

namespace NetServer
{

typedef Infra::TFuncation2<void, Json::Value&, Json::Value&> SessionProc_t;

class ISession
{
protected:
	ISession(){};
	virtual ~ISession(){};
public:
	virtual bool bind(const SessionProc_t & proc) = 0;
	virtual bool unbind() = 0;
//virtual bool destroy() = 0;
};

class CSessionManager
{
private:
	CSessionManager();
	~CSessionManager();
public:
	static CSessionManager* instance();

	ISession* createSession(int sockfd, struct sockaddr_in* addr);
	bool cancelSession(ISession* session);

};



} //NetServer
#endif //__SESSION_H__