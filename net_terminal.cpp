
#include "stdio.h"
#include "net_terminal.h"
#include "Log.h"
#include "terminal.h"
#include "Adapter.h"

#ifdef __cplusplus
extern "C" {
#endif


Terminal::ITerminal * g_pScreen = NULL;

/**
 * @brief 初始化安卓屏
 */
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

/**
 * @brief 获取适配器指针
 * @return 适配器指针
 */
PADAPTER_T net_terminal_adapter_get()
{
	return CAdapter::instance()->getAdapter();
}

/**
 * @brief 消息推送
 * @param buf 消息缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_notify(char* buf, int len)
{
	if (buf == NULL || len <= 0)
	{
		return (int)false;
	}

	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "screen no initialization\n");
		return (int)false;
	}

	return (int)g_pScreen->notify(buf, len);
}

/**
 * @brief GPS数据推送
 * @param buf GPS数据缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_pushGPS(char* buf, int len)
{
	if (buf == NULL || len <= 0)
	{
		return (int)false;
	}

	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "screen no initialization\n");
		return (int)false;
	}

	return (int)g_pScreen->pushGps(buf, len);
}

#ifdef __cplusplus
}
#endif