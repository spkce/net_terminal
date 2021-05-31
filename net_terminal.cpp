
#include "stdio.h"
#include "net_terminal.h"
#include "Log.h"
#include "terminal.h"
#include "Adapter.h"

#ifdef __cplusplus
extern "C" {
#endif


Terminal::ITerminal * g_pScreen = NULL;

void net_termianl_init()
{
	//初始化日志功能
	CLog* p = CLogManager::instance()->getLog("NetTerminal");
	p->setLogType(CLog::type_modMsg);
	p->setLogLevel(CLog::logLevel_5);
	
	Debug("NetTerminal", "screen init\n");
	//安卓屏创建
	g_pScreen = Terminal::ITerminal::createTerminal(Terminal::ITerminal::emTerminalScree);
	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "create screen fail\n");
		return ;
	}

	if (!g_pScreen->init())
	{
		Error("NetTerminal", "screen init fail\n");
		return ;
	}
}

PADAPTER_T net_terminal_adapter_get()
{
	return CAdapter::instance()->getAdapter();
}

void net_terminal_notify(char* buf, int len)
{
	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "screen no initialization\n");
		return ;
	}

	g_pScreen->notify(buf, len);
}

#ifdef __cplusplus
}
#endif