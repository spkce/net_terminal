#ifndef __TERMINAL_H__
#define __TERMINAL_H__

namespace NetServer {
	class ISession;
}
namespace Terminal
{

class ITerminal
{
public:
	enum
	{
		emTerminalScree,	
	};
protected:
	ITerminal();
	virtual ~ITerminal();
	
public:
	virtual bool init() = 0;

	virtual bool connect(NetServer::ISession* session) = 0;

	virtual bool disconnet(NetServer::ISession* session) = 0;

protected:
	int m_type;
};

} // Terminal
#endif //__TERMINAL_H__
