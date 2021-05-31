
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
* @brief ��Ϣ�ַ�
* @param msgID ��ϢID
* @param request ������
* @param response �ظ�
* @return �ɹ�/ʧ��
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
* @brief ֪ͨ��Ϣ��װ
* @param msgID ��ϢID
* @param buf ��Ϣ����
* @param len ��Ϣ����
* @return �ɹ�/ʧ��
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
