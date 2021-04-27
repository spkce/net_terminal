
#include "net_terminal.h"
#include "NetServer.h"
#ifdef __cplusplus
extern "C" {
#endif



void net_termianl_init()
{
	NetServer::CNetServer::instance()->start(80);

}

#ifdef __cplusplus
}
#endif