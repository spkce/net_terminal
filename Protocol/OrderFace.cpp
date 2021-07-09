#include "OrderFace.h"
#include "Adapter.h"

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
	
	int total = CAdapter::instance()->getFaceNum();
	
	if (total == 0)
	{
		response["totalFileNum"] = 0;
		return AE_SYS_NOERROR;
	}

	const int pageSize = request["pageSize"].asInt();
	const int index = request["index"].asInt();

	total = total > index + pageSize ? index + pageSize : total;

	for (int i = 0; i < total; i++)
	{
		FaceInfo_t info = {0};
		if (CAdapter::instance()->getFaceInfo(index + i, &info))
		{
			response["listing"][i]["faceID"] = info.faceID;
			response["listing"][i]["name"] = std::string(info.name);
			response["listing"][i]["identityID"] = std::string(info.identityID);
			response["listing"][i]["FaceUrl"] = std::string(info.path);
			response["listing"][i]["licenseNum"] = std::string(info.license);
		}
	}

	response["index"] = index;
	response["totalFileNum"] = total - index;
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

	if (request["mod"].asInt() == 0)
	{
		FaceInfo_t info = {0};
		info.faceID = request["faceID"].asInt();
		strncpy(info.name, request["name"].asCString(), sizeof(info.name));
		strncpy(info.identityID, request["identityID"].asCString(), sizeof(info.identityID));
		strncpy(info.license, request["licenseNum"].asCString(), sizeof(info.license));
		if (CAdapter::instance()->setFaceInfo(-1, &info))
		{
			return AE_SYS_NOERROR;
		}
	}
	else if (request["mod"].asInt() == 1)
	{
		FaceInfo_t info = {0};
		info.faceID = request["faceID"].asInt();
		strncpy(info.name, request["name"].asCString(), sizeof(info.name));
		strncpy(info.identityID, request["identityID"].asCString(), sizeof(info.identityID));
		strncpy(info.license, request["licenseNum"].asCString(), sizeof(info.license));
		if (CAdapter::instance()->setFaceInfo(info.faceID, &info))
		{
			return AE_SYS_NOERROR;
		}
	}
	else if (request["mod"].asInt() == 2)
	{
		int index = request["faceID"].asInt();
		if (CAdapter::instance()->setFaceInfo(index, NULL))
		{
			return AE_SYS_NOERROR;
		}
	}

	return AE_SYS_UNKNOWN_ERROR;
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
