
#include "IProtocl.h"
#include "COrderSysterm.h"
//#include "jsoncpp.h"
#include "openssl/aes.h"
#include "openssl/rand.h"
#include "openssl/evp.h"
#include "aes_encrypt.h"
#include "rsa_app.h"
#include "Session.h"
#include "NetProtocl.h"
#include "terminal.h"
#include <arpa/inet.h>

using namespace NetServer;
namespace Screen
{



CNetProtocl::CNetProtocl(Terminal::ITerminal* terminal)
:m_pTerminal(terminal)
{

}

CNetProtocl::~CNetProtocl()
{
}


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

				//printf("\033[35m""reString = %s""\033[0m\n", reString.c_str());
				//printf("\033[35m""reString = %d""\033[0m\n", reString.length());
				//printf("\033[35m""reString = %c""\033[0m\n", reString[reString.length()]);
				reply(session, &stParam, reString.c_str(), reString.length());
					//writerBuilder["indentation"] = "\t";
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

bool CNetProtocl::msgHub(ISession* session, unsigned int msgID, Json::Value &request, Json::Value &response)
{
	printf("\033[35m""msgID = %d""\033[0m\n", msgID);
	bool ret = false;
	if (!request.isMember("param"))
	{

		switch(msgID)
		{
			case IOrder::AE_STOP_SESSION:
				ret = logout(session, request, response);
				break;
			case IOrder::AE_GET_CAMERAS_STATUS:
				ret = getCameraStatus(session, request, response);
				break;
			default: break;
		}
	}
	else
	{
		int res = 0;
		Json::Value & reqParam = request["param"];
		Json::Value & resParam = response["param"];
		switch(msgID)
		{
			case IOrder::AE_GET_SETTING:
				res = getSetting(session, reqParam, resParam);
				break;

			case IOrder::AE_GET_VEHICLE_STATUS:
				res = getVehicleStatus(session, reqParam, resParam);
				break;
			case IOrder::AE_SEND_APP_INFO:
				res = sendAppInfo(session, reqParam, resParam);
				break;
			default: 
				res = -1;
				break;
		}
		
		ret = (res==0);

		response["rval"] = res;
		response["msgId"] = request["msgId"].asUInt();
		response["token"] = request["token"].asUInt();
	}

	return ret;
}

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

	response["aesCode"] = std::string(sRsaEncodeKey);

	response["timeout"] = 15;
	response["productType"] = 0;

	m_pTerminal->connect(session);

	return session->login();
}

bool CNetProtocl::logout(NetServer::ISession* session, Json::Value &request, Json::Value &response)
{
	m_pTerminal->disconnet(session);
	return session->logout();
}

bool CNetProtocl::keepAlive(NetServer::ISession* session, Json::Value &request, Json::Value &response)
{
	return session->keepAlive();
}

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

bool CNetProtocl::encrypt(const char* buf, int len, char* encryptBuf, int* Length)
{

}

bool CNetProtocl::reply(NetServer::ISession* session, Param_t* param, const char *buf, int len)
{
	unsigned char sAesOut[AES_MAX_OUT_LEN] = {0};
	char sendbuf[AES_MAX_OUT_LEN_BASE64] = {0};

	if(len > AES_MAX_IN_LEN)
	{
		printf("\033[35m""encrypt str too large""\033[0m\n");
		return false;
	}

	int iAesOutLen = 0;
	int iRet = aes_encrypt((unsigned char*)buf, AES_MAX_IN_LEN, len, sAesOut, AES_MAX_OUT_LEN, &iAesOutLen, m_AesKey);
	if(iRet < 0)
	{
		printf("\033[35m""app_aes_encrypt ERR: %d""\033[0m\n", iRet);
		return false;
	}

	if (iAesOutLen > AES_MAX_IN_LEN)
	{
		printf("\033[35m""encode str too large""\033[0m\n");
		return false;
	}
	
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

int CNetProtocl::getSetting(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	if (!reqParam.isMember("chanNo") || !reqParam.isMember("type"))
	{
		return -1;
	}

	unsigned int chanNo = reqParam["chanNo"].asUInt();
	std::string type = reqParam["type"].asString();

	resParam["chanNo"] = chanNo;
	resParam["type"] = type;
	
	if (type == "dateTime")
	{
		resParam["value"] = "2021-05-10 17:00:01";
	}
	
	return 0;
}

bool CNetProtocl::getCameraStatus(NetServer::ISession* session, Json::Value &request, Json::Value &response)
{
	Json::Value &resParam = response["param"];
	for(int i = 0; i < 6; i++)
	{
		resParam[i]["chanNo"] = i;
		resParam[i]["connStat"] = 0;
		resParam[i]["recordStatus"] = 0;
		resParam[i]["subRecStatus"] = 0;
		char name[12] = {0};
		snprintf(name, sizeof(name), "CH%d", i+1);
		resParam[i]["name"] = std::string(name);
	}
	
	response["rval"] = 0u;
	response["msgId"] = request["msgId"].asUInt();
	response["token"] = request["token"].asUInt();
	return true;
}

int CNetProtocl::getVehicleStatus(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	
	//if (!reqParam.isMember("type") || !reqParam["type"].isArray())
	//{
	//	return -1;
	//}

	//for(int i = 0; i < (int)reqParam["type"].size(); i++)
	//{
	//	if (reqParam["type"][i].asString() == "feedProtection")
	//	{
	//		resParam["feedProtection"] = 0;
	//	}
	//	else if (reqParam["type"][i].asString() == "gear")
	//	{
	//		resParam["gear"] = 1;
	//	}
	//}
	//"feedecStatus";
	//resParam["feedPro"] = 1;
	resParam["gear"] = 1;
	resParam["feedPro"] = 1;
	
	return 0;
}

int CNetProtocl::getDeviceStatus(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	//AE_GET_DEVICE_STATUS
	if (!reqParam.isMember("type") || !reqParam["type"].isArray())
	{
		return -1;
	}

	for(int i = 0; i < (int)reqParam["type"].size(); i++)
	{
		if (reqParam["type"][i].asString() == "time")
		{
			resParam["time"] = "2021-05-10 17:00:01";
		}
		else if (reqParam["type"][i].asString() == "CSQ")
		{
			resParam["CSQ"] = 1; // [0,31]
		}
		else if (reqParam["type"][i].asString() == "accStatus")
		{
			resParam["accStatus"] = 1;
		}
		else if (reqParam["type"][i].asString() == "locationStatus")
		{
			resParam["locationStatus"] = 1;
		}
		else if (reqParam["type"][i].asString() == "bizPIfLoginStatus")
		{
			resParam["bizPIfLoginStatus"] = 1;
		}
	}
	return 0;
}

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

}//Screen
