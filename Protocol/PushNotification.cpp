
#include "PushNotification.h"
#include "Adapter.h"

namespace Screen
{

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
