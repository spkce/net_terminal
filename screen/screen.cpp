#include "stdio.h"
#include <string.h>
#include <algorithm>
#include "screen.h"
#include "NetServer.h"
#include "Session.h"
#include "IProtocl.h"
#include "Log.h"
#include "ctime.h"

using namespace std;
using namespace Terminal;
using namespace NetServer;
namespace Screen
{

/**
* @brief 构造函数
**/
CScreen::CScreen()
:m_maxSession(MAX_SESSION_MAIN)
,m_maxGpsSession(MAX_SESSION_GPS)
,m_portMain(PORT_MAIN)
,m_portGps(PORT_GPS)
,m_pServMain(NULL)
,m_pServGps(NULL)
,m_gpsSession(NULL)
,m_mainSession(NULL)
{
	m_type = ITerminal::emTerminalScree;
	m_protocl = IProtocl::createInstance(IProtocl::emProtocl_hk, this);
	m_protoclGps = IProtocl::createInstance(IProtocl::emProtocl_media, this);
}

/**
* @brief 析构函数
**/
CScreen::~CScreen()
{
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
		return false;
	}

	if (type == IProtocl::emProtocl_hk)
	{
		if (m_mainSession == NULL || m_mainSession->getState() != ISession::emStateLogin)
		{
			if (m_mainSession != NULL)
			{
				m_mainSession->close();
			}

			m_mainSession = session;
			if (!m_pServGps->isRun())
			{
				Trace("NetTerminal", "GPS Server run\n");
				m_pServGps->start(m_maxGpsSession);
			}
			return true;
		}
	}
	else if (type == IProtocl::emProtocl_media)
	{
		if (m_mainSession == NULL || m_mainSession->getState() != ISession::emStateLogin)
		{
			Error("NetTerminal", "main session need connect first!\n");
			return false;
		}

		if (m_gpsSession == NULL || m_gpsSession->getState() != ISession::emStateLogin)
		{
			Trace("NetTerminal", "GPS session connect\n");
			if (m_gpsSession != NULL)
			{
				m_gpsSession->close();
			}

			m_gpsSession = session;
			return true;
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
		m_mainSession->close();
		m_mainSession = NULL;

		if (m_pServGps->isRun())
		{
			m_pServGps->stop();
			Trace("NetTerminal", "GPS Server stop\n");
			if (m_gpsSession != NULL)
			{
				m_gpsSession->close();
			}
		}
		return true;
	}
	else if (type == IProtocl::emProtocl_media)
	{
		if (m_gpsSession == session)
		{
			Trace("NetTerminal", "GPS session disconnet\n");
			session->close();
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
	if (m_mainSession != NULL && m_mainSession->getState() == ISession::emStateLogin)
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

	if (m_mainSession == NULL)
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
	if (m_gpsSession != NULL)
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
void CScreen::serverTask(int sockfd, struct sockaddr_in* addr)
{
	if (m_mainSession != NULL && m_mainSession->getState() == ISession::emStateLogin)
	{
		Warning("NetTerminal", "Gps Session was registered !\n");
		return;
	}

	ISession* pSession = CSessionManager::instance()->createSession(sockfd, addr, 15);
	if (pSession == NULL)
	{
		return ;
	}

	pSession->bind(ISession::SessionProc_t(&CScreen::sessionTask, this));
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
void CScreen::servGpsTask(int sockfd, struct sockaddr_in* addr)
{
	if (m_gpsSession != NULL && m_gpsSession->getState() == ISession::emStateLogin)
	{
		Warning("NetTerminal", "Gps Session was registered !\n");
		return;
	}

	ISession* pSession = CSessionManager::instance()->createSession(sockfd, addr);
	if (pSession == NULL)
	{
		return ;
	}

	pSession->bind(ISession::SessionProc_t(&CScreen::pushGpsTask, this));
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

} // Screen
