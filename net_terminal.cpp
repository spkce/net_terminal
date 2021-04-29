
#include "net_terminal.h"

#include "screen.h"

#ifdef __cplusplus
extern "C" {
#endif



void net_termianl_init()
{
	//NetServer::CNetServer::instance()->start(8888, 5);
	Screen::CScreen* p =  new Screen::CScreen();
	p->init();

}

#ifdef __cplusplus
}
#endif