#include <string.h>
#include <arpa/inet.h>
#include "terminal.h"
#include "MediaProtocl.h"
#include "Log.h"
#include <algorithm>
#include "Session.h"

namespace Screen
{

/**
* @brief 构造函数，
* @param terminal 终端指针
**/
CMediaProtocl::CMediaProtocl(Terminal::ITerminal* terminal)
:m_pTerminal(terminal)
{

}

/**
* @brief 析构函数，
**/
CMediaProtocl::~CMediaProtocl()
{

}

/**
* @brief 协议解析函数
* @param session 会话话指针
* @param buf 接收到的内容
* @param len 接收到的内容长度
* @return 成功/失败
**/
bool CMediaProtocl::parse(NetServer::ISession* session, char* buf, int len)
{
	if (len < (int)sizeof(MediaReqHder))
	{
		Error("NetTerminal", "date too short\n");
		return false;
	}

	MediaReqHder* pReqhdr = (MediaReqHder*)buf;
	if (pReqhdr->startCode != htons(REQ_START_CODE) || pReqhdr->msgID != htons(emReqMedia))
	{
		Error("NetTerminal", "start code no match\n");
		return false;
	}

	MediaResHder resHdr = {0};
	resHdr.startCode = htons(RES_START_CODE);
	resHdr.msgID = htons(emReqMedia);
	resHdr.retVal = htonl(emError);
	resHdr.packetSzie = 0;
	resHdr.totalSzie = 0;

	char path[116] = {0};

	len = len - sizeof(MediaReqHder);
	int copylen = len < (int)sizeof(path) ? len : sizeof(path);
	strncpy(path, buf + sizeof(MediaReqHder), copylen);

	if (std::string(path) == "GPS_NMEA")
	{
		if (login(session))
		{
			resHdr.retVal = htonl(emNoError);
			Error("NetTerminal", "login success\n");
		}
	}
	
	return reply(session, (const char*)&resHdr, sizeof(MediaResHder));
}

/**
* @brief 登录
* @param session 会话话指针
* @return 成功/失败
**/
bool CMediaProtocl::login(NetServer::ISession* session)
{
	if (m_pTerminal->connect(session, emProtocl_media))
	{
		return session->login();
	}

	return false;
}

/**
* @brief 推送消息
* @param session 会话话指针
* @param buf 接收到的内容
* @param len 接收到的内容长度
* @return 成功/失败
**/
bool CMediaProtocl::notify(NetServer::ISession* session, char* buf, int len)
{
	if (buf == NULL || len <= 0)
	{
		return 0;
	}

	char sendDate[1024] = {0};
	MediaResHder* pResHdr = (MediaResHder*)sendDate;
	pResHdr->startCode = htons(RES_START_CODE);
	pResHdr->msgID = htons(emReqMedia);
	pResHdr->retVal = htonl(emError);
	pResHdr->totalSzie = 0; //(暂不识别)

	int copyLen = len < (int)sizeof(sendDate) ? len : sizeof(sendDate);
	memcpy(sendDate + sizeof(MediaResHder), buf, copyLen);
	pResHdr->packetSzie = copyLen;
	copyLen += sizeof(MediaResHder);
	return sendPacket(session, sendDate, copyLen);
}

/**
* @brief 发送回包
* @param session 会话话指针
* @param param 返回APP端参数
* @param buf 发送的报文
* @param len 发送的报文长度
* @return 成功/失败
**/
bool CMediaProtocl::reply(NetServer::ISession* session, const char *buf, int len)
{
	return session->send(buf, len);
}

/**
* @brief 发送包
* @param session 会话话指针
* @param param 返回APP端参数
* @param buf 发送的报文
* @param len 发送的报文长度
* @return 成功/失败
**/
bool CMediaProtocl::sendPacket(NetServer::ISession* session, const char *buf, int len)
{
	return session->transmit(buf, len);
}

}//Screen

