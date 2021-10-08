#include "stdio.h"
#include <string.h>
#include <algorithm>
#include "screen.h"
#include "NetServer.h"
#include "Session.h"
#include "IProtocl.h"
#include "Log.h"
#include "ctime.h"
#include "Adapter.h"
#include "Order.h"

using namespace std;
using namespace Terminal;
using namespace NetServer;
namespace Screen
{

/**
* @brief 构造函数
**/
CScreen::CScreen()
:ITerminal::ITerminal(ITerminal::emTerminalScree)
,m_maxSession(MAX_SESSION_MAIN)
,m_maxGpsSession(MAX_SESSION_GPS)
,m_portMain(PORT_MAIN)
,m_portGps(PORT_GPS)
,m_pServMain(NULL)
,m_pServGps(NULL)
,m_gpsSession(NULL)
,m_mainSession(NULL)
{
	m_protocl = IProtocl::createInstance(IProtocl::emProtocl_hk, this);
	m_protoclGps = IProtocl::createInstance(IProtocl::emProtocl_media, this);
}

/**
* @brief 析构函数
**/
CScreen::~CScreen()
{
#ifdef CONFIG_FENCE
	Fence::CFenceManager::instance()->detach(Fence::CFenceManager::Observer_t(&CScreen::fenceTask, this));
#endif

	m_pServGps->stop();
	m_pServMain->stop();
	IProtocl::cancelInstance(m_protocl);
	IProtocl::cancelInstance(m_protoclGps);
}

/**
* @brief 初始化
* @return 成功：true；失败：false
**/
bool CScreen::init()
{
	m_pServMain = INetServer::create(m_portMain, INetServer::emTCPServer);
	m_pServMain->attach(INetServer::ServerProc_t(&CScreen::serverTask, this));
	m_pServMain->start(m_maxSession);

	m_pServGps = INetServer::create(m_portGps, INetServer::emTCPServer);
	m_pServGps->attach(INetServer::ServerProc_t(&CScreen::servGpsTask, this));
#ifdef CONFIG_FENCE
	Fence::CFenceManager::instance()->attach(Fence::CFenceManager::Observer_t(&CScreen::fenceTask, this));
#endif
	return true;
}

/**
* @brief 获取状态
* @return 状态
**/
int CScreen::getState()
{
	//只判断主连接
	if (m_mainSession != NULL && m_mainSession->getState() == ISession::emStateLogin)
	{
		return ITerminal::emInline;
	}

	return ITerminal::emOffline;
}

/**
* @brief session 连接
* @param session 会话指针
* @param type 协议类型
* @return 成功：true；失败：false
**/
bool CScreen::connect(ISession* session, int type)
{
	if (session == NULL)
	{
		Error("NetTerminal", "input session null !!!\n");
		return false;
	}

	if (type == IProtocl::emProtocl_hk)
	{
		if (CSessionManager::instance()->getState(m_mainSession) != ISession::emStateLogin)
		{
			CSessionManager::instance()->cancelSession(m_mainSession);
			m_mainSession = session;

			if (!m_pServGps->isRun())
			{
				Trace("NetTerminal", "GPS Server run\n");
				m_pServGps->start(m_maxGpsSession);
			}
			return true;
		}
		Error("NetTerminal", "main session is login!!!\n");
	}
	else if (type == IProtocl::emProtocl_media)
	{
		if (CSessionManager::instance()->getState(m_mainSession) != ISession::emStateLogin)
		{
			Error("NetTerminal", "main session need connect first!\n");
			CSessionManager::instance()->cancelSession(session);
			return false;
		}

		if (CSessionManager::instance()->getState(m_gpsSession) != ISession::emStateLogin)
		{
			Trace("NetTerminal", "GPS session connect\n");
			m_gpsSession = session;
			return true;
		}
		else
		{
			Trace("NetTerminal", "GPS session already connect\n");
			CSessionManager::instance()->cancelSession(session);
		}
	}
	
	return false;
}

/**
* @brief session 断开连接
* @param session 会话指针
* @param type 协议类型
* @return 成功：true；失败：false
**/
bool CScreen::disconnet(ISession* session, int type)
{
	if (session == NULL)
	{
		return false;
	}

	if (type == IProtocl::emProtocl_hk)
	{
		if (session != m_mainSession)
		{
			Error("NetTerminal", "no session\n");
			return false;
		}

		Trace("NetTerminal", "main session disconnet\n");
		CSessionManager::instance()->cancelSession(m_mainSession);
		m_mainSession = NULL;

		if (m_pServGps->isRun())
		{
			m_pServGps->stop();
			Trace("NetTerminal", "GPS Server stop\n");
			CSessionManager::instance()->cancelSession(m_gpsSession);
			m_gpsSession = NULL;
		}
		return true;
	}
	else if (type == IProtocl::emProtocl_media)
	{
		if (m_gpsSession == session)
		{
			Trace("NetTerminal", "GPS session disconnet\n");
			CSessionManager::instance()->cancelSession(session);
			m_gpsSession = NULL;
			return true;
		}
	}
	
	return false;
}

/**
* @brief 获取版本信息
* @param ver 版本信息
* @return 成功/失败
**/
bool CScreen::getVersion(std::string & ver)
{
	if (CSessionManager::instance()->getState(m_mainSession) == ISession::emStateLogin)
	{
		m_protocl->getVersion(ver);
		return true;
	}
	return false;
}

/**
* @brief 消息推送
* @param buf 消息内容
* @param len 消息长度
* @return 成功：true；失败：false
**/
bool CScreen::notify(char* buf, int len)
{
	if (buf == NULL || len <= 0)
	{
		Error("NetTerminal", "Input Param NULL\n");
		return false;
	}

	if (CSessionManager::instance()->getState(m_mainSession) != ISession::emStateLogin)
	{
		Error("NetTerminal", "screen connection dropped\n");
		return false;
	}

	return m_protocl->notify(m_mainSession, buf, len);
}

/**
* @brief GPS数据推送
* @param buf GPS数据内容
* @param len GPS数据长度
* @return 成功：true；失败：false
**/
bool CScreen::pushGps(char* buf, int len)
{
	if (CSessionManager::instance()->getState(m_mainSession) != ISession::emStateLogin)
	{
		if (CSessionManager::instance()->getState(m_gpsSession) == ISession::emStateLogin)
		{
			CSessionManager::instance()->cancelSession(m_gpsSession);
		}
		return false;
	}

	
	if (CSessionManager::instance()->getState(m_gpsSession) == ISession::emStateLogin)
	{
		return m_protoclGps->notify(m_gpsSession, buf, len);
	}

	return false;
}

/**
* @brief 服务器回调函数
* @param sockfd 套接字句柄
* @param addr 对端套接字地址
**/
bool CScreen::serverTask(int sockfd, struct sockaddr_in* addr)
{
	if (CSessionManager::instance()->getState(m_mainSession) == ISession::emStateLogin)
	{
		Warning("NetTerminal", "Gps Session was registered !\n");
		return false;
	}

	ISession* pSession = CSessionManager::instance()->createSession(sockfd, addr, 15);
	if (pSession == NULL)
	{
		return false;
	}

	if (!pSession->bind(ISession::SessionProc_t(&CScreen::sessionTask, this)))
	{
		CSessionManager::instance()->cancelSession(pSession);
	}
	return true;
}

/**
* @brief 会话回调函数
* @param session 会话指针
* @param buf 消息内容
* @param len 消息长度
**/
void CScreen::sessionTask(NetServer::ISession* session, char* buf, int len)
{
	if (session == NULL || buf == NULL || len <= 0)
	{
		return ;
	}
	m_protocl->parse(session, buf, len);
}

/**
* @brief GPS务器回调函数
* @param sockfd 套接字句柄
* @param addr 对端套接字地址
**/
bool CScreen::servGpsTask(int sockfd, struct sockaddr_in* addr)
{
	if (CSessionManager::instance()->getState(m_gpsSession) == ISession::emStateLogin)
	{
		Warning("NetTerminal", "Gps Session was registered !\n");
		return false;
	}

	ISession* pSession = CSessionManager::instance()->createSession(sockfd, addr);
	if (pSession == NULL)
	{
		return false;
	}

	if (!pSession->bind(ISession::SessionProc_t(&CScreen::pushGpsTask, this)))
	{
		CSessionManager::instance()->cancelSession(pSession);
	}

	return true;
}

/**
* @brief 会话回调函数
* @param session 会话指针
* @param buf 消息内容
* @param len 消息长度
**/
void CScreen::pushGpsTask(NetServer::ISession* session, char* buf, int len)
{
	if (session == NULL || buf == NULL || len <= 0)
	{
		return ;
	}

	m_protoclGps->parse(session, buf, len);
}

#ifdef CONFIG_FENCE
void CScreen::fenceTask(int event, int param1, int param2, void *p)
{
	switch (event)
	{
	case emFenceEvent_add:
	case emFenceEvent_mod:
	case emFenceEvent_del:
	{
		char msg[sizeof(MsgHdr_t) + sizeof(AreaInfo_t)] = {0};
		PtrMsgHdr_t phdr = (PtrMsgHdr_t)msg;
		phdr->msgID = IOrder::AE_SEND_AREA_INFO;

		PtrAreaInfo_t pArea = (PtrAreaInfo_t)(msg + sizeof(MsgHdr_t));
		pArea->event = event;
		pArea->type = param1;
		pArea->id = param2;

		if (notify(msg, sizeof(MsgHdr_t) + sizeof(AreaInfo_t)))
		{
			Trace("NetTerminal", "send fence success\n");
		}
		else
		{
			Error("NetTerminal", "send fence fail\n");
		}
	}
	break;
	case emFenceEvent_clr:
	{
		char msg[sizeof(MsgHdr_t) + sizeof(AreaInfo_t)] = {0};
		PtrMsgHdr_t phdr = (PtrMsgHdr_t)msg;
		phdr->msgID = IOrder::AE_CLEAR_ALL_AREA_INFO;

		PtrAreaInfo_t pArea = (PtrAreaInfo_t)(msg + sizeof(MsgHdr_t));
		pArea->event = event;
		pArea->type = param1;
		pArea->id = 0;

		if (notify(msg, sizeof(MsgHdr_t) + sizeof(AreaInfo_t)))
		{
			Trace("NetTerminal", "send clear fence success\n");
		}
		else
		{
			Error("NetTerminal", "send clear fence fail\n");
		}
	}
	break;
	default: break;
	}
}
#endif
} // Screen
