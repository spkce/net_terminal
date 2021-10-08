#ifndef __SCREEN_H__
#define __SCREEN_H__
#include <vector>
#include "thread.h"
#include "terminal.h"
#include "MsgQueue.h"
#ifdef CONFIG_FENCE
#include "FenceManager.h"
#endif

struct sockaddr_in;

namespace NetServer {
	class INetServer;
	class ISession;
}
namespace Screen
{

class IProtocl;
class CScreen : public Terminal::ITerminal
{
public:
	/**
	* @brief 构造函数
	**/
	CScreen();

	/**
	* @brief 析构函数
	**/
	virtual ~CScreen();

	/**
	* @brief 初始化
	* @return 成功：true；失败：false
	**/
	virtual bool init();

	/**
	* @brief 获取状态
	* @return 状态
	**/
	virtual int getState();

	/**
	* @brief session 连接
	* @param session 会话指针
	* @param type 协议类型
	* @return 成功：true；失败：false
	**/
	virtual bool connect(NetServer::ISession* session, int type);

	/**
	* @brief session 断开连接
	* @param session 会话指针
	* @param type 协议类型
	* @return 成功：true；失败：false
	**/
	virtual bool disconnet(NetServer::ISession* session, int type);
	/**
	* @brief 获取版本信息
	* @param ver 版本信息
	* @return 成功/失败
	**/
	virtual bool getVersion(std::string & ver);
	/**
	* @brief 消息推送
	* @param buf 消息内容
	* @param len 消息长度
	* @return 成功：true；失败：false
	**/
	virtual bool notify(char* buf, int len);

	/**
	* @brief GPS数据推送
	* @param buf GPS数据内容
	* @param len GPS数据长度
	* @return 成功：true；失败：false
	**/
	virtual bool pushGps(char* buf, int len);
	
	/**
	* @brief 服务器回调函数
	* @param sockfd 套接字句柄
	* @param addr 对端套接字地址
	* @return 成功：true；失败：false
	**/
	bool serverTask(int sockfd, struct sockaddr_in* addr);
	
	/**
	* @brief 会话回调函数
	* @param session 会话指针
	* @param buf 消息内容
	* @param len 消息长度
	**/
	void sessionTask(NetServer::ISession* session, char* buf, int len);
	
	/**
	* @brief GPS务器回调函数
	* @param sockfd 套接字句柄
	* @param addr 对端套接字地址
	* @return 成功：true；失败：false
	**/
	bool servGpsTask(int sockfd, struct sockaddr_in* addr);
	
	/**
	* @brief 会话回调函数
	* @param session 会话指针
	* @param buf 消息内容
	* @param len 消息长度
	**/
	void pushGpsTask(NetServer::ISession* session, char* buf, int len);

#ifdef CONFIG_FENCE
	/**
	* @brief 围栏信息回调函数
	* @param session 会话指针
	* @param buf 消息内容
	* @param len 消息长度
	**/
	void fenceTask(int event, int param1, int param2, void* p);
#endif

private:
#define PORT_MAIN 7877
#define PORT_GPS 8881
#define MAX_SESSION_MAIN 5
#define MAX_SESSION_GPS 1
	const int m_maxSession;
	const int m_maxGpsSession;
	const int m_portMain;
	const int m_portGps;
	NetServer::INetServer* m_pServMain;
	NetServer::INetServer* m_pServGps;
	IProtocl* m_protocl;
	IProtocl* m_protoclGps;
	NetServer::ISession* m_gpsSession;
	NetServer::ISession* m_mainSession;

};



} // Screen
#endif //__SCREEN_H__