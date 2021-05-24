#include "OrderStorage.h"

namespace Screen
{

int COrderStorage::getSDLetter(Json::Value &request, Json::Value &response)
{
	//AE_GET_SD_LETTER
	response["list"][0] = "A";
	response["list"][1] = "B";
	return AE_SYS_NOERROR;
}

int COrderStorage::getSDInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_SD_INFO
	if (!request.isMember("driver") || !request["driver"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["totalSpace"] = 30424;
	response["freeSpace"] = 29650;
	response["residualLife"] = "99";
	response["healthStatus"] = "good";
	response["status"] = "nonsupport";
	return AE_SYS_NOERROR;

}

int COrderStorage::setSDLockStatus(Json::Value &request, Json::Value &response)
{
	//AE_SET_SD_LOCK_STATUS
	if (!request.isMember("SDEncrypt") || !request["SDEncrypt"].isString()
		|| !request.isMember("reset") || !request["reset"].isString()
		|| !request.isMember("driver") || !request["driver"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderStorage::setSDPassword(Json::Value &request, Json::Value &response)
{
	//AE_SET_SD_PASSWD
	if (!request.isMember("oldPasswd") || !request["oldPasswd"].isString()
		|| !request.isMember("sdPasswd") || !request["sdPasswd"].isString()
		|| !request.isMember("driver") || !request["driver"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderStorage::formatSD(Json::Value &request, Json::Value &response)
{
	//AE_FORMAT
	if (!request.isMember("driver") || !request["driver"].isString()
		|| !request.isMember("sdPasswd") || !request["sdPasswd"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::getRecodeSchedule(Json::Value &request, Json::Value &response)
{
	//AE_GET_RECORD_SCHEDILE
	if (!request.isMember("day") || !request["day"].isInt()
		|| !request.isMember("chanNo") || !request["chanNo"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	int chanNo = request["chanNo"].asInt();
	response["chanNo"] = chanNo;
	response["listing"][0]["day"] = 1;
	response["listing"][0]["timeslots"][0]["type"] = 1;
	response["listing"][0]["timeslots"][0]["startTime"] = "00:00:00";
	response["listing"][0]["timeslots"][0]["ensTime"] = "23:59:59";
	
	response["listing"][1]["day"] = 2;
	response["listing"][1]["timeslots"][0]["type"] = 1;
	response["listing"][1]["timeslots"][0]["startTime"] = "00:00:00";
	response["listing"][1]["timeslots"][0]["ensTime"] = "23:59:59";
	return AE_SYS_NOERROR;
}

int COrderStorage::setRecodeSchedule(Json::Value &request, Json::Value &response)
{
	//AE_SET_RECORD_SCHEDILE
	if (!request.isMember("chanNo") || !request["chanNo"].isInt()
		|| !request.isMember("listing") || !request["listing"].isArray())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::copyDaySchedule(Json::Value &request, Json::Value &response)
{
	//AE_COPY_DAY_SCHEDILE
	if (!request.isMember("fromDay") || !request["fromDay"].isInt()
		|| !request.isMember("toDay") || !request["toDay"].isArray()
		|| !request.isMember("chanNo") || !request["chanNo"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::copyChannelSchedule(Json::Value &request, Json::Value &response)
{
	//AE_COPY_CHANNEL_SCHEDILE
	if (!request.isMember("fromChan") || !request["fromChan"].isInt()
		|| !request.isMember("toChan") || !request["toChan"].isArray())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::exportMediaFile(Json::Value &request, Json::Value &response)
{
	//AE_EXPORT_MEDIA_FILE
	if (!request.isMember("exportDevice") || !request["exportDevice"].isString()
		|| !request.isMember("chanNo") || !request["chanNo"].isInt())

	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	// !request.isMember("timeSlot") || !request["timeSlot"].isArray()
	//!request.isMember("filelist") || !request["filelist"].isArray()
	response["filelist"][0]["result"] = 1;
	response["filelist"][0]["name"] = "a.mp4";
	return AE_SYS_NOERROR;
}

int COrderStorage::exportMediaLog(Json::Value &request, Json::Value &response)
{
	//AE_EXPORT_LOG
	if (!request.isMember("exportDevice") || !request["exportDevice"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	if (request.isMember("timeSlot") && request["timeSlot"].isArray())
	{
		for (int i = 0; i < (int)request["timeSlot"].size(); i++)
		{
			if (!request["timeSlot"][i].isMember("startTime") 
				|| !request["timeSlot"][i]["startTime"].isString()
				|| !request["timeSlot"][i].isMember("endTime")
				|| !request["timeSlot"][i]["endTime"].isString())
			{
				response == Json::nullValue;
				return AE_SYS_UNKNOWN_ERROR;
			}
		}
	} 

	response["filelist"][0]["result"] = 1;
	response["filelist"][0]["name"] = "a.mp4";
	return AE_SYS_NOERROR;
}

int COrderStorage::exportConfig(Json::Value &request, Json::Value &response)
{
	//AE_EXPORT_CONFIG
	if (!request.isMember("type") || !request["type"].isInt()
		|| !request.isMember("exportDevice") ||request["exportDevice"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::importConfig(Json::Value &request, Json::Value &response)
{
	//AE_IMPORT_CONFIG
	if (!request.isMember("type") || !request["type"].isInt()
		|| !request.isMember("importDevice") ||request["importDevice"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::cancelExport(Json::Value &request, Json::Value &response)
{
	//AE_CONCEL_EXPORT
	if (!request.isMember("type") || !request["type"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::getStorageSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_STORAGE_SETTING
	response["clipDuration"] = 1;
	response["microphone"] = 1;
	response["cycleRecord"] = 1;
	response["subRec"] = 1;
	return AE_SYS_NOERROR;
}

int COrderStorage::setStorageSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_STORAGE_SETTING
	return AE_SYS_NOERROR;
}

}//Screen
