
#include "Log.h"
#include "Order.h"
#include "OrderSysterm.h"
#include "OrderMedia.h"
#include "OrderNetwork.h"
#include "OrderStorage.h"
#include "OrderTime.h"
#include "OrderPlatform.h"
#include "OrderFace.h"
#include "OrderPeripheral.h"
#include "OrderNotify.h"
#include "PushNotification.h"

namespace Screen
{

/**
* @brief 消息分发
* @param msgID 消息ID
* @param request 请求报文
* @param response 回复
* @return 成功/失败
**/
bool IOrder::orderHub(unsigned int msgID, Json::Value &request, Json::Value &response)
{
	Debug("NetTerminal", "msgID = %d\n", msgID);
	
	Json::Value reqParam = Json::nullValue;
	Json::Value resParam = Json::nullValue;
	if (request.isMember("param"))
	{
		reqParam.swap(request["param"]);
	}
	
	int res = AE_SYS_NOERROR;
	switch(msgID)
	{
		case AE_GET_DEVICE_INFO:
			res = COrderSysterm::getDeviceInfo(reqParam, resParam);
			break;
		case AE_GET_DEVICE_STATUS:
			res = COrderSysterm::getDeviceStatus(reqParam, resParam);
			break;
		case AE_GET_VEHICLE_STATUS:
			res = COrderSysterm::getVehicleStatus(reqParam, resParam);
			break;
		case AE_GET_SETTING:
			res = COrderSysterm::getStting(reqParam, resParam);
			break;
		case AE_SEND_TOUCH_INFO:
			res = COrderNotify::sendTouchInfo(reqParam, resParam);
			break;
		default:
			res = AE_SYS_UNKNOWN_ERROR;
			break;
	}
	
	if (resParam != Json::nullValue)
	{
		response["param"].swap(resParam["param"]);
	}

	response["rval"] = res;
	response["msgId"] = request["msgId"].asUInt();
	response["token"] = request["token"].asUInt();
	return res == AE_SYS_NOERROR;
}

/**
* @brief 通知消息封装
* @param msgID 消息ID
* @param buf 消息内容
* @param len 消息长度
* @return 成功/失败
**/
bool IOrder::notifyHub(unsigned int msgID, char* buf, int len, Json::Value &send)
{
	int res = AE_SYS_NOERROR;
	Json::Value & param = send["param"];
	switch(msgID)
	{
		case AE_SEND_WARN_INFO:
			res = CPushNotification::sendWarnInfo(buf, len, param);
		break;
	}

	return res == AE_SYS_NOERROR;
}

}//Screen
