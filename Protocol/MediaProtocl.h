#ifndef __MEDIA_PROTOCL_H__
#define __MEDIA_PROTOCL_H__

#include "IProtocl.h"

namespace NetServer {
	class ISession;
}

namespace Terminal {
	class ITerminal;
}

namespace Screen
{

/**
* @brief media 推送协议
**/
class CMediaProtocl : public IProtocl
{
#define REQ_START_CODE 0xAABB /*请求包头标识符*/
#define RES_START_CODE 0xBBAA /*请求包头标识符*/
	/**
	* @brief 请求ID
	**/
	enum
	{
		emReqMedia = 0xB90B,
	};
	
	/**
	* @brief 错误码
	**/
	enum
	{
		emNoError = 0,
		emError = 2,
	};
	/**
	* @brief 请求头
	**/
	typedef struct tagMediaReqHder
	{
		unsigned short startCode;
		unsigned short msgID;
		unsigned int seekType;
		unsigned int seek;
		unsigned int resolution;
	}MediaReqHder;

	/**
	* @brief 回复头
	**/
	typedef struct tagMediaResHder
	{
		unsigned short startCode;
		unsigned short msgID;
		unsigned int retVal;
		unsigned int packetSzie;
		unsigned int totalSzie;
	}MediaResHder;
public:
	/**
	* @brief 构造函数，
	* @param terminal 终端指针
	**/
	CMediaProtocl(Terminal::ITerminal* terminal);

	/**
	* @brief 析构函数，
	**/
	virtual ~CMediaProtocl();

	/**
	* @brief 协议解析函数
	* @param session 会话话指针
	* @param buf 接收到的内容
	* @param len 接收到的内容长度
	* @return 成功/失败
	**/
	virtual bool parse(NetServer::ISession* session, char* buf, int len);

	/**
	* @brief 推送消息
	* @param msgID 消息ID
	* @param buf 接收到的内容
	* @param len 接收到的内容长度
	* @return 成功/失败
	**/
	virtual bool notify(NetServer::ISession* session, char* buf, int len);

	/**
	* @brief 登录
	* @param session 会话话指针
	* @return 成功/失败
	**/
	virtual bool login(NetServer::ISession* session);

private:
	/**
	* @brief 发送回包
	* @param session 会话话指针
	* @param param 返回APP端参数
	* @param buf 发送的报文
	* @param len 发送的报文长度
	* @return 成功/失败
	**/
	bool reply(NetServer::ISession* session, const char *buf, int len);

	/**
	* @brief 发送包
	* @param session 会话话指针
	* @param param 返回APP端参数
	* @param buf 发送的报文
	* @param len 发送的报文长度
	* @return 成功/失败
	**/
	bool sendPacket(NetServer::ISession* session, const char *buf, int len);

private:
	Terminal::ITerminal* m_pTerminal; //终端指针
};

}//Screen

#endif // __GPS_PROTOCL_H__
