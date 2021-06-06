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
* @brief ���캯����
* @param terminal �ն�ָ��
**/
CMediaProtocl::CMediaProtocl(Terminal::ITerminal* terminal)
:m_pTerminal(terminal)
{

}

/**
* @brief ����������
**/
CMediaProtocl::~CMediaProtocl()
{

}

/**
* @brief Э���������
* @param session �Ự��ָ��
* @param buf ���յ�������
* @param len ���յ������ݳ���
* @return �ɹ�/ʧ��
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
* @brief ��¼
* @param session �Ự��ָ��
* @return �ɹ�/ʧ��
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
* @brief ������Ϣ
* @param session �Ự��ָ��
* @param buf ���յ�������
* @param len ���յ������ݳ���
* @return �ɹ�/ʧ��
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
	pResHdr->totalSzie = 0; //(�ݲ�ʶ��)

	int copyLen = len < (int)sizeof(sendDate) ? len : sizeof(sendDate);
	memcpy(sendDate + sizeof(MediaResHder), buf, copyLen);
	pResHdr->packetSzie = copyLen;
	copyLen += sizeof(MediaResHder);
	return sendPacket(session, sendDate, copyLen);
}

/**
* @brief ���ͻذ�
* @param session �Ự��ָ��
* @param param ����APP�˲���
* @param buf ���͵ı���
* @param len ���͵ı��ĳ���
* @return �ɹ�/ʧ��
**/
bool CMediaProtocl::reply(NetServer::ISession* session, const char *buf, int len)
{
	return session->send(buf, len);
}

/**
* @brief ���Ͱ�
* @param session �Ự��ָ��
* @param param ����APP�˲���
* @param buf ���͵ı���
* @param len ���͵ı��ĳ���
* @return �ɹ�/ʧ��
**/
bool CMediaProtocl::sendPacket(NetServer::ISession* session, const char *buf, int len)
{
	return session->transmit(buf, len);
}

}//Screen

