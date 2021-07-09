
#include "PushNotification.h"
#include "Adapter.h"
#include <regex>
#include <vector>

namespace Screen
{

int CPushNotification::notification(char* buf, int len, Json::Value &send)
{
	if (buf == NULL || len < (int)sizeof(Notification_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}

	int ret = AE_SYS_UNKNOWN_ERROR;
	PtrNotification_t p = (PtrNotification_t)buf;
	if (std::string(p->type) == "photoTaken")
	{
		send["type"] = "photoTaken";
		Json::Value & param = send["param"];

		if (p->photoTaken.result == 0)
		{
			param[0]["name"] = std::string(p->photoTaken.path);
			param[0]["thumbnail"] = std::string(p->photoTaken.thmPath);
			param[0]["startTime"] = std::string(p->photoTaken.startTime);
			param[0]["fileSize"] = p->photoTaken.filesize;
			param[0]["channel"] = p->photoTaken.channel;
			param[0]["model"] = p->photoTaken.result;
		}
		else
		{
			param[0]["model"] = p->photoTaken.result;
		}
		ret = AE_SYS_NOERROR;
	}

	return ret;
}

int CPushNotification::sendWarnInfo(char* buf, int len, Json::Value &send)
{
	if (buf == NULL || len < (int)sizeof(WarnInfo_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}

	PtrWarnInfo_t p = (PtrWarnInfo_t)buf;

	send["type"] = p->type;

	return AE_SYS_NOERROR;
}

int CPushNotification::sendCheckInfo(char* buf, int len, Json::Value &send)
{
	if (buf == NULL || len < (int)sizeof(CheckInfo_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}
	
	PtrCheckInfo_t p = (PtrCheckInfo_t)buf;
	
	send["checkCount"] = p->checkCount;
	send["checkList"][0]["index"] = p->index;
	send["checkList"][0]["content"] = std::string(p->content);

	char result[12] = {0};
	snprintf(result, sizeof(result), "%d", p->result);
	send["checkList"][0]["result"] = result;
	return AE_SYS_NOERROR;
}

int CPushNotification::sendClientMessage(char* buf, int len, Json::Value &send)
{
	//AE_SEND_CLIENT_MESSAGE
	if (buf == NULL || len < (int)sizeof(MessageInfo_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}
	
	PtrMessageInfo_t p = (PtrMessageInfo_t)buf;
	
	send["message"] = std::string(p->message);
	send["showType"] = p->showType;
	send["type"] = p->msgType;
	send["priority"] = p->priority;
	send["durction"] = p->durction;

	return AE_SYS_NOERROR;
}

int CPushNotification::sendLicense(char* buf, int len, Json::Value &send)
{
	//AE_SEND_CLIENT_MESSAGE
	if (buf == NULL || len < (int)sizeof(MessageInfo_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}

	PtrCeritfy_t p = (PtrCeritfy_t)buf;
	send["type"] = p->operate;
	send["id"] = p->id;

	time_t tmp;
	char timeBuf[32] = {0};
	tmp = p->startTime;
	struct tm *info = gmtime(&tmp);
	snprintf(timeBuf, sizeof(timeBuf), "%4d-%02d-%02d %02d:%02d:%02d", 
			info->tm_year + 1900, 
			info->tm_mon + 1,
			info->tm_mday,
			info->tm_hour,
			info->tm_min,
			info->tm_sec);
	send["startTime"] = timeBuf;

	tmp = p->endTime;
	info = gmtime(&tmp);
	snprintf(timeBuf, sizeof(timeBuf), "%4d-%02d-%02d %02d:%02d:%02d", 
			info->tm_year + 1900, 
			info->tm_mon + 1,
			info->tm_mday,
			info->tm_hour,
			info->tm_min,
			info->tm_sec);
	send["endTime"] = timeBuf;
	send["licenseDetail"]["licenseType"] = p->type;

	std::string content(p->detail);
	std::regex rex(",+");
	std::vector<std::string> vec(std::sregex_token_iterator(content.begin(), content.end(), rex, -1), std::sregex_token_iterator());
	if (p->type == 0)
	{
		//准运证
		if (vec.size() < 5)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}

		send["licenseDetail"]["siteName"] = vec[0];
		send["licenseDetail"]["unloadingArea"] = vec[1];
		send["licenseDetail"]["route"] = vec[2];
		send["licenseDetail"]["licenseNum"] = vec[3];
		send["licenseDetail"]["projectName"] = vec[4];
	}
	else if (p->type == 1)
	{
		//运输证
		if (vec.size() < 3)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}

		send["licenseDetail"]["transporttationEnterprise"] = vec[0];
		send["licenseDetail"]["licenseNum"] = vec[1];
		send["licenseDetail"]["vehicleNum"] = vec[2];
	}
	else if (p->type == 2)
	{
		//排放证
		if (vec.size() < 8)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}

		send["licenseDetail"]["projectName"] = vec[0];
		send["licenseDetail"]["projectAddress"] = vec[1];
		send["licenseDetail"]["constructinEmployer"] = vec[2];
		send["licenseDetail"]["constructionContracter"] = vec[3];
		send["licenseDetail"]["transporttationEnterprise"] = vec[4];
		send["licenseDetail"]["eliminateArea"] = vec[5];
		send["licenseDetail"]["licenseNum"] = vec[6];
		send["licenseDetail"]["route"] = vec[7];
	}
	else if (p->type == 3)
	{
		//处置通行证
		if (vec.size() < 8)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}
		send["licenseDetail"]["projectAddress"] = vec[0];
		send["licenseDetail"]["unloadingArea"] = vec[1];
		send["licenseDetail"]["route"] = vec[2];
		send["licenseDetail"]["licenseNum"] = vec[3];
		send["licenseDetail"]["projectName"] = vec[4];
		send["licenseDetail"]["allowTimePeriod"] = vec[5];
		send["licenseDetail"]["plateNum"] = vec[6];
		send["licenseDetail"]["certificateUnit"] = vec[7];
	}
	return AE_SYS_NOERROR;
}

}//Screen
