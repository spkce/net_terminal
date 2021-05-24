#include "OrderTime.h"

namespace Screen
{

int COrderTime::getDayLightTime(Json::Value &request, Json::Value &response)
{
	//AE_GET_DAYLIGHT_TIME
	
	response["DST"] = 1;
	response["startDate"] = "m04.5.1";
	response["endDate"] = "m04.5.1";
	response["startTime"] = "20:17";
	response["endTime"] = "20:17";
	response["DSTBias"] = "60";
	return AE_SYS_NOERROR;
}

int COrderTime::setDayLightTime(Json::Value &request, Json::Value &response)
{
	//AE_SET_DAYLIGHT_TIME
	if (!request.isMember("DST") || !request["DST"].isInt()
		|| request.isMember("startDate") || !request["startDate"].isString()
		|| request.isMember("endDate") || !request["endDate"].isString()
		|| request.isMember("startTime") || !request["startTime"].isString()
		|| request.isMember("endTime") || !request["endTime"].isString()
		|| request.isMember("DSTBias") || !request["DSTBias"].isString()
		)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderTime::getTimeZone(Json::Value &request, Json::Value &response)
{
	//AE_GET_TIMEZONE
	response["timeZone"] = "GMT+08:00";
	return AE_SYS_NOERROR;
}

int COrderTime::setTimeZone(Json::Value &request, Json::Value &response)
{
	//AE_SET_TIMEZONE
	if (!request.isMember("timeZone") || !request["timeZone"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderTime::getTimeSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_TIME_SETTING
	response["dateTime"] = "2021-01-01 10:10:10";
	response["DST"] = 0;
	response["startDate"] = "m04.5.1";
	response["endDate"] = "m04.5.1";
	response["startTime"] = "20:17";
	response["endTime"] = "20:17";
	response["DSTBias"] = "60";
	response["timeZone"] = "GMT+08:00";
	return AE_SYS_NOERROR;
}

int COrderTime::setTimeSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_TIME_SETTING
	return AE_SYS_NOERROR;
}

}//Screen
