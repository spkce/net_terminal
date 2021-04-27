#ifndef __SESSION_H__
#define __SESSION_H__

#include "thread.h"

namespace NetServer
{

class ISession
{
protected:
	ISession();
	virtual ~ISession();
public:
	virtual bool bind(int sockfd, const Infra::ThreadProc_t & proc) = 0;
	virtual bool unbind(const Infra::ThreadProc_t & proc) = 0;
};

} //NetServer
#endif //__SESSION_H__