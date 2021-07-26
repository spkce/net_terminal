#include "OrderNotify.h"
#include "Adapter.h"

namespace Screen
{

int COrderNotify::sendTouchInfo(Json::Value &request, Json::Value &response)
{
	//AE_SEND_TOUCH_INFO
	if (!request.isMember("touchX") || !request["touchX"].isInt()
		|| !request.isMember("touchY") ||!request["touchY"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	TouchInfo_t stTouchInfo = {0, 0, -1, -1, -1};
	stTouchInfo.touchX = request["touchX"].asInt();
	stTouchInfo.touchY = request["touchY"].asInt();

	if (request.isMember("screenWidth") && request["screenWidth"].isInt())
	{
		stTouchInfo.screenWidth = request["screenWidth"].asInt();
	}

	if (request.isMember("screenHeight") && request["screenHeight"].isInt())
	{
		stTouchInfo.screenHeight = request["screenHeight"].asInt();
	}

	if (request.isMember("touchType") && request["touchType"].isInt())
	{
		stTouchInfo.touchType = request["touchType"].asInt();
	}

	if (CAdapter::instance()->sendTouchInfo(&stTouchInfo))
	{
		return AE_SYS_NOERROR;
	}
	return AE_SYS_UNKNOWN_ERROR;
}


int COrderNotify::sendUpgradeResult(Json::Value &request, Json::Value &response)
{
	//AE_SEND_UPGRADE_RESULT
	if (!request.isMember("deviceType") || !request["deviceType"].isInt()
		||!request.isMember("upgradeResult") || !request["upgradeResult"].isUInt()
	)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	unsigned int progress = 0;
	if (request["upgradeResult"].asUInt() == 5)
	{
		if (request.isMember("downloadProgress") || !request["downloadProgress"].isUInt())
		{
			progress = request["downloadProgress"].asUInt();
		}
		else
		{
			return AE_SYS_UNKNOWN_ERROR;
		}
		
	}
	else if (request["upgradeResult"].asUInt() == 1)
	{
		if (request.isMember("upgradeProgress") || !request["upgradeProgress"].isUInt())
		{
			progress = request["upgradeProgress"].asUInt();
		}
		else
		{
			return AE_SYS_UNKNOWN_ERROR;
		}
	}
	
	if (CAdapter::instance()->upgradeResult(request["upgradeResult"].asUInt(), progress))
	{
		return AE_SYS_NOERROR;
	}
	return AE_SYS_UNKNOWN_ERROR;
}

}//Screen
