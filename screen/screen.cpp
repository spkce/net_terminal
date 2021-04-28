
#include "screen.h"
#include "NetServer.h"

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
	m_pServ = CNetServer::create(8888);
	m_pServ->attach(INetServer::ServerProc_t(&CScreen::serverTask, this));
	m_pServ->start(5);
}

void CScreen::serverTask(int sockfd, struct sockaddr_in* addr)
{

}

} // Screen