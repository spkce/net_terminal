
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

}//Screen
