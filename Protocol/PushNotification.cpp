
#include "PushNotification.h"
#include "Adapter.h"
#include <regex>
#include <vector>

namespace Screen
{

/**
* @brief 通知
* @param buf 推送内容
* @param len 推送内容
* @param send 推送报文
* @return 错误码
**/
int CPushNotification::notification(char* buf, int len, Json::Value &send)
{
	//AE_NOTIFICATION
	if (buf == NULL || len < (int)sizeof(Notification_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}

	int ret = AE_SYS_UNKNOWN_ERROR;
	PtrNotification_t p = (PtrNotification_t)buf;
	std::string notifyType(p->type);
	if (notifyType == "photoTaken")
	{
		send["type"] = notifyType;
		Json::Value & param = send["param"];

		if (p->photoTaken.result == 0)
		{
			param[0]["name"] = std::string(p->photoTaken.path);
			param[0]["thumbnail"] = std::string(p->photoTaken.thmPath);
			param[0]["startTime"] = std::string(p->photoTaken.startTime);
			param[0]["fileSize"] = p->photoTaken.filesize;
			param[0]["channel"] = p->photoTaken.channel;
			param[0]["model"] = p->photoTaken.result;
		}
		else
		{
			param[0]["model"] = p->photoTaken.result;
		}
		ret = AE_SYS_NOERROR;
	}
	else if (notifyType == "faceResult")
	{
		send["type"] = notifyType;
		send["param"][0]["result"] = p->faceResult.result;
		send["param"][0]["faceSimilarity"] = p->faceResult.similarity;
		ret = AE_SYS_NOERROR;
	}
	else if (notifyType == "ADASAlarm" || notifyType == "DBAAlarm")
	{
		send["type"] = notifyType;
		send["param"][0]["detailType"] = p->alarm.detailType;
		send["param"][0]["picName"] = std::string(p->alarm.picName);
		send["param"][0]["videoName"] = std::string(p->alarm.videoName);
		send["param"][0]["time"] = std::string(p->alarm.stime);
		send["param"][0]["chanNo"] = p->alarm.channel;
		ret = AE_SYS_NOERROR;
	}
	else if (notifyType == "peripheralAccessStatus")
	{
		send["type"] = notifyType;
		send["param"][0]["deviceType"] = std::string(p->peripheral.deviceName);
		send["param"][0]["status"] = p->peripheral.state;
		ret = AE_SYS_NOERROR;
	}
	else if (notifyType == "firmwareFound")
	{
		send["type"] = notifyType;
		send["param"][0]["url"] = std::string(p->upgrade.url);
		ret = AE_SYS_NOERROR;
	}
	else if (notifyType == "gearChange")
	{
		send["type"] = notifyType;
		send["param"][0]["gear"] = p->gear.gear;
		ret = AE_SYS_NOERROR;
	}
	else if (notifyType == "liftStatus" || notifyType == "hermeticStatus"
		|| notifyType == "carryStatus" || notifyType == "speedLimitStatus"
		|| notifyType == "liftLimitStatus" || notifyType == "rotateLimitStatus"
		|| notifyType == "lockStatus")
	{
		send["type"] = notifyType;
		send["param"][0]["status"] = p->vehicle.state;
		ret = AE_SYS_NOERROR;
	}

	return ret;
}

/**
* @brief 报警信息通知
* @param buf 推送内容
* @param len 推送内容
* @param send 推送报文
* @return 错误码
**/
int CPushNotification::sendWarnInfo(char* buf, int len, Json::Value &send)
{
	//AE_SEND_WARN_INFO
	if (buf == NULL || len < (int)sizeof(WarnInfo_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}

	PtrWarnInfo_t p = (PtrWarnInfo_t)buf;

	send["type"] = p->type;

	return AE_SYS_NOERROR;
}

/**
* @brief 自检信息通知
* @param buf 推送内容
* @param len 推送内容
* @param send 推送报文
* @return 错误码
**/
int CPushNotification::sendCheckInfo(char* buf, int len, Json::Value &send)
{
	//AE_SEND_SELF_CHECKING_INFO
	if (buf == NULL || len < (int)sizeof(CheckInfo_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}
	
	PtrCheckInfo_t p = (PtrCheckInfo_t)buf;
	
	send["checkCount"] = p->checkCount;
	send["checkList"][0]["index"] = p->index;
	send["checkList"][0]["content"] = std::string(p->content);

	char result[12] = {0};
	snprintf(result, sizeof(result), "%d", p->result);
	send["checkList"][0]["result"] = result;
	return AE_SYS_NOERROR;
}

/**
* @brief 消息通知
* @param buf 推送内容
* @param len 推送内容
* @param send 推送报文
* @return 错误码
**/
int CPushNotification::sendClientMessage(char* buf, int len, Json::Value &send)
{
	//AE_SEND_CLIENT_MESSAGE
	if (buf == NULL || len < (int)sizeof(MessageInfo_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}
	
	PtrMessageInfo_t p = (PtrMessageInfo_t)buf;
	
	send["message"] = std::string(p->message);
	send["showType"] = p->showType;
	send["type"] = p->msgType;
	send["priority"] = p->priority;
	send["durction"] = p->durction;

	return AE_SYS_NOERROR;
}

/**
* @brief 许可证通知
* @param buf 推送内容
* @param len 推送内容
* @param send 推送报文
* @return 错误码
**/
int CPushNotification::sendLicense(char* buf, int len, Json::Value &send)
{
	//AE_SEND_CLIENT_MESSAGE
	if (buf == NULL || len < (int)sizeof(MessageInfo_t))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}

	PtrCeritfy_t p = (PtrCeritfy_t)buf;
	send["type"] = p->operate;
	send["id"] = p->id;

	time_t tmp;
	char timeBuf[32] = {0};
	tmp = p->startTime;
	struct tm *info = gmtime(&tmp);
	snprintf(timeBuf, sizeof(timeBuf), "%4d-%02d-%02d %02d:%02d:%02d", 
			info->tm_year + 1900, 
			info->tm_mon + 1,
			info->tm_mday,
			info->tm_hour,
			info->tm_min,
			info->tm_sec);
	send["startTime"] = timeBuf;

	tmp = p->endTime;
	info = gmtime(&tmp);
	snprintf(timeBuf, sizeof(timeBuf), "%4d-%02d-%02d %02d:%02d:%02d", 
			info->tm_year + 1900, 
			info->tm_mon + 1,
			info->tm_mday,
			info->tm_hour,
			info->tm_min,
			info->tm_sec);
	send["endTime"] = timeBuf;
	send["licenseDetail"]["licenseType"] = p->type;

	std::string content(p->detail);
	std::regex rex(",+");
	std::vector<std::string> vec(std::sregex_token_iterator(content.begin(), content.end(), rex, -1), std::sregex_token_iterator());
	if (p->type == 0)
	{
		//准运证
		if (vec.size() < 5)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}

		send["licenseDetail"]["siteName"] = vec[0];
		send["licenseDetail"]["unloadingArea"] = vec[1];
		send["licenseDetail"]["route"] = vec[2];
		send["licenseDetail"]["licenseNum"] = vec[3];
		send["licenseDetail"]["projectName"] = vec[4];
	}
	else if (p->type == 1)
	{
		//运输证
		if (vec.size() < 3)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}

		send["licenseDetail"]["transporttationEnterprise"] = vec[0];
		send["licenseDetail"]["licenseNum"] = vec[1];
		send["licenseDetail"]["vehicleNum"] = vec[2];
	}
	else if (p->type == 2)
	{
		//排放证
		if (vec.size() < 8)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}

		send["licenseDetail"]["projectName"] = vec[0];
		send["licenseDetail"]["projectAddress"] = vec[1];
		send["licenseDetail"]["constructinEmployer"] = vec[2];
		send["licenseDetail"]["constructionContracter"] = vec[3];
		send["licenseDetail"]["transporttationEnterprise"] = vec[4];
		send["licenseDetail"]["eliminateArea"] = vec[5];
		send["licenseDetail"]["licenseNum"] = vec[6];
		send["licenseDetail"]["route"] = vec[7];
	}
	else if (p->type == 3)
	{
		//处置通行证
		if (vec.size() < 8)
		{
			return AE_SYS_UNKNOWN_ERROR;
		}
		send["licenseDetail"]["projectAddress"] = vec[0];
		send["licenseDetail"]["unloadingArea"] = vec[1];
		send["licenseDetail"]["route"] = vec[2];
		send["licenseDetail"]["licenseNum"] = vec[3];
		send["licenseDetail"]["projectName"] = vec[4];
		send["licenseDetail"]["allowTimePeriod"] = vec[5];
		send["licenseDetail"]["plateNum"] = vec[6];
		send["licenseDetail"]["certificateUnit"] = vec[7];
	}
	return AE_SYS_NOERROR;
}

/**
* @brief 电子围栏通知
* @param buf 推送内容
* @param len 推送内容
* @param send 推送报文
* @return 错误码
**/
int CPushNotification::sendArea(char* buf, int len, Json::Value &send)
{
	if (buf == NULL || len < (int)sizeof(AREA_INFO_T))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}

	PtrAreaInfo_t p = (PtrAreaInfo_t)buf;
	send["tatalCount"] = p->areaNum;
	if (p->operate == 3)
	{
		for (int i= 0; i < (int)p->areaNum; i++)
		{
			Json::Value & areaInfo = send["areaList"][i];
			Area_t & area = p->area[i];
			areaInfo["type"] = p->operate;
			areaInfo["areaType"] = area.type;
			areaInfo["id"] = area.id;
		}
	}
	else
	{
		for (int i= 0; i < (int)p->areaNum; i++)
		{
			Json::Value & areaInfo = send["areaList"][i];
			Area_t & area = p->area[i];
			areaInfo["type"] = p->operate;
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
				areaInfo["centerLong"] =area.center.longtitude;
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
				areaInfo["lineWidth"] = area.lineWidth[0];
				for (int i = 0; i < (int)area.pointNum; i++)
				{
					areaInfo["pointList"][i]["pointLong"] = area.inflctPoint[i].longtitude;
					areaInfo["pointList"][i]["pointLat"] = area.inflctPoint[i].latitude;
				}
			}
			else
			{
				continue;
			}
		}
	}
	return AE_SYS_NOERROR;
}

/**
* @brief 清空电子围栏
* @param buf 推送内容
* @param len 推送内容
* @param send 推送报文
* @return 错误码
**/
int CPushNotification::sendClearArea(char* buf, int len, Json::Value &send)
{
	if (buf == NULL || len < (int)sizeof(MSG_HDR_T))
	{
		return AE_SYS_UNKNOWN_ERROR; 
	}

	return AE_SYS_NOERROR;
}

}//Screen
