
#include "stdio.h"
#include "net_terminal.h"
#include "Log.h"
#include "terminal.h"
#include "Adapter.h"
 #include <string.h>

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
 * @brief 获取安卓屏连接状态
 * @return 在线：true；离线：false
 */
int net_termianl_is_inline()
{
	if (g_pScreen == NULL)
	{
		return false;
	}

	if (g_pScreen->getState() == Terminal::ITerminal::emInline)
	{
		return true;
	}

	return false;
}

/**
 * @brief 获取适配器指针
 * @param mod 模块名字
 * @param level 等级 4:关闭，3:所有等级 2:trace及以上 1:warning及以上 0:error
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_debug_set(const char* mod, int level)
{
	CLog* p = CLogManager::instance()->findLog(mod);
	if (p == NULL)
	{
		return (int)false;
	}
	
	switch (level)
	{
	case 4:
		p->setLogLevel(CLog::logLevel_0);
		break;
	case 3:
		p->setLogLevel(CLog::logLevel_5);
		break;
	case 2:
		p->setLogLevel(CLog::logLevel_3);
		break;
	case 1:
		p->setLogLevel(CLog::logLevel_2);
		break;
	case 0:
		p->setLogLevel(CLog::logLevel_1);
		break;
	default:
		return (int)false;
	}
	return (int)true;
}
/**
 * @brief 获取版本信息
 * @param buf 缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_get_version(char* buf, unsigned int len)
{
	if (buf == NULL || len == 0)
	{
		return (int)false;
	}

	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "screen no initialization\n");
		return (int)false;
	}
	std::string ver;
	int ret = g_pScreen->getVersion(ver);
	if (ret)
	{
		strncpy(buf, ver.c_str(), (size_t)len);
	}
	
	return ret;
}

/**
 * @brief 升级包是否合法
 * @param url 升级包路径 
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_upgrade_check(const char* url)
{
	if (url == NULL)
	{
		return (int)false;
	}

	std::string urlStr(url);
	std::string filename = urlStr.substr(urlStr.find_last_of('/') + 1);
	Trace("NetTerminal", "filename = %s\n", filename.c_str());

	if (filename.find("update") != filename.npos)
	{
		return (int)true;
	}

	return (int)false;
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

/**
 * @brief 人脸对比结果发送
 * @param result 对比结果
 * @param similarity 相似度
 * @return 成功：返回true；失败：返回false
 */
void net_terminal_face_contrast_result(int result, unsigned int similarity)
{
	char msg[sizeof(MSG_HDR_T) + sizeof(Notification_t)] = {0};
	PtrMsgHdr_t phdr = (PtrMsgHdr_t)msg;
	phdr->msgID = 601;
	PtrNotification_t pNotify = (PtrNotification_t)(msg + sizeof(MsgHdr_t));
	strncpy(pNotify->type, "faceResult", sizeof(pNotify->type));
	pNotify->faceResult.result = result;
	pNotify->faceResult.similarity = similarity;
	g_pScreen->notify(msg, sizeof(MsgHdr_t) + sizeof(Notification_t));
}

#ifdef __cplusplus
}
#endif