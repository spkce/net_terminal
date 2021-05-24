#include "OrderPeripheral.h"

namespace Screen
{

int COrderPeripheral::getAddedIPCList(Json::Value &request, Json::Value &response)
{
	//AE_GET_ADDED_IPC_LIST
	response["list"][0]["model"] = "UNKOWN";
	response["list"][0]["ip"] = "192.168.1.150";
	response["list"][0]["port"] = 122;
	response["list"][0]["bindChanNo"] = 7;
	response["list"][0]["activeMode"] = 1;
	response["list"][0]["firmVer"] = "V1.0.1";
	response["list"][0]["status"] = 1;
	response["list"][0]["IPv4Gateway"] = "192.168.0.1";
	response["list"][0]["HTTPPort"] = 8000;
	response["list"][0]["serialNum"] = "ipc8000";
	response["list"][0]["mac"] = "00:77:ba:aa:77";
	return AE_SYS_NOERROR;
}

int COrderPeripheral::setAddableIPCList(Json::Value &request, Json::Value &response)
{
	//AE_GET_ADDABLE_IPC_LIST
	response["list"][0]["model"] = "UNKOWN";
	response["list"][0]["ip"] = "192.168.1.150";
	response["list"][0]["port"] = 122;
	response["list"][0]["activeMode"] = 1;
	response["list"][0]["firmVer"] = "V1.0.1";
	response["list"][0]["status"] = 1;
	response["list"][0]["IPv4Gateway"] = "192.168.0.1";
	response["list"][0]["HTTPPort"] = 8000;
	response["list"][0]["serialNum"] = "ipc8000";
	response["list"][0]["mac"] = "00:77:ba:aa:77";
	return AE_SYS_NOERROR;
}

int COrderPeripheral::addIPC(Json::Value &request, Json::Value &response)
{
	//AE_ADD_IPC
	if (!request.isMember("mac") || !request["mac"].isString()
		|| !request.isMember("userName") || !request["userName"].isString()
		|| !request.isMember("password") || !request["password"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	response["list"][0]["model"] = "UNKOWN";
	response["list"][0]["ip"] = "192.168.1.150";
	response["list"][0]["port"] = 122;
	response["list"][0]["bindChanNo"] = 7;
	response["list"][0]["activeMode"] = 1;
	response["list"][0]["firmVer"] = "V1.0.1";
	response["list"][0]["status"] = 1;
	response["list"][0]["IPv4Gateway"] = "192.168.0.1";
	response["list"][0]["HTTPPort"] = 8000;
	response["list"][0]["serialNum"] = "ipc8000";
	response["list"][0]["mac"] = "00:77:ba:aa:77";
	return AE_SYS_NOERROR;
}

int COrderPeripheral::delIPC(Json::Value &request, Json::Value &response)
{
	//AE_DEL_IPC
	if (!request.isMember("chanNo") || !request["chanNo"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderPeripheral::getPeripheralStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_PERIPHERAL_STATUS
	if (!request.isMember("peripheralList") || !request["peripheralList"].isArray())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

}//Screen
