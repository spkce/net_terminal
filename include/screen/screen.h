#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "terminal.h"

struct sockaddr_in;

namespace NetServer {
	class INetServer;
}
namespace Screen
{

class CScreen : public Terminal::ITerminal
{
private:

public:
	CScreen();
	virtual ~CScreen();

	bool init();

	void serverTask(int sockfd, struct sockaddr_in* addr);
private:
	NetServer::INetServer* m_pServ;
};



} // Screen
#endif //__SCREEN_H__