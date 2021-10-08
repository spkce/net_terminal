
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
 * @brief ��ʼ����׿��
 */
void net_termianl_init()
{
	//��ʼ����־����
	CLog* p = CLogManager::instance()->getLog("NetTerminal");
	p->setLogType(CLog::type_modMsg);
	p->setLogLevel(CLog::logLevel_5);
	
	Debug("NetTerminal", "screen init\n");
	//��׿������
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
 * @brief ��ȡ������ָ��
 * @return ������ָ��
 */
PADAPTER_T net_terminal_adapter_get()
{
	return CAdapter::instance()->getAdapter();
}

/**
 * @brief ��ȡ��׿������״̬
 * @return ���ߣ�true�����ߣ�false
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
 * @brief ��ȡ������ָ��
 * @param mod ģ������
 * @param level �ȼ� 4:�رգ�3:���еȼ� 2:trace������ 1:warning������ 0:error
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief ��ȡ�汾��Ϣ
 * @param buf ������ 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief �������Ƿ�Ϸ�
 * @param url ������·�� 
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief ��Ϣ����
 * @param buf ��Ϣ������ 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief GPS��������
 * @param buf GPS���ݻ����� 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief �����ԱȽ������
 * @param result �ԱȽ��
 * @param similarity ���ƶ�
 * @return �ɹ�������true��ʧ�ܣ�����false
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