
#include "OrderSysterm.h"
#include "Adapter.h"
#include <regex>
#include <vector>
#ifdef CONFIG_FENCE
#include "FenceManager.h"
#endif

namespace Screen
{

/**
* @brief 获取所有设置的当前参数
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getDeviceSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_ALL_CURRENT_SETTINGS
	return AE_SYS_NOERROR;
}

/**
* @brief 获取电池状态
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getBatteryLevel(Json::Value &request, Json::Value &response)
{
	//AE_GET_BATTERY_LEVEL
	response["batteryLevel"] = 75;

	return AE_SYS_NOERROR;
}

/**
* @brief 获取所有通道接入和录像状态
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getCameraStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_CAMERAS_STATUS
	
	for (int i = 0; i < 6; i++)
	{
		response[i]["chanNo"] = i;
		response[i]["connStat"] = 0;
		response[i]["recordStatus"] = 0;
		response[i]["subRecStatus"] = 0;
		char name[12] = {0};
		snprintf(name, sizeof(name), "CH%d", i + 1);
		response[i]["name"] = std::string(name);
	}

	return AE_SYS_NOERROR;
}

/**
* @brief 获取设备G-sensor数据
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getGSensorData(Json::Value &request, Json::Value &response)
{
	//AE_GET_GSENSOR_DATA
	response["accX"] = 111;
	response["accY"] = 111;
	response["accZ"] = 111;
	return AE_SYS_NOERROR;
}

/**
* @brief 获取当前GPS坐标
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getGPSData(Json::Value &request, Json::Value &response)
{
	//AE_GET_GPS
	response["valid"] = 1;
	response["time"] = "2021-05-10 17:00:01";
	response["divisionEW"] = "E";
	response["longitude"] = 435000000;
	response["divisionNS"] = "N";
	response["latitude"] = 108000000;
	response["direction"] = 630;
	response["height"] = 200;
	response["speed"] = 80000;
	response["satellites"] = 3;
	response["precision"] = 100;
	return AE_SYS_NOERROR;
}

/**
* @brief 获取设备信息
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getDeviceInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_DEVICE_INFO
	DevInfo_t stDevInfo = {0};
	if (CAdapter::instance()->getDeviceInfo(&stDevInfo))
	{
		response["deviceType"] = stDevInfo.sDeviceType;
		response["firmVer"] = stDevInfo.sFirmVersion;
		response["firmDate"] = stDevInfo.sFirmDate;
		response["paramVersion"] = stDevInfo.sParamVersion;
		response["serialNum"] = stDevInfo.sSerialNum;
		response["verifyCode"] = stDevInfo.sVerifyCode;
		response["language"] = stDevInfo.uLanguage;

		if(stDevInfo.uDDR)
		{
			response["DDR"] = stDevInfo.uDDR;
		}

		if(stDevInfo.sCustomID[0] != 0)
		{
			response["customID"] = stDevInfo.sCustomID;
		}

		if(stDevInfo.sHardwareVer[0] != 0)
		{
			response["hardwareVer"] = stDevInfo.sHardwareVer;
		}

		if (stDevInfo.sMCUVer[0] != 0)
		{
			response["MCUVer"] = stDevInfo.sMCUVer;
		}

		if (stDevInfo.sFpgaVer[0] != 0)
		{
			response["fpgaVersion"] = stDevInfo.sFpgaVer;
		}

		if (stDevInfo.sDspVer[0] != 0)
		{
			response["dspVersion"] = stDevInfo.sDspVer;
		}

		if (stDevInfo.sGpsVer[0] != 0)
		{
			response["GPSVersion"] = stDevInfo.sGpsVer;
		}

		response["peripheralDeviceList"][0]["name"] = "strKey.audioVersion";
		response["peripheralDeviceList"][0]["version"] = "AUDIOALARM_2021.3.5";

		response["peripheralDeviceList"][1]["name"] = "strKey.ledVersion";
		response["peripheralDeviceList"][1]["version"] = "v1.2";
#if 0
		AudioInfo_t audioInfo = {0};
		if (CAdapter::instance()->getAudioAlarmInfo(&audioInfo))
		{
			Json::Value audio = Json::nullValue;
			audio["name"] = "strKey.audioVersion";
			audio["version"] = std::string(audioInfo.ver);

			response["peripheralDeviceList"].append(audio);
		}

		LED_INFO_T ledInfo = {0};
		if (CAdapter::instance()->getLedScreenInfo(&ledInfo))
		{
			Json::Value led = Json::nullValue;
			led["name"] = "strKey.ledVersion";
			led["version"] = std::string(ledInfo.ver);

			response["peripheralDeviceList"].append(led);
		}
#endif
		return AE_SYS_NOERROR;
	}

	return AE_SYS_UNKNOWN_ERROR;
	
}

/**
* @brief 获取车辆相关信息
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getVehicleInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_VEHICLE_INFO
	response["driverPhone"] = "12345678910";
	response["provinceID"] = "12345";
	response["cityID"] = "12345";
	response["manufacturerID"] = "12345";
	response["ateColor"] = 0;
	response["ateType"] = 2; //[1,13]
	response["vehCharacter"] = "self";
	response["plateNum"] = "self";
	response["terminalType"] = "a3";
	response["terminalID"] = "1234567";
	response["VIN"] = "12345";
	response["engineNum"] = "12345";
	response["serial"] = "12345";
	return AE_SYS_NOERROR;
}

/**
* @brief 设置车辆相关信息
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setVehicleInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_VEHICLE_INFO
	return AE_SYS_NOERROR;
}

/**
* @brief 获取驾驶员相关信息
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getDriverInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_DRIVER_INFO
	response["licenseNumber"] = "12345678910";
	response["validTime"] = "12345";
	response["qualCert"] = "12345";
	response["status"] = 1;
	response["checkInTime"] = "2016.04.15";
	response["certificationOrgan"] = "xxxxx"; //[1,13]
	response["identityID"] = "123456789";
	response["driverName"] = "self";

	return AE_SYS_NOERROR;
}

/**
* @brief 设置驾驶员相关信息
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setDriverInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_DRIVER_INFO


	return AE_SYS_NOERROR;
}

/**
* @brief 获取车辆状态
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getCarStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_CAR_STATUS
	CarStatus_t stCarStatus = {0};
	if (CAdapter::instance()->getCarStatus(&stCarStatus))
	{
		response["corneringLamp"] = stCarStatus.corneringLamp;
		response["brake"] = stCarStatus.brake;
		return AE_SYS_NOERROR;
	}
	return AE_SYS_UNKNOWN_ERROR;
}

/**
* @brief 获取设备当前的搜星信息
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getSatelliteInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_SATELLITE_INFO
	if (!request.isMember("type"))
	{
		response = Json::nullValue;
		return AE_PROT_INVALID_TYPE;
	}
	
	response["satelliteCount"] = 3;
	response["HDOP"] = 1.0;
	//request["type"].asUInt();
	for (int i = 0; i < 3;i++)
	{
		response["infos"][i]["index"] = i;
		response["infos"][i]["radio"] = 30;
		response["infos"][i]["type"] = 1;
		response["infos"][i]["type"] = 1;
	}
	

	
	return AE_SYS_NOERROR;
}

/**
* @brief 获取设备状态
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getDeviceStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_DEVICE_STATUS
	if (!request.isMember("type") || !request["type"].isArray())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	DevStatus_t stDevStatus = {0};
	if (CAdapter::instance()->getDeviceStatus(&stDevStatus))
	{
		for (int i = 0; i < (int)request["type"].size(); i++)
		{
			if (request["type"][i].asString() == "time" && stDevStatus.curTime[0] != 0)
			{
				response["time"] = stDevStatus.curTime;
			}
			else if (request["type"][i].asString() == "CSQ" && stDevStatus.CSQ != -1)
			{
				response["CSQ"] = stDevStatus.CSQ;
			}
			else if (request["type"][i].asString() == "accStatus" && stDevStatus.accStatus != -1)
			{
				response["accStatus"] = stDevStatus.accStatus;
			}
			else if (request["type"][i].asString() == "locationStatus" && stDevStatus.locationStatus != -1)
			{
				response["locationStatus"] = stDevStatus.locationStatus;
			}
			else if (request["type"][i].asString() == "bizPIfLoginStatus" && stDevStatus.bizPIfLoginStatus != -1)
			{
				response["bizPIfLoginStatus"] = stDevStatus.bizPIfLoginStatus;
			}
		}

		return AE_SYS_NOERROR;
	}

	return AE_SYS_UNKNOWN_ERROR;
}

/**
* @brief 获取车辆状态
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getVehicleStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_VEHICLE_STATUS
	if (!request.isMember("type") || !request["type"].isArray())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	VehStatus_t stVehStatus = {0};
	if (CAdapter::instance()->getVehicleStatus(&stVehStatus))
	{
		for(int i = 0; i < (int)request["type"].size(); i++)
		{
			if (request["type"][i].asString() == "feedProtection" && stVehStatus.feedProtection != -1)
			{
				response["feedProtection"] = stVehStatus.feedProtection;
			}
			else if (request["type"][i].asString() == "gear" && stVehStatus.gear != -1)
			{
				response["gear"] = stVehStatus.gear;
			}
			else if (request["type"][i].asString() == "carryStatus" && stVehStatus.carryStatus != -1)
			{
				response["carryStatus"] = stVehStatus.carryStatus;
			}
			else if (request["type"][i].asString() == "hermeticStatus" && stVehStatus.hermeticStatus != -1)
			{
				response["hermeticStatus"] = stVehStatus.hermeticStatus;
			}
			else if (request["type"][i].asString() == "liftStatus" && stVehStatus.liftStatus != -1)
			{
				response["liftStatus"] = stVehStatus.liftStatus;
			}
			else if (request["type"][i].asString() == "speedLimitStatus" && stVehStatus.speedLimitStatus != -1)
			{
				response["speedLimitStatus"] = stVehStatus.speedLimitStatus;
			}
			else if (request["type"][i].asString() == "liftLimitStatus" && stVehStatus.liftLimitStatus != -1)
			{
				response["liftLimitStatus"] = stVehStatus.liftLimitStatus;
			}
			else if (request["type"][i].asString() == "rotateLimitStatus" && stVehStatus.rotateLimitStatus != -1)
			{
				response["rotateLimitStatus"] = stVehStatus.rotateLimitStatus;
			}
			else if (request["type"][i].asString() == "lockStatus" && stVehStatus.lockStatus != -1)
			{
				response["lockStatus"] = stVehStatus.lockStatus;
			}
			else if (request["type"][i].asString() == "maintainMode")
			{
				if (stVehStatus.maintainMode)
				{
					response["maintainMode"] = 1;
				}
				else
				{
					response["maintainMode"] = 0;
				}
				response["maintainValue"] = stVehStatus.maintainMode;
			}
			else if (request["type"][i].asString() == "speedLimitThreshold" && stVehStatus.speedLimitThreshold != -1)
			{
				response["speedLimitThreshold"] = stVehStatus.speedLimitThreshold;
			}
		}

		return AE_SYS_NOERROR;
	}

	return AE_SYS_UNKNOWN_ERROR;	
}

/**
* @brief 获取图像设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getPictureSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_PICTURE_SETTING
	if (!request.isMember("chanNo"))
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["OSDName"][0]["index"] = 1;
	response["OSDName"][0]["str"] = "channel name"; 

	return AE_SYS_NOERROR;
}

/**
* @brief 设置图像设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setPictureSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_PICTURE_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief 获取压缩设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getCompressSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_COMPRESS_SETTING
	if (!request.isMember("chanNo") || !request.isMember("streamType"))
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	response["resolution"] = 1;
	response["aspectRatio"] = 1;
	response["encodeMode"] = 1;
	response["videoQuality"] = 1;
	response["packageFormat"] = 0;
	response["bitRateType"] = 1;
	response["audioEncodeMode"] = 1;
	response["audioBitRate"] = 1;
	response["frameRate"] = 30;
	response["audioSamplingRate"] = 1;
	response["videoType"] = 1;
	response["bitRateType"] = 1;
	response["imageQuality"] = 1;

	return AE_SYS_NOERROR;
}

/**
* @brief 获取压缩设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setCompressSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_COMPRESS_SETTING
	
	return AE_SYS_NOERROR;
}

/**
* @brief 设置图片设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getImageSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_IMAGE_SETTING
	if (!request.isMember("chanNo") || !request.isMember("streamType"))
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["resolution"] = 0;
	response["aspectRatio"] = 0;
	response["encodeMode"] = 0;
	response["videoQuality"] = 0;
	response["distortionCalibration"] = 0;
	response["videoFormat"] = 0;
	response["packageFormat"] = 0;
	response["WDR"] = 0;
	response["linkageRec"] = 0;
	return AE_SYS_NOERROR;
}

/**
* @brief 设置图片设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setImageSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_IMAGE_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief 获取通用设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getGenericSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_GENERIC_SETTING
	response["language"] = 0;
	response["LCDRotate"] = 0;
	response["LCDPoweroff"] = 0;
	response["shutdownDelay"] = 0;
	response["plateNumber"] = "浙A22455";
	response["trainInfo"] = "aa/bbb-ccc";
	response["btnPressTip"] = 0;
	response["speakerSwitch"] = 0;
	response["volume"] = 0;
	response["waterMark"] = 0;
	response["touchTip"] = 0;
	response["enterScreenSaverTime"] = 0;
	response["recordMode"] = 0;

	return AE_SYS_NOERROR;
}

/**
* @brief 设置通用设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setGenericSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_GENERIC_SETTING

	return AE_SYS_NOERROR;
}

/**
* @brief 获取提醒设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getPromptSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_PROMPT_SETTING
	response["lightOnPrompt"] = 0;
	response["greenLightPrompt"] = 0;
	response["frontVehicleStartingPrompt"] = 0;
	response["motionDetect"] = 0;
	response["speedLimitDetection"] = 0;

	return AE_SYS_NOERROR;
}

/**
* @brief 设置提醒设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setPromptSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_PROMPT_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief 获取告警设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getAlertSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_ALERT_SETTING
	response["fatigueDrivingAlert"] = 0;
	response["speedingPrompt"] = 0;
	response["SDAbnormalTip"] = 0;

	return AE_SYS_NOERROR;
}

/**
* @brief 设置告警设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setAlertSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_ALERT_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief 获取传感设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getSensorSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_SENSOR_SETTING
	response["gSensorSensitity"] = 0;
	response["parkingSurveillance"] = 0;
	response["parkMontorThreshold"] = "80";
	response["gps"] = 0;
	return AE_SYS_NOERROR;
}

/**
* @brief 设置传感设置
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::setSensorSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_SENSOR_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief 获取某项设置的当前参数
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getStting(Json::Value &request, Json::Value &response)
{
	//AE_GET_SETTING
	if (!request.isMember("chanNo") || !request["chanNo"].isInt() 
	|| !request.isMember("type") || !request["type"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	std::string type = request["type"].asString();

	/*时间，目前只支持时间的获取*/
	if (type != "dateTime")
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	SETTING_T stSetting = {0};
	if (CAdapter::instance()->getSetting(&stSetting))
	{
		if (stSetting.sTime[0] == 0)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}

		response["chanNo"] = request["chanNo"].asUInt();
		response["type"] = type;
		response["value"] = stSetting.sTime;
		return AE_SYS_NOERROR;
	}

	return AE_SYS_UNKNOWN_ERROR;
}

/**
* @brief 获取许可证消息
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getLicenseInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_LICENSE_INFO
	if (!request.isMember("id") || !request["id"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (request["id"].asUInt() == 0)
	{
		const int ceritfyNum = CAdapter::instance()->getCeritfyNum();

		Json::Value licenseList = Json::nullValue;

		for (int i = 1; i <= ceritfyNum; i++)
		{
			Ceritfy_t ceritfy = {0};
			
			if (!CAdapter::instance()->getCeritfy(i, &ceritfy))
			{
				continue;
			}

			if (!licenseFill(licenseList[i - 1], &ceritfy))
			{
				return AE_SYS_UNKNOWN_ERROR;
			}
		}

		response["licenseList"].swap(licenseList);
	}
	else
	{
		Ceritfy_t ceritfy = {0};
		ceritfy.id = request["id"].asUInt();
		if (!CAdapter::instance()->getCeritfy(0, &ceritfy))
		{
			return AE_SYS_UNKNOWN_ERROR;
		}

		if (!licenseFill(response["licenseList"][0], &ceritfy))
		{
			return AE_SYS_UNKNOWN_ERROR;
		}
	}

	return AE_SYS_NOERROR;
}

/**
* @brief 设备启动自检
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::startSelfChecking(Json::Value &request, Json::Value &response)
{
	//AE_START_SELF_CHECKING
	return AE_SYS_NOERROR;
}

#ifdef CONFIG_FENCE
/**
* @brief 获取电子围栏信息
* @param request 请求报文
* @param response 回复报文
* @return 错误码
**/
int COrderSysterm::getAreaInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_AREA_INFO
	if (!request.isMember("index") || !request["index"].isUInt()
		|| !request.isMember("type") || !request["type"].isUInt()
		|| !request.isMember("pageSize") || !request["pageSize"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	const unsigned int type = request["type"].asUInt();
	const unsigned int index = request["index"].asUInt();
	const unsigned int pageSize = request["pageSize"].asUInt();
	const int areaNum = Fence::CFenceManager::instance()->getFenceNumber((Fence::FenceType_t)type);
	
	if (areaNum == 0)
	{
		response["totalCount"] = 0;
		return AE_SYS_NOERROR;
	}
	else if (areaNum > 0)
	{
		Json::Value fenceInfo = Json::nullValue;
		

		for (size_t i = index; i < (size_t)areaNum && i < index + pageSize; i++)
		{
			Json::Value  areaInfo = Json::nullValue;
			
			Fence::fence_t info;
			memset(&info, 0, sizeof(info));

			if (!Fence::CFenceManager::instance()->getFence((Fence::FenceType_t)type, i, &info))
			{
				break;
			}

			areaInfo["areaType"] = info.type;
			areaInfo["id"] = info.id;
			areaInfo["property"] = info.property;

			switch(info.property >> 11 & 0x07)
			{
				case 1:/*装货区*/
					areaInfo["areaName"] = "strKey.fenceType1";
					break;
				case 2: /*禁区*/
					areaInfo["areaName"] = "strKey.fenceType2";
					break;
				case 3: /*卸货区*/
					areaInfo["areaName"] = "strKey.fenceType3";
					break;
				case 4: /*限速区*/
					areaInfo["areaName"] = "strKey.fenceType4";
					break;
				case 5: /*停车区*/
					areaInfo["areaName"] = "strKey.fenceType5";
					break;
				case 6: /*路线*/
					areaInfo["areaName"] = "strKey.fenceType6";
					break;
				default:
				{
					std::string name = info.name;
					if (name != "")
					{
						areaInfo["areaName"] = name;
					}
				}
				break;
			}

			if (info.type == emFenceType_circle)
			{
				areaInfo["centerLong"] = info.shape.circle.centre.y;
				areaInfo["centerLat"] = info.shape.circle.centre.x;
				areaInfo["radius"] = info.shape.circle.radius;
			}
			else if (info.type == emFenceType_rect)
			{
				areaInfo["startPointLat"] = info.shape.rect.leftPoint.x;
				areaInfo["startPointLong"] = info.shape.rect.leftPoint.y;
				areaInfo["endPointLat"] = info.shape.rect.rightPoint.x;
				areaInfo["endPointLong"] = info.shape.rect.rightPoint.y;
			}
			else if (info.type == emFenceType_polygon)
			{
				areaInfo["polygonVertexCount"] = info.shape.polygon.num;
				for (int i = 0; i< (int)info.shape.polygon.num; i++)
				{
					areaInfo["pointList"][i]["pointLat"] = info.shape.polygon.vertex[i].x;
					areaInfo["pointList"][i]["pointLong"] = info.shape.polygon.vertex[i].y;
				}
			}
			else if (info.type == emFenceType_line)
			{
				for (int i = 0; i < (int)info.shape.line.num; i++)
				{
					areaInfo["pointList"][i]["pointLat"] = info.shape.line.segment[i].inflctPoint.x;
					areaInfo["pointList"][i]["pointLong"] = info.shape.line.segment[i].inflctPoint.y;
				}
			}
			else
			{
				continue;
			}

			fenceInfo["areaList"].append(areaInfo);
		}
		fenceInfo["totalCount"] = fenceInfo["areaList"].size();
		response.swap(fenceInfo);
		return AE_SYS_NOERROR;
	}

	return AE_SYS_UNKNOWN_ERROR;
}
#endif

int COrderSysterm::checkSelf(Json::Value &request, Json::Value &response)
{
	if (CAdapter::instance()->checkSelf())
	{
		return AE_SYS_NOERROR;
	}
	return AE_SYS_UNKNOWN_ERROR;
}

bool COrderSysterm::licenseFill(Json::Value &license, PtrCeritfy_t pCeritfy)
{
	license["type"] = pCeritfy->operate;
	license["id"] = pCeritfy->id;

	time_t tmp;
	char timeBuf[32] = {0};
	tmp = pCeritfy->startTime;
	struct tm *info = gmtime(&tmp);
	if (info == NULL)
	{
		return false;
	}

	snprintf(timeBuf, sizeof(timeBuf), "%4d-%02d-%02d %02d:%02d:%02d", 
			info->tm_year + 1900, 
			info->tm_mon + 1,
			info->tm_mday,
			info->tm_hour,
			info->tm_min,
			info->tm_sec);
	license["startTime"] = timeBuf;

	tmp = pCeritfy->endTime;
	info = gmtime(&tmp);
	snprintf(timeBuf, sizeof(timeBuf), "%4d-%02d-%02d %02d:%02d:%02d", 
			info->tm_year + 1900, 
			info->tm_mon + 1,
			info->tm_mday,
			info->tm_hour,
			info->tm_min,
			info->tm_sec);
	license["endTime"] = timeBuf;
	license["licenseDetail"]["licenseType"] = pCeritfy->type;

	std::string content(pCeritfy->detail);
	std::regex rex(",+");
	std::vector<std::string> vec(std::sregex_token_iterator(content.begin(), content.end(), rex, -1), std::sregex_token_iterator());
	if (pCeritfy->type == 0)
	{
		//准运证
		if (vec.size() < 5)
		{
			return false;
		}

		license["licenseDetail"]["siteName"] = vec[0];
		license["licenseDetail"]["unloadingArea"] = vec[1];
		license["licenseDetail"]["route"] = vec[2];
		license["licenseDetail"]["licenseNum"] = vec[3];
		license["licenseDetail"]["projectName"] = vec[4];
	}
	else if (pCeritfy->type == 1)
	{
		//运输证
		if (vec.size() < 3)
		{
			return false;
		}

		license["licenseDetail"]["transporttationEnterprise"] = vec[0];
		license["licenseDetail"]["licenseNum"] = vec[1];
		license["licenseDetail"]["vehicleNum"] = vec[2];
	}
	else if (pCeritfy->type == 2)
	{
		//排放证
		if (vec.size() < 8)
		{
			return false;
		}

		license["licenseDetail"]["projectName"] = vec[0];
		license["licenseDetail"]["projectAddress"] = vec[1];
		license["licenseDetail"]["constructinEmployer"] = vec[2];
		license["licenseDetail"]["constructionContracter"] = vec[3];
		license["licenseDetail"]["transporttationEnterprise"] = vec[4];
		license["licenseDetail"]["eliminateArea"] = vec[5];
		license["licenseDetail"]["licenseNum"] = vec[6];
		license["licenseDetail"]["route"] = vec[7];
	}
	else if (pCeritfy->type == 3)
	{
		//处置通行证
		if (vec.size() < 8)
		{
			return false;
		}
		license["licenseDetail"]["projectAddress"] = vec[0];
		license["licenseDetail"]["unloadingArea"] = vec[1];
		license["licenseDetail"]["route"] = vec[2];
		license["licenseDetail"]["licenseNum"] = vec[3];
		license["licenseDetail"]["projectName"] = vec[4];
		license["licenseDetail"]["allowTimePeriod"] = vec[5];
		license["licenseDetail"]["plateNum"] = vec[6];
		license["licenseDetail"]["certificateUnit"] = vec[7];
	}

	return true;
}

}//Screen
