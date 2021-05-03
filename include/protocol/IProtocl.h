#ifndef __I_PROTOCL_H__
#define __I_PROTOCL_H__

namespace NetServer {
	class ISession;
}

namespace Screen
{

class IProtocl
{	
public:
	typedef  enum protocl_t
	{
		emProtocl_hk,
	}protocl_t;
protected:
	IProtocl();
	virtual ~IProtocl();
public:
	static IProtocl * createInstance(protocl_t type);
	static void cancelInstance(IProtocl * protocl);

	virtual bool parse(NetServer::ISession* session, char* buf, int len) = 0;
};





} //Screen

#endif //__I_PROTOCL_H__
