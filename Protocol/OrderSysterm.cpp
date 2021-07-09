
#include "OrderSysterm.h"
#include "Adapter.h"
#include <regex>
#include <vector>

namespace Screen
{

/**
* @brief ��ȡ�������õĵ�ǰ����
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::getDeviceSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_ALL_CURRENT_SETTINGS
	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡ���״̬
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::getBatteryLevel(Json::Value &request, Json::Value &response)
{
	//AE_GET_BATTERY_LEVEL
	response["batteryLevel"] = 75;

	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡ����ͨ�������¼��״̬
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ��ȡ�豸G-sensor����
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ��ȡ��ǰGPS����
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ��ȡ�豸��Ϣ
* @param request ������
* @param response �ظ�����
* @return ������
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
		return AE_SYS_NOERROR;
	}

	return AE_SYS_UNKNOWN_ERROR;
	
}

/**
* @brief ��ȡ���������Ϣ
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ���ó��������Ϣ
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setVehicleInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_VEHICLE_INFO
	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡ��ʻԱ�����Ϣ
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ���ü�ʻԱ�����Ϣ
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setDriverInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_DRIVER_INFO


	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡ����״̬
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ��ȡ�豸��ǰ��������Ϣ
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ��ȡ�豸״̬
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ��ȡ����״̬
* @param request ������
* @param response �ظ�����
* @return ������
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
			else if (request["type"][i].asString() == "maintainMode" && stVehStatus.maintainMode != -1)
			{
				response["maintainMode"] = stVehStatus.maintainMode;
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
* @brief ��ȡͼ������
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ����ͼ������
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setPictureSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_PICTURE_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡѹ������
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ��ȡѹ������
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setCompressSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_COMPRESS_SETTING
	
	return AE_SYS_NOERROR;
}

/**
* @brief ����ͼƬ����
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ����ͼƬ����
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setImageSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_IMAGE_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡͨ������
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::getGenericSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_GENERIC_SETTING
	response["language"] = 0;
	response["LCDRotate"] = 0;
	response["LCDPoweroff"] = 0;
	response["shutdownDelay"] = 0;
	response["plateNumber"] = "��A22455";
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
* @brief ����ͨ������
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setGenericSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_GENERIC_SETTING

	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡ��������
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ������������
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setPromptSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_PROMPT_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡ�澯����
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ���ø澯����
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setAlertSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_ALERT_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡ��������
* @param request ������
* @param response �ظ�����
* @return ������
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
* @brief ���ô�������
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::setSensorSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_SENSOR_SETTING
	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡĳ�����õĵ�ǰ����
* @param request ������
* @param response �ظ�����
* @return ������
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

	/*ʱ�䣬Ŀǰֻ֧��ʱ��Ļ�ȡ*/
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
* @brief ��ȡ���֤��Ϣ
* @param request ������
* @param response �ظ�����
* @return ������
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

		for (int i = 0; i < ceritfyNum; i++)
		{
			Ceritfy_t ceritfy = {0};
			
			if (!CAdapter::instance()->getCeritfy(request["id"].asUInt(), &ceritfy))
			{
				return AE_SYS_UNKNOWN_ERROR;
			}

			if (!licenseFill(licenseList[i], &ceritfy))
			{
				return AE_SYS_UNKNOWN_ERROR;
			}
		}

		response["licenseList"].swap(licenseList);
	}
	else
	{
		Ceritfy_t ceritfy = {0};
		if (!CAdapter::instance()->getCeritfy(request["id"].asUInt(), &ceritfy))
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
* @brief �豸�����Լ�
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::startSelfChecking(Json::Value &request, Json::Value &response)
{
	//AE_START_SELF_CHECKING
	return AE_SYS_NOERROR;
}

/**
* @brief ��ȡ����Χ����Ϣ
* @param request ������
* @param response �ظ�����
* @return ������
**/
int COrderSysterm::getAreaInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_AREA_INFO
	const int areaNum = CAdapter::instance()->getAreaNum();
	response["tatalCount"] = areaNum;
	if (areaNum == 0)
	{
		response["tatalCount"] = 0;
		return AE_SYS_NOERROR;
	}
	else if (areaNum > 0)
	{
		Area_t area = {0};
		for (size_t i = 0; i < (size_t)areaNum; i++)
		{
			Json::Value & areaInfo = response["areaList"][(int)i];
			if (!CAdapter::instance()->getArea(i, &area))
			{
				return AE_SYS_UNKNOWN_ERROR;
			}

			areaInfo["areaType"] = area.type;
			areaInfo["id"] = area.id;
			areaInfo["property"] = area.property;

			if (area.property != 0)
			{
				areaInfo["startTime"] = std::string(area.startTime);
				areaInfo["endTime"] = std::string(area.endTime);
			}

			if (area.type == 0)
			{
				areaInfo["centerLong"] = area.center.longtitude;
				areaInfo["centerLat"] = area.center.latitude;
				areaInfo["radius"] = area.radius;
			}
			else if (area.type == 1)
			{
				areaInfo["startPointLong"] = area.leftPoint.longtitude;
				areaInfo["startPointLat"] = area.leftPoint.latitude;
				areaInfo["endPointLong"] = area.rightPoint.longtitude;
				areaInfo["endPointLat"] = area.rightPoint.latitude;
			}
			else if (area.type == 2)
			{
				areaInfo["polygonVertexCount"] = area.vertexNum;
				for (int i = 0; i< (int)area.vertexNum; i++)
				{
					areaInfo["pointList"][i]["pointLong"] = area.vertex[i].longtitude;
					areaInfo["pointList"][i]["pointLat"] = area.vertex[i].latitude;
				}
			}
			else if (area.type == 3)
			{
				areaInfo["lineWidth"] = area.lineWidth;
				for (int i = 0; i < (int)area.pointNum; i++)
				{
					areaInfo["pointList"][i]["pointLong"] = area.inflctPoint[i].longtitude;
					areaInfo["pointList"][i]["pointLat"] = area.inflctPoint[i].latitude;
				}
			}
		}
		
		return AE_SYS_NOERROR;
	}

	return AE_SYS_UNKNOWN_ERROR;
}

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
		//׼��֤
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
		//����֤
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
		//�ŷ�֤
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
		//����ͨ��֤
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
