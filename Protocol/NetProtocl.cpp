
#include "IProtocl.h"
#include "jsoncpp.h"
#include "openssl/aes.h"
#include "openssl/rand.h"
#include "openssl/evp.h"
#include "aes_encrypt.h"
#include "rsa_app.h"
#include "Session.h"
#include "NetProtocl.h"
#include "terminal.h"
#include <arpa/inet.h>
#include "Order.h"

using namespace NetServer;
namespace Screen
{

/**
* @brief 构造函数，
* @param terminal 终端指针
**/
CNetProtocl::CNetProtocl(Terminal::ITerminal* terminal)
:m_pTerminal(terminal)
{

}

/**
* @brief 析构函数，
**/
CNetProtocl::~CNetProtocl()
{
}

/**
* @brief 报文解析
* @param session 会话话指针
* @param buf 接收到的内容
* @param len 接收到的内容长度
* @return 成功/失败
**/
bool CNetProtocl::parse(ISession * session, char* buf, int len)
{
	if (session->getState() == ISession::emStateLogin)
	{
		messageProcess(session, buf, len);
		printf("\033[35m""%s:%d %s ""\033[0m\n",__FILE__, __LINE__, __FUNCTION__);
		return true;
	}
	else
	{
		return handShake(session, buf, len);
	}
}

/**
* @brief 消息处理
* @param session 会话话指针
* @param buf 接收到的内容
* @param len 接收到的内容长度
* @return 成功/失败
**/
bool CNetProtocl::messageProcess(NetServer::ISession* session, char* buf, int len)
{
		bool res = false;
		unsigned int uReqIdx = 0;
		unsigned int uDateLen = 0;
		if (!headerCheck(buf, &uReqIdx, &uDateLen))
		{
			printf("\033[35m""header Check err""\033[0m\n");
			return false;
		}

		char dataBuf[NET_APP_RECV_SIZE] = {0};
		int uLen = 0;
		decrypt(buf + sizeof(struct msgHeader), uDateLen, dataBuf, &uLen);
		std::string recv = dataBuf;
		Json::String errs;
		Json::Value request;
		Json::CharReaderBuilder readerBuilder;
		std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
		res = jsonReader->parse(recv.c_str(), recv.c_str() + recv.length(), &request, &errs);
		if (!res || !errs.empty())
		{
			printf("\033[35m""parse:%s""\033[0m\n", errs.c_str());
			return false;
		}
	
		printf("\033[35m""request = %s""\033[0m\n", request.toStyledString().c_str());

		if (request.isMember("token") && request.isMember("msgId"))
		{
			Param_t stParam;
			stParam.uTokenId = request["token"].asUInt();
			stParam.uMsgId = request["msgId"].asUInt();
			stParam.uReqIdx = uReqIdx;
			stParam.uEncrypt = 0;

			Json::Value response = Json::nullValue;
			res = msgHub(session, stParam.uMsgId, request, response);
			if (res)
			{
				printf("\033[35m""response = %s""\033[0m\n", response.toStyledString().c_str());
				std::ostringstream os;
				Json::StreamWriterBuilder writerBuilder;
				writerBuilder["indentation"] = "";
				std::unique_ptr<Json::StreamWriter> const jsonWriter(writerBuilder.newStreamWriter());
				jsonWriter->write(response, &os);
				std::string reString = os.str();
				reString += " ";

				reply(session, &stParam, reString.c_str(), reString.length());

				return true;
			}
			res = false;
		}
		else
		{
			res = false;
		}


		return res;

}

/**
* @brief 消息分发
* @param session 会话话指针
* @param msgID 消息ID
* @param request 请求报文
* @param response 回复
* @return 成功/失败
**/
bool CNetProtocl::msgHub(ISession* session, unsigned int msgID, Json::Value &request, Json::Value &response)
{
	bool ret = IOrder::orderHub(msgID, request, response);

	if (ret && msgID == IOrder::AE_GET_SETTING)
	{
		keepAlive(session);
	}

	return ret;
}

/**
* @brief 登录
* @param session 会话话指针
* @param request 请求报文
* @param response 回复报文
* @return 成功/失败
**/
bool CNetProtocl::login(ISession* session, Json::Value &request, Json::Value &response)
{

	std::string rsaKey = request["rsaKey"].asString();

	response["rval"] = 0;
	response["msg_id"] = request["msg_id"].asUInt();
	response["param"] = 1;//TokenNumber
	response["version"] = "V1.1.0";
	
	char sRsaEncodeKey[300] = {0};
 	char sKeyStr[100] = {0};
	
	memset(m_AesKey, 0, aesKeyLength);
	RAND_pseudo_bytes(m_AesKey, aesKeyLength);

	for (size_t i = 0; i < aesKeyLength; i++)
	{
		sprintf(sKeyStr + i * 2, "%02x", m_AesKey[i]);
	}
	int iRet = app_rsa_encode(rsaKey.c_str(), sKeyStr, (unsigned char *)sRsaEncodeKey);
	if (iRet < 0)
	{
		return false;
	}

	response["aesCode"] = std::string(sRsaEncodeKey);

	response["timeout"] = 15;
	response["productType"] = 0;

	m_pTerminal->connect(session);

	return session->login();
}

/**
* @brief 登出
* @param session 会话话指针
* @return 成功/失败
**/
bool CNetProtocl::logout(NetServer::ISession* session)
{
	m_pTerminal->disconnet(session);
	return session->logout();
}

/**
* @brief 保活
* @param session 会话话指针
* @return 成功/失败
**/
bool CNetProtocl::keepAlive(NetServer::ISession* session)
{
	return session->keepAlive();
}

/**
* @brief 处理握手请求
* @param session 会话话指针
* @param request 请求报文
* @param response 回复报文
* @return 成功/失败
**/
bool CNetProtocl::handShake(NetServer::ISession* session, char* buf, int len)
{
		std::string recv = buf;
		Json::String errs;
		Json::Value request;
		Json::CharReaderBuilder readerBuilder;
		
		std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
		bool res = jsonReader->parse(recv.c_str(), recv.c_str() + recv.length(), &request, &errs);
		if (!res || !errs.empty())
		{
			return false;
		}
		
		printf("\033[35m""request = %s""\033[0m\n", request.toStyledString().c_str());

		if (request.isMember("token") && request.isMember("msg_id") && request["msg_id"].asUInt() == IOrder::AE_START_SESSION)
		{
			Json::Value response = Json::nullValue;

			if (login(session, request, response))
			{
				printf("\033[35m""response = %s""\033[0m\n", response.toStyledString().c_str());

				std::string reString = response.toStyledString().c_str();

				session->send(reString.c_str(), reString.length());
				return true;
			}
		}

		return false;
}

/**
* @brief 检查报文协议头
* @param buf 接收到的内容
* @param index 消息index 每次通讯+1
* @param len 接收到的内容长度
* @return 成功/失败
**/
bool CNetProtocl::headerCheck(const char *buf, unsigned int *index, unsigned int * len)
{
	struct msgHeader* pHeader = (struct msgHeader*)buf;

	if (pHeader->uMsgConstant != htonl(MSG_HEADER_CONS))
	{
		return false;
	}
	else
	{
		*index = ntohl(pHeader->uMsgIndex);
		*len = ntohl(pHeader->uMsgLength);
		return true;
	}
	/*//消息头：ABBC，前4个字节
	if (buf[0] != 0x41 || buf[1] != 0x42 || buf[2] != 0x42 || buf[3] != 0x43)
	{
		return false;
	}
	else
	{
		//获取消息索引，跳过消息头再取4个字节
		*index = (buf[4] << 24) + (buf[5] << 16) + (buf[6] << 8) + buf[7];
		//获取消息长度，跳过消息头及索引再取4个字节
		*len = (buf[8] << 24) + (buf[9] << 16) + (buf[10] << 8) + buf[11];
		return true;
	}
	*/
}


#ifndef ROUND_UP
#define ROUND_UP(x, align)       (((int)(x) + (align - 1)) & ~(align - 1))
#endif

#ifndef ROUND_DOWN
#define ROUND_DOWN(x, align)    ((int)(x) & ~(align - 1))
#endif

/**
* @brief 解密
* @param buf 待解码的内容
* @param len 待解码的内容长度
* @param decodeBuf 解码后的内容
* @param Length 解码后的内容长度
* @return 成功/失败
**/
bool CNetProtocl::decrypt(const char* buf, int len, char* decodeBuf, int* Length)
{

	char baseBuf[NET_APP_RECV_SIZE] = {0};
	
	int iBaseLen = EVP_DecodeBlock((unsigned char*)baseBuf, (const unsigned char*)buf, len);
	int iAesLen = ROUND_UP(iBaseLen, aesKeyLength);

	int iRet = aes_decrypt(baseBuf, iAesLen, decodeBuf, NET_APP_RECV_ADD, Length, m_AesKey);
	if (iRet < 0)
	{
		printf("\033[35m""aes decrypt failed""\033[0m\n");
		return false;
	}

	return true;
}

/**
* @brief 加密
* @param buf 待加密的内容
* @param len 待加密的内容长度
* @param encryptBuf 加密后的内容
* @param Length 加密后的内容长度
* @return 成功/失败
**/
bool CNetProtocl::encrypt(const char* buf, int len, unsigned char* encryptBuf, int* Length)
{
	int iRet = aes_encrypt((unsigned char*)buf, AES_MAX_IN_LEN, len, encryptBuf, AES_MAX_OUT_LEN, Length, m_AesKey);
	if(iRet < 0)
	{
		printf("\033[35m""app_aes_encrypt ERR: %d""\033[0m\n", iRet);
		return false;
	}
	
	if (*Length > AES_MAX_IN_LEN)
	{
		printf("\033[35m""encode str too large""\033[0m\n");
		return false;
	}

	return true;
}

/**
* @brief 发送回包
* @param session 会话话指针
* @param param 返回APP端参数
* @param buf 发送的报文
* @param len 发送的报文长度
* @return 成功/失败
**/
bool CNetProtocl::reply(NetServer::ISession* session, Param_t* param, const char *buf, int len)
{
	//todo sAesOut sendbuf 应该用堆区内存，否则可能会有栈溢出
	unsigned char sAesOut[AES_MAX_OUT_LEN] = {0};
	char sendbuf[AES_MAX_OUT_LEN_BASE64] = {0};

	if (buf == NULL || len <= 0)
	{
		return false;
	}

	if(len > AES_MAX_IN_LEN)
	{
		printf("\033[35m""encrypt str too large""\033[0m\n");
		return false;
	}
	
	int iAesOutLen = 0;
	if (!encrypt(buf, len, sAesOut, &iAesOutLen))
	{
		return false;
	}
	//int iRet = aes_encrypt((unsigned char*)buf, AES_MAX_IN_LEN, len, sAesOut, AES_MAX_OUT_LEN, &iAesOutLen, m_AesKey);
	//if(iRet < 0)
	//{
	//	printf("\033[35m""app_aes_encrypt ERR: %d""\033[0m\n", iRet);
	//	return false;
	//}
//
	//if (iAesOutLen > AES_MAX_IN_LEN)
	//{
	//	printf("\033[35m""encode str too large""\033[0m\n");
	//	return false;
	//}
	
	struct msgHeader* pHeader = (struct msgHeader*)sendbuf;
	char* pMsgBody = (sendbuf + sizeof(struct msgHeader));
	int iBase64OutLen = EVP_EncodeBlock((unsigned char *)pMsgBody, sAesOut, iAesOutLen); //base64编码

	pHeader->uMsgConstant = htonl(MSG_HEADER_CONS);
	pHeader->uMsgIndex = htonl(param->uReqIdx);
	pHeader->uMsgLength = htonl(iBase64OutLen);
	int iDataLen = strlen(pMsgBody) + sizeof(struct msgHeader);

	session->send(sendbuf, iDataLen);
	return true;
}
/*
int CNetProtocl::sendAppInfo(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	
	if (!reqParam.isMember("version"))
	{
		return -1;
	}

	resParam = Json::nullValue;

	return 0;
}

int CNetProtocl::sendTouchInfo(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	//AE_SEND_TOUCH_INFO
	if (!reqParam.isMember("touchX") || !reqParam.isMember("touchY") 
	|| !reqParam.isMember("screenWidth") || !reqParam.isMember("screenHeight") || !reqParam.isMember("touchType"))
	{
		return -1;
	}

	resParam = Json::nullValue;
	return 0;
}
*/
}//Screen
