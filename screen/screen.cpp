#include "stdio.h"
#include "screen.h"
#include "NetServer.h"
#include "Session.h"
#include "ScreenProtocl.h"

using namespace Terminal;
using namespace NetServer;
namespace Screen
{

CScreen::CScreen()
:m_pServ(NULL)
{
	m_type = ITerminal::emTerminalScree;
}

CScreen::~CScreen()
{
}

bool CScreen::init()
{
	m_protocl = IScreenProtocl::getInstance();
	m_pServ = INetServer::create(7877, INetServer::emTCPServer);
	m_pServ->attach(INetServer::ServerProc_t(&CScreen::serverTask, this));
	m_pServ->start(5);

	return true;
}

void CScreen::serverTask(int sockfd, struct sockaddr_in* addr)
{
	ISession* pSession = CSessionManager::instance()->createSession(sockfd, addr, 15);

	pSession->bind(ISession::SessionProc_t(&CScreen::sessionTask, this));

}

void CScreen::sessionTask(char* buf, int len)
{
	m_protocl->parse(buf, len);
}

} // Screen