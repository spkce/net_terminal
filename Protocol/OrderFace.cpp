#include "OrderFace.h"

namespace Screen
{

int COrderFace::getFaceInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_FACE_INFO
	if (!request.isMember("chanNo") || !request["chanNo"].isInt()
		||!request.isMember("pageSize") || !request["pageSize"].isInt()
		||!request.isMember("index") || !request["index"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	response["totalFileNum"] = 3;
	response["index"] = 1;
	response["listing"][0]["faceID"] = 1;
	response["listing"][0]["name"] = "nico";
	response["listing"][0]["identityID"] = "5xxxxxx";
	response["listing"][0]["FaceUrl"] = "http://xxxx";
	return AE_SYS_NOERROR;
}

int COrderFace::setFaceInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_FACE_INFO
	if (!request.isMember("chanNo") || !request["chanNo"].isInt()
		||!request.isMember("faceID") || !request["faceID"].isInt()
		||!request.isMember("name") || !request["name"].isString()
		||!request.isMember("identityID") || !request["identityID"].isString()
		||!request.isMember("mod") || !request["mod"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderFace::getOverTimeDrivingSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_OVERTIME_DRIVING_SETTING
	if (!request.isMember("chanNo") || !request["chanNo"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["daylightDrivingTimeMax"] = 8;
	response["nightDrivingTimeMax"] = 4;
	response["restTimeMin"] = 20;
	response["allDayDrivingTimeMax"] = 1;
	response["daylightStartTime"] = 480;
	response["daylightEndTime"] = 1050;
	return AE_SYS_NOERROR;
}

int COrderFace::setOverTimeDrivingSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_OVERTIME_DRIVING_SETTING
	if (!request.isMember("chanNo") || !request["chanNo"].isInt()
		|| !request.isMember("daylightDrivingTimeMax") || !request["daylightDrivingTimeMax"].isInt()
		|| !request.isMember("nightDrivingTimeMax") || !request["nightDrivingTimeMax"].isInt()
		|| !request.isMember("restTimeMin") || !request["restTimeMin"].isInt()
		|| !request.isMember("allDayDrivingTimeMax") || !request["allDayDrivingTimeMax"].isInt()
		|| !request.isMember("daylightStartTime") || !request["daylightStartTime"].isInt()
		|| !request.isMember("daylightEndTime") || !request["daylightEndTime"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderFace::faceContrast(Json::Value &request, Json::Value &response)
{
	if (!request.isMember("chanNo") || !request["chanNo"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["list"][0]["infoList"][0]["x"] = 1;
	response["list"][0]["infoList"][0]["y"] = 1;
	response["list"][0]["infoList"][0]["identityID"] = "5xxxxx"; 
	response["list"][0]["infoList"][0]["similarity"] = 80; 
	return AE_SYS_NOERROR;
}

}//Screen
