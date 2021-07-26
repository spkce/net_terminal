#include "OrderPeripheral.h"
#include "Adapter.h"

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

	PeriStatus_t status = {0};
	if (CAdapter::instance()->getPeripheralStatus(&status))
	{
		Json::Value & list = request["peripheralList"];
		for (int i = 0; i < (int)list.size(); i++)
		{
			if (list[i].asString() == "lift" && status.lift != -1)
			{
				response["lift"] = status.lift;
			}
			else if (list[i].asString() == "hermetic" && status.hermetic != -1)
			{
				response["hermetic"] = status.hermetic;
			}
			else if (list[i].asString() == "carry" && status.carry != -1)
			{
				response["carry"] = status.carry;
			}
			else if (list[i].asString() == "ledScreen" && status.led != -1)
			{
				response["ledScreen"] = status.led;
			}
			else if (list[i].asString() == "audibleVisualAlarm" && status.audioAlarm != -1)
			{
				response["audibleVisualAlarm"] = status.audioAlarm;
			}
			else if (list[i].asString() == "conbox" && status.conbox != -1)
			{
				response["conbox"] = status.conbox;
			}
			else if (list[i].asString() == "cam0" && status.cam[0] != -1)
			{
				response["cam0"] = status.cam[0];
			}
			else if (list[i].asString() == "cam1" && status.cam[1] != -1)
			{
				response["cam1"] = status.cam[1];
			}
			else if (list[i].asString() == "cam2" && status.cam[2] != -1)
			{
				response["cam2"] = status.cam[2];
			}
			else if (list[i].asString() == "cam3" && status.cam[3] != -1)
			{
				response["cam3"] = status.cam[3];
			}
			else if (list[i].asString() == "cam4" && status.cam[4] != -1)
			{
				response["cam4"] = status.cam[4];
			}
			else if (list[i].asString() == "cam5" && status.cam[5] != -1)
			{
				response["cam5"] = status.cam[5];
			}
			else if (list[i].asString() == "cam6" && status.cam[6] != -1)
			{
				response["cam6"] = status.cam[6];
			}
			else if (list[i].asString() == "cam7" && status.cam[7] != -1)
			{
				response["cam7"] = status.cam[7];
			}
		}
		return AE_SYS_NOERROR;
	}

	return AE_SYS_UNKNOWN_ERROR;
}

}//Screen
