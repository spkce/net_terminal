#include "OrderSmart.h"

namespace Screen
{

int COrderSmart::getCarStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_CAR_STATUS
	response["corneringLamp"] = 0;
	response["brake"] = 0;
}

int COrderSmart::getFaceInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_FACE_INFO
	if (!request.isMember("chanNo") || !request["chanNo"].isInt()
		|| !request.isMember("pageSize") ||  request["pageSize"].isInt()
		|| !request.isMember("index") || request["index"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["totalFileNum"] = 1;
	response["index"] = 1;
	response["listing"][0]["faceID"] = 1;
	response["listing"][0]["name"] = "";
	response["listing"][0]["identifyID"] = "";
	response["listing"][0]["groupID"] = "";
	response["listing"][0]["faceVersion"] = "";
	response["listing"][0]["licenseNum"] = "";

	return AE_SYS_NOERROR;
}

int COrderSmart::setFaceInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_FACE_INFO
	if (!request.isMember("chanNo") || !request["chanNo"].isInt()
		|| !request.isMember("faceID") ||  request["faceID"].isInt()
		|| !request.isMember("name") || request["name"].isString()
		|| !request.isMember("identifyID") || request["identifyID"].isString()
		|| !request.isMember("mod") || request["mod"].isInt()
		)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderSmart::faceContrast(Json::Value &request, Json::Value &response)
{
	//AE_FACE_CONTRAST
	if (!request.isMember("chanNo") || !request["chanNo"].isInt()
		|| !request.isMember("pic") ||  request["pic"].isString()
	)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

} // namespace Screen
