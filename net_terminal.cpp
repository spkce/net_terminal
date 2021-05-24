
#include "net_terminal.h"

#include "screen.h"
#include "Adapter.h"

#ifdef __cplusplus
extern "C" {
#endif



void net_termianl_init()
{
	//NetServer::CNetServer::instance()->start(8888, 5);
	Screen::CScreen* p =  new Screen::CScreen();
	p->init();

}

PADAPTER_T net_terminal_adapter_get()
{
	return CAdapter::instance()->getAdapter();
}

#ifdef __cplusplus
}
#endif