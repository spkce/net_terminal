
#include "PushNotification.h"
#include "Adapter.h"

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
		param[0]["name"] = std::string(p->photoTaken.path);
		param[0]["thumbnail"] = std::string(p->photoTaken.thmPath);
		param[0]["startTime"] = std::string(p->photoTaken.startTime);
		param[0]["fileSize"] = p->photoTaken.filesize;
		param[0]["channel"] = p->photoTaken.channel;
		param[0]["model"] = p->photoTaken.result;
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

}//Screen
