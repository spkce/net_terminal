#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "terminal.h"

struct sockaddr_in;

namespace NetServer {
	class INetServer;
	class ISession;
}
namespace Screen
{

class IScreenProtocl;
class CScreen : public Terminal::ITerminal
{
private:

public:
	CScreen();
	virtual ~CScreen();

	bool init();

	void serverTask(int sockfd, struct sockaddr_in* addr);
	void sessionTask(char* buf, int len);
private:
	NetServer::INetServer* m_pServ;
	IScreenProtocl* m_protocl;
};



} // Screen
#endif //__SCREEN_H__