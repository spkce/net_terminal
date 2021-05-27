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
		stTouchInfo.screenWidth = request["touchType"].asInt();
	}

	if (CAdapter::instance()->sendTouchInfo(&stTouchInfo))
	{
		return AE_SYS_NOERROR;
	}
	return AE_SYS_UNKNOWN_ERROR;
}

}//Screen
